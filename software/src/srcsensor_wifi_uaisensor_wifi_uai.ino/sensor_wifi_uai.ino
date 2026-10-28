/*
 * ====================================================================
 *  ESTACIONAMIENTO UAI  -  Versión 2 : SENSOR AVANZADO (SIN DEEP SLEEP)
 * ====================================================================
 *  ¿Qué mejora respecto a la versión 1 (sensor básico)?
 *
 *   1. FILTRO ANTI-FALSAS-ALARMAS
 *      Una persona que pasa caminando ya no cambia el estado. El
 *      cambio solo se confirma si se repite varias lecturas seguidas
 *      (3 para OCUPADO, 4 para LIBRE).
 *
 *   2. ENVÍA MÁS DATOS A LA PÁGINA WEB
 *      Además del estado, manda: distancia medida, calidad de la señal
 *      WiFi, tiempo encendido y un "latido" (contador que sube cada
 *      2 s). Con el latido la web sabe si el sensor sigue vivo.
 *
 *   3. SOLO ENVÍA AL INSTANTE CUANDO ALGO CAMBIA
 *      El cambio de estado se publica de inmediato; el resto de datos
 *      se actualiza cada 2 segundos.
 *
 *   4. SE RECUPERA SOLO
 *      Si se cae el WiFi, reintenta conectarse sin reiniciar. Si el
 *      sensor falla al arrancar, reintenta en vez de quedarse trabado.
 *
 *   5. LED DE LA PLACA COMO INDICADOR
 *      Encendido = OCUPADO | Apagado = LIBRE | Parpadeando = conectando.
 *      (Sirve para mostrar el estado aunque no se vea la pantalla.)
 *
 *  Funciona con las 3 páginas web. La más completa es la
 *  07_web_presentacion.html.
 *
 *  Conexión del sensor VL53L0X a la placa:
 *     VIN -> 3V3
 *     GND -> GND
 *     SDA -> D2
 *     SCL -> D1
 * ====================================================================
 */

// ---------------------------- LIBRERÍAS -----------------------------
#include <ESP8266WiFi.h>        // Conexión WiFi
extern "C" {
  #include "wpa2_enterprise.h"  // Librería para WiFi con usuario y contraseña
}
#include <FirebaseESP8266.h>    // Conexión con Firebase
#include <Wire.h>               // Comunicación I2C (el "idioma" del sensor)
#include "Adafruit_VL53L0X.h"   // Sensor láser VL53L0X

// -------------------- DATOS DE CONEXIÓN (EDITAR) --------------------
#define WIFI_SSID      "UAI Alumnos" // Nombre de tu red WiFi
#define WIFI_USER      "vicentejfernandez@alumnos.uai.cl" // Tu usuario o correo de la universidad
#define WIFI_PASSWORD  "4%eZorhk"    // Clave de tu red WiFi
#define FIREBASE_HOST  "estacionamiento-uai-default-rtdb.firebaseio.com"  // Dirección de la base de datos
#define FIREBASE_AUTH  "eENfltqnIqbYBDkdx2N3JuyC5FqohPTF8qhY7KZv"        // Clave secreta de Firebase

// --------------------------- PINES ----------------------------------
#define PIN_SDA D2              // Cable de DATOS (SDA) del sensor -> pin D2 (GPIO4)
#define PIN_SCL D1              // Cable de RELOJ (SCL) del sensor -> pin D1 (GPIO5)
#define PIN_LED LED_BUILTIN     // LED azul de la placa (GPIO2). OJO: se enciende con LOW

// ------------------------ AJUSTES (SE PUEDEN CAMBIAR) ---------------
#define UMBRAL_MM             500    // Si hay algo a MENOS de 500 mm (50 cm) = hay un auto
#define INTERVALO_LECTURA_MS  1000    // Mide cada 1 segundo
#define INTERVALO_LATIDO_MS   2000   // Envía datos a la web cada 2 segundos
#define CONFIRMA_OCUPADO      4      // Lecturas seguidas con auto para decir OCUPADO (≈2 s)
#define CONFIRMA_LIBRE        3      // Lecturas seguidas sin auto para decir LIBRE   (≈1,5 s)
#define RUTA_SENSOR           "/sensor_1"   // Dónde se guardan los datos en Firebase

