/*
 * ====================================================================
 *  ESTACIONAMIENTO UAI  -  VERSIÓN 2 (MEJORADA): DEEP SLEEP OPTIMIZADO
 * ====================================================================
 *  Mejoras respecto a la Versión 1 (v1_original.ino):
 *   1. Despierta con la radio WiFi apagada (WAKE_RF_DISABLED), lo que
 *      reduce el pico de corriente en cada ciclo.
 *   2. WiFi no persistente: no escribe en la memoria flash cada vez.
 *   3. Espera máxima de 15 s para conectar el WiFi, para no agotar
 *      la batería si no hay red.
 *   4. Muestra el motivo del reinicio en el Monitor Serie (diagnóstico).
 *
 *  Misma lógica de detección: 5 lecturas para OCUPADO, 3 para LIBRE,
 *  umbral de 500 mm. Requiere unir D0 (GPIO16) con RST.
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

#define SLEEP_US 2000000UL   // 2 segundos

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

// Duerme sin encender el WiFi al despertar (menos pico de corriente)
void dormir() {
  ESP.deepSleep(SLEEP_US, WAKE_RF_DISABLED);
  delay(100);  // necesario: deja que el chip entre en deep sleep
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("\n--- Despertando del Deep Sleep ---");
  Serial.print("Motivo de reset: ");
  Serial.println(ESP.getResetReason());   // DIAGNÓSTICO

  // WiFi apagado y sin escribir en flash en cada ciclo
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);

  ESP.rtcUserMemoryRead(0, (uint32_t*) &datosRTC, sizeof(datosRTC));

  if (datosRTC.validador != 12345) {
    datosRTC.validador = 12345;
    datosRTC.estado_actual = 0;
    datosRTC.contador_oc = 0;
    datosRTC.contador_li = 0;
  }

  if (!lox.begin()) {
    Serial.println("Error Láser. Durmiendo...");
    dormir();
    return;
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

    WiFi.forceSleepWake();
    delay(1);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Timeout de 15 s para no colgarse si no hay red
    unsigned long t0 = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - t0 < 15000) {
      delay(100);
    }

    if (WiFi.status() == WL_CONNECTED) {
      config.host = FIREBASE_HOST;
      config.signer.tokens.legacy_token = FIREBASE_AUTH;
      Firebase.begin(&config, &auth);

      String str_estado = (datosRTC.estado_actual == 1) ? "OCUPADO" : "LIBRE";
      if (Firebase.setString(firebaseData, "/sensor_1/estado", str_estado)) {
        Serial.println("Enviado: " + str_estado);
      } else {
        Serial.println("Error Firebase: " + firebaseData.errorReason());
      }
    } else {
      Serial.println("No se pudo conectar al WiFi.");
      // Revertir para reintentar el envío en el próximo ciclo
      datosRTC.estado_actual = (datosRTC.estado_actual == 1) ? 0 : 1;
      if (datosRTC.estado_actual == 0) datosRTC.contador_oc = 5;
      else datosRTC.contador_li = 3;
    }

    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    delay(10);
  } else {
    Serial.println("Sin cambios. Volviendo a dormir rápido para ahorrar batería.");
  }

  ESP.rtcUserMemoryWrite(0, (uint32_t*) &datosRTC, sizeof(datosRTC));

  Serial.println("Durmiendo...");
  Serial.flush();
  dormir();
}

void loop() {}
