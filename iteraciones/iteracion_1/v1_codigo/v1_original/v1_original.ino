/*
 * ====================================================================
 *  ESTACIONAMIENTO UAI  -  VERSIÓN 1 (ORIGINAL): PRIMER CÓDIGO DEL SENSOR
 * ====================================================================
 *  Primera versión del firmware del proyecto. La placa duerme (Deep
 *  Sleep), despierta cada 2 s, mide con el VL53L0X y guarda los
 *  contadores en la memoria RTC. Solo enciende el WiFi y escribe en
 *  Firebase (/sensor_1/estado) cuando el estado cambia:
 *     - OCUPADO: 5 lecturas seguidas a menos de 500 mm
 *     - LIBRE:   3 lecturas seguidas sin auto
 *
 *  Requiere unir D0 (GPIO16) con RST para despertar del Deep Sleep.
 *  Versión siguiente: iteraciones/iteracion_2/v2_codigo/v2_mejorado/
 * ====================================================================
 */

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include "Adafruit_VL53L0X.h"

// 1. Credenciales (reemplaza por las tuyas)
#define WIFI_SSID "TU_WIFI"
#define WIFI_PASSWORD "TU_CLAVE_WIFI"
#define FIREBASE_HOST "estacionamiento-uai-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "TU_FIREBASE_SECRET"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// 2. Estructura RTC
struct {
  uint32_t validador;
  int estado_actual;
  int contador_oc;
  int contador_li;
} datosRTC;

void setup() {
  Serial.begin(115200);

  // Dar tiempo a que el voltaje se estabilice antes de exigir energía
  delay(1000);
  Serial.println("\n--- Despertando del Deep Sleep ---");

  ESP.rtcUserMemoryRead(0, (uint32_t*) &datosRTC, sizeof(datosRTC));

  if (datosRTC.validador != 12345) {
    datosRTC.validador = 12345;
    datosRTC.estado_actual = 0;
    datosRTC.contador_oc = 0;
    datosRTC.contador_li = 0;
  }

  if (!lox.begin()) {
    Serial.println("Error Láser. Durmiendo...");
    ESP.deepSleep(2e6);
  }

  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  bool auto_detectado = (measure.RangeStatus != 4 && measure.RangeMilliMeter < 500);
  bool cambiar_estado = false;

  if (auto_detectado) {
    datosRTC.contador_oc++;
    datosRTC.contador_li = 0;
    if (datosRTC.contador_oc >= 5 && datosRTC.estado_actual == 0) {
      datosRTC.estado_actual = 1;
      cambiar_estado = true;
    }
  } else {
    datosRTC.contador_li++;
    datosRTC.contador_oc = 0;
    if (datosRTC.contador_li >= 3 && datosRTC.estado_actual == 1) {
      datosRTC.estado_actual = 0;
      cambiar_estado = true;
    }
  }

  if (cambiar_estado) {
    Serial.println("Cambio detectado. Conectando WiFi y enviando a Firebase...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) { delay(100); }

    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&config, &auth);

    String str_estado = (datosRTC.estado_actual == 1) ? "OCUPADO" : "LIBRE";
    Firebase.setString(firebaseData, "/sensor_1/estado", str_estado);

    WiFi.disconnect(true);
    delay(10);
  } else {
    Serial.println("Sin cambios. Volviendo a dormir rápido para ahorrar batería.");
  }

  ESP.rtcUserMemoryWrite(0, (uint32_t*) &datosRTC, sizeof(datosRTC));

  // Hibernar por 2 segundos (2,000,000 microsegundos)
  Serial.println("Durmiendo...");
  ESP.deepSleep(2e6);
}

void loop() {}