// ------------------------ OBJETOS GLOBALES --------------------------
Adafruit_VL53L0X lox = Adafruit_VL53L0X();  // El sensor láser
FirebaseData firebaseData;                  // Respuestas de Firebase
FirebaseAuth auth;                          // Autenticación
FirebaseConfig config;                      // Configuración

// ------------------------ VARIABLES DE ESTADO -----------------------
bool ocupado = false;               // Estado CONFIRMADO del espacio (false = LIBRE)
int  contOcupado = 0;               // Lecturas seguidas "con auto"
int  contLibre   = 0;               // Lecturas seguidas "sin auto"
int  distanciaMm = -1;              // Última distancia medida (-1 = nada detectado)
unsigned long cambioEstadoS = 0;    // Segundo (desde que se encendió) en que cambió el estado
unsigned long latido = 0;           // Contador que sube en cada envío
unsigned long tUltimaLectura = 0;   // Momento de la última medición
unsigned long tUltimoLatido  = 0;   // Momento del último envío
unsigned long tIntentoWiFi   = 0;   // Momento del último reintento de WiFi

// ====================================================================
//  FUNCIONES AUXILIARES
// ====================================================================

// Enciende o apaga el LED según el estado (LED encendido = OCUPADO)
void actualizarLed() {
  digitalWrite(PIN_LED, ocupado ? LOW : HIGH);   // En esta placa LOW = encendido
}

// Intenta iniciar el sensor láser. Si falla, parpadea y reintenta.
void iniciarSensor() {
  while (!lox.begin()) {
    Serial.println("Error de sensor láser. Revisa cables D1 (SCL) y D2 (SDA). Reintentando...");
    digitalWrite(PIN_LED, LOW);  delay(100);     // Destello corto
    digitalWrite(PIN_LED, HIGH); delay(400);
  }
  Serial.println("Sensor láser OK");
}

// Conecta al WiFi la primera vez (el LED parpadea mientras espera)
void conectarWiFi() {
  Serial.print("Conectando a WiFi WPA2-Enterprise");
  WiFi.mode(WIFI_STA);                 // Modo "cliente" (se conecta a un router)
  WiFi.disconnect(true);               // Limpia conexiones previas

  // Inyecta las credenciales de usuario y contraseña antes de conectar
wifi_station_set_wpa2_enterprise_auth(1);
wifi_station_set_enterprise_identity((uint8_t*)WIFI_USER, strlen(WIFI_USER));
wifi_station_set_enterprise_username((uint8_t*)WIFI_USER, strlen(WIFI_USER));
wifi_station_set_enterprise_password((uint8_t*)WIFI_PASSWORD, strlen(WIFI_PASSWORD));

  WiFi.begin(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(PIN_LED, !digitalRead(PIN_LED));   // Parpadeo
    delay(250);
    Serial.print(".");
  }
  WiFi.setAutoReconnect(true);         // Si se cae, la placa intenta volver sola
  digitalWrite(PIN_LED, HIGH);         // Apaga el LED
  Serial.println();
  Serial.print("WiFi conectado. IP: ");
  Serial.println(WiFi.localIP());
}

// Revisa que haya WiFi. Si no, reintenta cada 5 s sin bloquear el programa.
bool wifiListo() {
  if (WiFi.status() == WL_CONNECTED) return true;
  if (millis() - tIntentoWiFi > 5000) {
    tIntentoWiFi = millis();
    Serial.println("WiFi caído, reintentando...");
    WiFi.reconnect();
  }
  return false;
}

// Hace UNA medición. Guarda la distancia y devuelve true si hay un auto cerca.
bool leerSensor() {
  VL53L0X_RangingMeasurementData_t medida;
  lox.rangingTest(&medida, false);

  if (medida.RangeStatus == 4) {       // 4 = medición inválida / nada a la vista
    distanciaMm = -1;
    return false;
  }
  distanciaMm = medida.RangeMilliMeter;
  return distanciaMm < UMBRAL_MM;      // true = hay un auto
}

