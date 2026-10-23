/*
 * ====================================================================
 *  ESTACIONAMIENTO UAI  -  PASO 1: SENSOR BÁSICO (SIEMPRE ENCENDIDO)
 * ====================================================================
 *  ¿Qué hace este programa?
 *  Mide con un sensor láser si hay un auto estacionado y avisa a
 *  internet (Firebase) si el espacio está "OCUPADO" o "LIBRE".
 *  Lo hace cada 2 segundos, sin parar.
 *
 *  Es la versión más simple: sirve para comprobar que el sensor, el
 *  WiFi y Firebase funcionan. Gasta mucha energía porque nunca duerme.
 *
 *  Materiales:
 *   - Placa ESP8266 (NodeMCU / Wemos D1 mini)
 *   - Sensor láser VL53L0X
 *
 *  Conexión del sensor VL53L0X a la placa:
 *     VIN -> 3V3
 *     GND -> GND
 *     SDA -> D2
 *     SCL -> D1
 * ====================================================================
 */

// ---------------------------- LIBRERÍAS -----------------------------
#include <ESP8266WiFi.h>        // Permite conectarse a una red WiFi
#include <FirebaseESP8266.h>    // Permite hablar con la base de datos Firebase
#include <Wire.h>               // Comunicación I2C (el "idioma" del sensor)
#include "Adafruit_VL53L0X.h"   // Controla el sensor láser VL53L0X

// -------------------- DATOS DE CONEXIÓN (EDITAR) --------------------
#define WIFI_SSID      "WOM-6E7C5E"   // Nombre de tu red WiFi
#define WIFI_PASSWORD  "29893091"     // Clave de tu red WiFi
#define FIREBASE_HOST  "estacionamiento-uai-default-rtdb.firebaseio.com"  // Dirección de la base de datos
#define FIREBASE_AUTH  "eENfltqnIqbYBDkdx2N3JuyC5FqohPTF8qhY7KZv"        // Clave secreta de Firebase

// --------------------------- PINES (I2C) ----------------------------
// El sensor se comunica por I2C, que usa 2 cables:
#define PIN_SDA D2   // Cable de DATOS  (SDA) -> pin D2 de la placa (GPIO4)
#define PIN_SCL D1   // Cable de RELOJ  (SCL) -> pin D1 de la placa (GPIO5)

// ------------------------ OBJETOS GLOBALES --------------------------
Adafruit_VL53L0X lox = Adafruit_VL53L0X();  // Representa al sensor láser
FirebaseData firebaseData;                  // Guarda las respuestas de Firebase
FirebaseAuth auth;                          // Datos de autenticación
FirebaseConfig config;                      // Configuración de Firebase

// ====================================================================
//  setup(): se ejecuta UNA sola vez al encender la placa
// ====================================================================
void setup() {
  Serial.begin(115200);   // Abre el monitor serie (para ver mensajes en el PC)

  // Le indicamos al I2C exactamente qué pines usar
  Wire.begin(PIN_SDA, PIN_SCL);

  // --- Paso 1: encender el sensor láser ---
  if (!lox.begin()) {
    Serial.println("Error de sensor láser");
    while (1);   // Si el sensor falla, el programa se queda detenido aquí
  }

  // --- Paso 2: conectar al WiFi ---
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {   // Espera hasta conectarse
    delay(500);
    Serial.print(".");                      // Un punto por cada intento
  }

  // --- Paso 3: conectar a Firebase ---
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Serial.println("Conectado y transmitiendo en vivo...");
}

// ====================================================================
//  loop(): se repite una y otra vez para siempre
// ====================================================================
void loop() {
  // Variable donde el sensor deja el resultado de la medición
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);   // Hace una medición de distancia

  // RangeStatus 4 significa "medición inválida".
  // Si la medición es válida Y el objeto está a menos de 500 mm (50 cm),
  // consideramos que hay un auto.
  if (measure.RangeStatus != 4 && measure.RangeMilliMeter < 500) {
    Firebase.setString(firebaseData, "/sensor_1/estado", "OCUPADO");
    Serial.println("Auto detectado -> OCUPADO");
  } else {
    Firebase.setString(firebaseData, "/sensor_1/estado", "LIBRE");
    Serial.println("Espacio vacío -> LIBRE");
  }

  delay(2000);   // Espera 2 segundos antes de volver a medir
}
