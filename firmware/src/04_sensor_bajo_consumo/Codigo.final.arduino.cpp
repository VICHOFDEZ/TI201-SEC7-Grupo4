/*
 * ====================================================================
 *  ESTACIONAMIENTO UAI - SENSOR UNIVERSAL DE BAJO CONSUMO (DEEP SLEEP)
 * ====================================================================
 *  Compatible con: NodeMCU ESP8266 + VL53L0X + Firebase + Web Pasillos
 *
 *  CABLEADO DEEP SLEEP (D0 -> RST):
 *    1) DESCONECTA el cable D0-RST antes de subir el código.
 *    2) Sube el programa.
 *    3) CONECTA el cable D0-RST y presiona el botón RST una vez.
 *
 *  CABLEADO VL53L0X:
 *    VIN -> 3V3 | GND -> GND | SDA -> D2 (GPIO4) | SCL -> D1 (GPIO5)
 * ====================================================================
 */

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"

// ================= CONFIGURACIÓN UNIVERSAL (EDITAR) =================
#define SENSOR_ID        "sensor_1"   // Cambiar a "sensor_2" en la segunda placa
#define ZONA_ID          "p1"         // Pasillo asignado: "p1", "p2", "p3", "p4" o "p5"

#define WIFI_SSID        "Galaxy"     // Red WiFi 2.4 GHz (o "iPhone de Renato" con Maximizar compatibilidad)
#define WIFI_PASSWORD    "Mateo123"   // Contraseña de la red WiFi
#define FIREBASE_HOST    "estacionamiento-uai-default-rtdb.firebaseio.com" // SIN https://
#define FIREBASE_AUTH    "eENfltqnIqbYBDkdx2N3JuyC5FqohPTF8qhY7KZv"

// Parámetros de detección y energía
#define UMBRAL_MM        500          // Distancia en mm (500 mm = 50 cm)
#define LECTURAS_OCUPADO 3            // Lecturas seguidas para confirmar OCUPADO
#define LECTURAS_LIBRE   2            // Lecturas seguidas para confirmar LIBRE
#define TIEMPO_SLEEP_SEG 2            // Segundos durmiendo entre lecturas
#define CICLOS_LATIDO    8            // Envía latido cada ~16 s para mantener estado en línea
// ====================================================================

#define PIN_SDA D2
#define PIN_SCL D1

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Memoria RTC (sobrevive al Deep Sleep)
struct {
  uint32_t validador;
  int estado_actual;    // 0 = LIBRE, 1 = OCUPADO
  int contador_oc;
  int contador_li;
  int ciclos_latido;
  uint32_t latido;
} datosRTC;

void dormir() {
  Serial.println("Durmiendo...");
  ESP.deepSleep((uint64_t)TIEMPO_SLEEP_SEG * 1000000ULL);
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("\n--- Despertando (" SENSOR_ID ") ---");

  Wire.begin(PIN_SDA, PIN_SCL);

  // 1. Leer memoria RTC
  bool primer_encendido = false;
  ESP.rtcUserMemoryRead(0, (uint32_t*) &datosRTC, sizeof(datosRTC));
  if (datosRTC.validador != 12345) {
    datosRTC.validador = 12345;
    datosRTC.estado_actual = 0;
    datosRTC.contador_oc = 0;
    datosRTC.contador_li = 0;
    datosRTC.ciclos_latido = 0;
    datosRTC.latido = 0;
    primer_encendido = true;
  }

  // 2. Iniciar sensor láser VL53L0X
  if (!lox.begin()) {
    Serial.println("ERROR: No se detecta el VL53L0X.");
    dormir();
  }

  // 3. Medir distancia
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  bool auto_detectado = (measure.RangeStatus != 4 && measure.RangeMilliMeter < UMBRAL_MM);
  bool cambiar_estado = false;

  Serial.print("Distancia: ");
  Serial.println(measure.RangeStatus != 4 ? String(measure.RangeMilliMeter) + " mm" : "Fuera de rango");

  // 4. Filtro anti falsos positivos (histéresis)
  if (auto_detectado) {
    datosRTC.contador_oc++;
    datosRTC.contador_li = 0;
    if (datosRTC.contador_oc >= LECTURAS_OCUPADO && datosRTC.estado_actual == 0) {
      datosRTC.estado_actual = 1;
      cambiar_estado = true;
    }
  } else {
    datosRTC.contador_li++;
    datosRTC.contador_oc = 0;
    if (datosRTC.contador_li >= LECTURAS_LIBRE && datosRTC.estado_actual == 1) {
      datosRTC.estado_actual = 0;
      cambiar_estado = true;
    }
  }

  datosRTC.ciclos_latido++;
  bool toca_latido = (datosRTC.ciclos_latido >= CICLOS_LATIDO);

  // 5. Conectar WiFi y enviar a Firebase al iniciar, cambiar de estado o enviar latido
  if (primer_encendido || cambiar_estado || toca_latido) {
    Serial.println("Conectando WiFi para reportar a Firebase...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long inicio = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - inicio < 15000) {
      delay(100);
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("ERROR: Sin WiFi. Se reintentará al despertar.");
      if (cambiar_estado) datosRTC.estado_actual = (datosRTC.estado_actual == 1) ? 0 : 1;
      ESP.rtcUserMemoryWrite(0, (uint32_t*) &datosRTC, sizeof(datosRTC));
      dormir();
    }

    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    firebaseData.setBSSLBufferSize(1024, 1024);
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    datosRTC.latido++;
    String rutaBase = "/" + String(SENSOR_ID);
    String str_estado = (datosRTC.estado_actual == 1) ? "OCUPADO" : "LIBRE";

    bool okEstado = Firebase.setString(firebaseData, rutaBase + "/estado", str_estado);
    Firebase.setString(firebaseData, rutaBase + "/zona", ZONA_ID);
    Firebase.setInt(firebaseData, rutaBase + "/latido", datosRTC.latido);

    if (okEstado) {
      datosRTC.ciclos_latido = 0;
      Serial.println("OK -> Enviado: " + rutaBase + " = " + str_estado + " (latido " + String(datosRTC.latido) + ")");
    } else {
      Serial.println("ERROR Firebase: " + firebaseData.errorReason());
      if (cambiar_estado) datosRTC.estado_actual = (datosRTC.estado_actual == 1) ? 0 : 1;
    }

    WiFi.disconnect(true);
    delay(10);
  } else {
    Serial.println("Sin cambios. Volviendo a dormir.");
  }

  // 6. Guardar RTC y dormir
  ESP.rtcUserMemoryWrite(0, (uint32_t*) &datosRTC, sizeof(datosRTC));
  dormir();
}

void loop() {}