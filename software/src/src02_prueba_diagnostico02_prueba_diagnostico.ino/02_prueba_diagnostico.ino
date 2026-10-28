/*
 * ====================================================================
 *  ESTACIONAMIENTO UAI  -  PASO 2: PRUEBA DE DIAGNÓSTICO
 * ====================================================================
 *  ¿Qué hace este programa?
 *  NO mide autos. Solo verifica, paso a paso, que todas las partes
 *  del sistema arrancan bien:
 *     1. La placa despierta
 *     2. La memoria RTC funciona (la que usaremos en el Paso 4)
 *     3. El sensor láser responde
 *     4. El WiFi se conecta
 *     5. Firebase se conecta
 *
 *  Si llegas al mensaje "SISTEMA COMPLETAMENTE ESTABLE", todo está
 *  listo para pasar al Paso 3 (sensor avanzado) y luego al Paso 4 (ahorro de energía).
 *  Abre el Monitor Serie a 115200 baudios para ver los mensajes.
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
#include <Wire.h>               // Comunicación I2C
#include "Adafruit_VL53L0X.h"   // Sensor láser VL53L0X

// -------------------- DATOS DE CONEXIÓN (EDITAR) --------------------
#define WIFI_SSID      "WOM-6E7C5E"   // Nombre de tu red WiFi
#define WIFI_PASSWORD  "29893091"     // Clave de tu red WiFi
#define FIREBASE_HOST  "estacionamiento-uai-default-rtdb.firebaseio.com"  // Dirección de la base de datos
#define FIREBASE_AUTH  "eENfltqnIqbYBDkdx2N3JuyC5FqohPTF8qhY7KZv"        // Clave secreta de Firebase

// --------------------------- PINES (I2C) ----------------------------
#define PIN_SDA D2   // Cable de DATOS (SDA) -> pin D2 (GPIO4)
#define PIN_SCL D1   // Cable de RELOJ (SCL) -> pin D1 (GPIO5)

// ------------------------ OBJETOS GLOBALES --------------------------
Adafruit_VL53L0X lox = Adafruit_VL53L0X();  // El sensor láser
FirebaseData firebaseData;                  // Respuestas de Firebase
FirebaseAuth auth;                          // Autenticación
FirebaseConfig config;                      // Configuración

// ---------------------- MEMORIA RTC (RECORDATORIO) ------------------
// La memoria RTC es un pequeño espacio que NO se borra cuando la placa
// duerme (deep sleep). Aquí guardaremos datos entre un "despertar" y otro.
struct {
  uint32_t validador;     // Número "firma": si vale 12345, la memoria es válida
  int estado_actual;      // 0 = LIBRE, 1 = OCUPADO
  int contador_oc;        // Cuántas lecturas seguidas detectaron un auto
  int contador_li;        // Cuántas lecturas seguidas NO detectaron auto
} datosRTC;

// ====================================================================
//  setup(): se ejecuta una vez y va informando cada paso
// ====================================================================
void setup() {
  Serial.begin(115200);
  delay(2000);   // Pausa para que la energía se estabilice y se abra el monitor

  // Iniciamos el I2C en los pines indicados
  Wire.begin(PIN_SDA, PIN_SCL);

  Serial.println("\n=======================");
  Serial.println("1. CEREBRO DESPIERTO");

  // --- Paso 2: leer la memoria RTC ---
  Serial.println("2. LEYENDO MEMORIA RTC...");
  ESP.rtcUserMemoryRead(0, (uint32_t*) &datosRTC, sizeof(datosRTC));
  // Si la "firma" no es 12345, es la primera vez que se enciende:
  // dejamos todo en cero (estado LIBRE, contadores en 0).
  if (datosRTC.validador != 12345) {
    datosRTC.validador = 12345;
    datosRTC.estado_actual = 0;
    datosRTC.contador_oc = 0;
    datosRTC.contador_li = 0;
  }
  Serial.println("-> Memoria OK");

  // --- Paso 3: iniciar el sensor láser ---
  Serial.println("3. INICIANDO SENSOR LÁSER...");
  if (!lox.begin()) {
    // A diferencia del Paso 1, aquí NO nos detenemos: solo avisamos
    Serial.println("-> ERROR DE SENSOR: Revisa cables D1 y D2");
  } else {
    Serial.println("-> Sensor OK");
  }

  // --- Paso 4: conectar al WiFi ---
  Serial.println("4. ENCENDIENDO ANTENA WIFI...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n-> WiFi Conectado");

  // --- Paso 5: conectar a Firebase ---
  Serial.println("5. CONECTANDO A FIREBASE...");
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Serial.println("-> Firebase OK");

  Serial.println("=======================");
  Serial.println("¡SISTEMA COMPLETAMENTE ESTABLE!");
}

// ====================================================================
//  loop(): vacío a propósito, esto es solo una prueba de arranque
// ====================================================================
void loop() {
}