// FILTRO: decide si el estado realmente cambió.
// Devuelve true SOLO cuando el cambio queda confirmado.
bool actualizarEstado(bool autoDetectado) {
  if (autoDetectado) {
    contOcupado++;                     // Suma una lectura "con auto"
    contLibre = 0;                     // Reinicia la cuenta contraria
    if (!ocupado && contOcupado >= CONFIRMA_OCUPADO) {
      ocupado = true;                  // Confirmado: pasó a OCUPADO
      return true;
    }
  } else {
    contLibre++;
    contOcupado = 0;
    if (ocupado && contLibre >= CONFIRMA_LIBRE) {
      ocupado = false;                 // Confirmado: pasó a LIBRE
      return true;
    }
  }
  return false;                        // Sin cambios
}

// Envía TODOS los datos a Firebase en una sola petición.
void publicar() {
  if (!wifiListo()) return;            // Sin WiFi no hay nada que enviar

  latido++;                            // Cada envío suma 1 (la web lo usa para saber que seguimos vivos)

  FirebaseJson json;                   // Paquete de datos a enviar
  json.set("estado",       String(ocupado ? "OCUPADO" : "LIBRE"));
  json.set("distancia_mm", distanciaMm);                 // -1 = fuera de rango
  json.set("rssi",         (int)WiFi.RSSI());            // Señal WiFi en dBm (más cerca de 0 = mejor)
  json.set("uptime_s",     (int)(millis() / 1000));      // Segundos encendido
  json.set("cambio_s",     (int)cambioEstadoS);          // Segundo en que cambió el estado por última vez
  json.set("latido",       (int)latido);                 // Contador de envíos

  // updateNode actualiza solo estos campos sin borrar los demás
  if (Firebase.updateNode(firebaseData, RUTA_SENSOR, json)) {
    Serial.println("   -> Enviado a Firebase");
  } else {
    Serial.print("   -> Error Firebase: ");
    Serial.println(firebaseData.errorReason());
  }

  tUltimoLatido = millis();            // Reinicia el reloj del próximo envío
}

// ====================================================================
//  setup(): se ejecuta UNA vez al encender
// ====================================================================
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n=== Estacionamiento UAI - Sensor avanzado ===");

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);         // LED apagado al inicio

  Wire.begin(PIN_SDA, PIN_SCL);        // Inicia el I2C en los pines indicados

  iniciarSensor();                     // 1. Sensor láser
  conectarWiFi();                      // 2. WiFi

  config.host = FIREBASE_HOST;         // 3. Firebase
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Estado inicial: 3 mediciones rápidas para no empezar con un dato falso.
  // Si al menos 2 de 3 detectan auto, partimos en OCUPADO.
  int conAuto = 0;
  for (int i = 0; i < 3; i++) {
    if (leerSensor()) conAuto++;
    delay(100);
  }
  ocupado = (conAuto >= 2);
  if (ocupado) contOcupado = CONFIRMA_OCUPADO; else contLibre = CONFIRMA_LIBRE;
  cambioEstadoS = millis() / 1000;
  actualizarLed();

  publicar();                          // Primer envío
  Serial.println("Sistema listo. Monitoreando...");
}

// ====================================================================
//  loop(): se repite para siempre. Usa "millis()" para medir el tiempo
//  en vez de delay(), así el programa nunca se queda bloqueado.
// ====================================================================
void loop() {
  unsigned long ahora = millis();

  // --- A) Cada 0,5 s: medir y decidir si cambió el estado ---
  if (ahora - tUltimaLectura >= INTERVALO_LECTURA_MS) {
    tUltimaLectura = ahora;

    bool autoDetectado = leerSensor();
    bool cambio = actualizarEstado(autoDetectado);

    Serial.print("Distancia: ");
    if (distanciaMm < 0) Serial.print("fuera de rango");
    else { Serial.print(distanciaMm); Serial.print(" mm"); }
    Serial.print(" | Estado: ");
    Serial.println(ocupado ? "OCUPADO" : "LIBRE");

    if (cambio) {                      // El estado cambió: avisar AL INSTANTE
      cambioEstadoS = millis() / 1000;
      actualizarLed();
      Serial.println(ocupado ? ">>> AUTO DETECTADO -> OCUPADO" : ">>> ESPACIO VACÍO -> LIBRE");
      publicar();
    }
  }

  // --- B) Cada 2 s: enviar datos aunque nada haya cambiado ---
  if (millis() - tUltimoLatido >= INTERVALO_LATIDO_MS) {
    publicar();
  }
}