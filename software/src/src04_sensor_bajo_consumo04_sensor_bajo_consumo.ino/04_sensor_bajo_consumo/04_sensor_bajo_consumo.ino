/*
 * ====================================================================
 *  ESTACIONAMIENTO UAI  -  PASO 4: SENSOR DE BAJO CONSUMO (DEEP SLEEP)
 * ====================================================================
 *  ¿Qué hace este programa?
 *  Es la versión final para funcionar con batería. La placa pasa casi
 *  todo el tiempo "dormida". Cada 2 segundos despierta, mide, y vuelve
 *  a dormir. Solo enciende el WiFi cuando el estado CAMBIA de verdad
 *  (de LIBRE a OCUPADO o al revés), porque el WiFi es lo que más
 *  batería gasta.
 *
 *  Para evitar falsas alarmas (por ejemplo, una persona que pasa
 *  caminando), el cambio se confirma solo si se repite varias veces:
 *     - Para pasar a OCUPADO: 5 lecturas seguidas con auto detectado
 *     - Para pasar a LIBRE:   3 lecturas seguidas sin auto
 *
 *  Los contadores se guardan en la memoria RTC, que sobrevive al sueño.
 *
 *  IMPORTANTE (cableado del Deep Sleep):
 *  Para que la placa pueda despertarse sola, hay que unir con un cable
 *  el pin D0 (GPIO16) con el pin RST.
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
#include <FirebaseESP8266.h>    // Conexión con Firebase
#include <Wire.h>               // Comunicación I2C (agregado: antes faltaba)
#include "Adafruit_VL53L0X.h"   // Sensor láser VL53L0X

// -------------------- DATOS DE CONEXIÓN (EDITAR) --------------------
#define WIFI_SSID      "TU_WIFI"            // Nombre de tu red WiFi
#define WIFI_PASSWORD  "TU_CLAVE_WIFI"      // Clave de tu red WiFi
#define FIREBASE_HOST  "estacionamiento-uai-default-rtdb.firebaseio.com"  // Dirección de la base de datos
#define FIREBASE_AUTH  "TU_FIREBASE_SECRET" // Clave secreta de Firebase

// --------------------------- PINES (I2C) ----------------------------
// (Agregado: esta versión no tenía los pines declarados)
#define PIN_SDA D2   // Cable de DATOS (SDA) -> pin D2 (GPIO4)
#define PIN_SCL D1   // Cable de RELOJ (SCL) -> pin D1 (GPIO5)

// ------------------------ OBJETOS GLOBALES --------------------------
Adafruit_VL53L0X lox = Adafruit_VL53L0X();  // El sensor láser
FirebaseData firebaseData;                  // Respuestas de Firebase
FirebaseAuth auth;                          // Autenticación
FirebaseConfig config;                      // Configuración

// ---------------------------- MEMORIA RTC ---------------------------
// Espacio de memoria que NO se borra cuando la placa duerme.
// Así "recuerda" lo que pasó en los despertares anteriores.
struct {
  uint32_t validador;     // Número "firma": si vale 12345, los datos son válidos
  int estado_actual;      // 0 = LIBRE, 1 = OCUPADO
  int contador_oc;        // Lecturas seguidas con auto detectado
  int contador_li;        // Lecturas seguidas sin auto
} datosRTC;

// ====================================================================
//  setup(): en Deep Sleep, TODO el programa corre aquí en cada despertar
//  (la placa se reinicia cada vez, por eso loop() queda vacío)
// ====================================================================
void setup() {
  Serial.begin(115200);

  // Pausa para que el voltaje se estabilice antes de exigir energía
  delay(1000);
  Serial.println("\n--- Despertando del Deep Sleep ---");

  // Iniciamos el I2C en los pines indicados
  Wire.begin(PIN_SDA, PIN_SCL);

  // --- Recuperar los datos guardados antes de dormir ---
  ESP.rtcUserMemoryRead(0, (uint32_t*) &datosRTC, sizeof(datosRTC));

  // Si la firma no coincide, es el primer encendido: valores iniciales
  if (datosRTC.validador != 12345) {
    datosRTC.validador = 12345;
    datosRTC.estado_actual = 0;   // Empezamos en LIBRE
    datosRTC.contador_oc = 0;
    datosRTC.contador_li = 0;
  }

  // --- Iniciar el sensor láser ---
  if (!lox.begin()) {
    Serial.println("Error Láser. Durmiendo...");
    ESP.deepSleep(2e6);   // Si falla, duerme 2 s e intenta de nuevo
  }

  // --- Medir la distancia ---
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  // ¿Hay un auto? (medición válida y objeto a menos de 500 mm = 50 cm)
  bool auto_detectado = (measure.RangeStatus != 4 && measure.RangeMilliMeter < 500);
  bool cambiar_estado = false;   // Se pondrá en true solo si hay que avisar a Firebase

  // --- Lógica de confirmación (evita falsas alarmas) ---
  if (auto_detectado) {
    datosRTC.contador_oc++;      // Suma una lectura "con auto"
    datosRTC.contador_li = 0;    // Reinicia la cuenta de "sin auto"
    // Si lleva 5 seguidas y estaba LIBRE -> confirma que ahora está OCUPADO
    if (datosRTC.contador_oc >= 5 && datosRTC.estado_actual == 0) {
      datosRTC.estado_actual = 1;
      cambiar_estado = true;
    }
  } else {
    datosRTC.contador_li++;      // Suma una lectura "sin auto"
    datosRTC.contador_oc = 0;    // Reinicia la cuenta de "con auto"
    // Si lleva 3 seguidas y estaba OCUPADO -> confirma que ahora está LIBRE
    if (datosRTC.contador_li >= 3 && datosRTC.estado_actual == 1) {
      datosRTC.estado_actual = 0;
      cambiar_estado = true;
    }
  }

  // --- Solo si el estado cambió: conectar e informar ---
  if (cambiar_estado) {
    Serial.println("Cambio detectado. Conectando WiFi y enviando a Firebase...");

    // Conectar al WiFi (espera hasta lograrlo)
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) { delay(100); }

    // Conectar a Firebase
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&config, &auth);

    // Enviar el nuevo estado como texto
    String str_estado = (datosRTC.estado_actual == 1) ? "OCUPADO" : "LIBRE";
    Firebase.setString(firebaseData, "/sensor_1/estado", str_estado);

    // Apagar el WiFi para ahorrar batería
    WiFi.disconnect(true);
    delay(10);
  } else {
    Serial.println("Sin cambios. Volviendo a dormir rápido para ahorrar batería.");
  }

  // --- Guardar los datos en la memoria RTC para el próximo despertar ---
  ESP.rtcUserMemoryWrite(0, (uint32_t*) &datosRTC, sizeof(datosRTC));

  // --- A dormir ---
  // 2e6 = 2.000.000 microsegundos = 2 segundos
  Serial.println("Durmiendo...");
  ESP.deepSleep(2e6);
}

// ====================================================================
//  loop(): vacío a propósito. Con Deep Sleep la placa se reinicia en
//  cada despertar, así que nunca llega a ejecutarse.
// ====================================================================
void loop() {}
