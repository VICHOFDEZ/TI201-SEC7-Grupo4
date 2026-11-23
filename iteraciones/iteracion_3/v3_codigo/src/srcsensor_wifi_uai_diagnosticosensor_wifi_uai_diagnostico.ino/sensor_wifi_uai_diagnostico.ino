/*
 * ====================================================================
 *  ESTACIONAMIENTO UAI  -  Versión 2 : SENSOR AVANZADO (SIN DEEP SLEEP)
 * ====================================================================
 */

// ---------------------------- LIBRERÍAS -----------------------------
#include <ESP8266WiFi.h>        // Conexión WiFi normal
#include <FirebaseESP8266.h>    // Conexión con Firebase
#include <Wire.h>               // Comunicación I2C
#include "Adafruit_VL53L0X.h"   // Sensor láser VL53L0X

// -------------------- DATOS DE CONEXIÓN (EDITAR) --------------------
// IMPORTANTE: Asegúrate de usar una red normal, como el hotspot de tu celular
#define WIFI_SSID      "Galaxy S22 EF1A"  
#define WIFI_PASSWORD  "Mateo123" 
#define FIREBASE_HOST  "estacionamiento-uai-default-rtdb.firebaseio.com"  
#define FIREBASE_AUTH  "eENfltqnIqbYBDkdx2N3JuyC5FqohPTF8qhY7KZv"        

// --------------------------- PINES ----------------------------------
#define PIN_SDA D2              
#define PIN_SCL D1              
#define PIN_LED LED_BUILTIN     

// ------------------------ AJUSTES -----------------------------------
#define UMBRAL_MM             500    
#define INTERVALO_LECTURA_MS  1000   
#define INTERVALO_LATIDO_MS   2000   
#define CONFIRMA_OCUPADO      4      
#define CONFIRMA_LIBRE        3      
#define RUTA_SENSOR           "/sensor_1"   

// ------------------------ OBJETOS GLOBALES --------------------------
Adafruit_VL53L0X lox = Adafruit_VL53L0X();  
FirebaseData firebaseData;                  
FirebaseAuth auth;                          
FirebaseConfig config;                      

// ------------------------ VARIABLES DE ESTADO -----------------------
bool ocupado = false;               
int  contOcupado = 0;               
int  contLibre   = 0;               
int  distanciaMm = -1;              
unsigned long cambioEstadoS = 0;    
unsigned long latido = 0;           
unsigned long tUltimaLectura = 0;   
unsigned long tUltimoLatido  = 0;   
unsigned long tIntentoWiFi   = 0;   

// ====================================================================
//  FUNCIONES AUXILIARES
// ====================================================================

void actualizarLed() {
  digitalWrite(PIN_LED, ocupado ? LOW : HIGH);   
}

void iniciarSensor() {
  while (!lox.begin()) {
    Serial.println("Error de sensor láser. Revisa cables D1 (SCL) y D2 (SDA). Reintentando...");
    digitalWrite(PIN_LED, LOW);  delay(100);     
    digitalWrite(PIN_LED, HIGH); delay(400);
  }
  Serial.println("Sensor láser OK");
}

void conectarWiFi() {
  Serial.print("Conectando a WiFi normal");
  WiFi.mode(WIFI_STA);                 
  WiFi.disconnect(true);               // Limpia memoria de conexiones fallidas previas
  delay(100);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(PIN_LED, !digitalRead(PIN_LED));   
    delay(250);
    Serial.print(".");
  }
  WiFi.setAutoReconnect(true);         
  digitalWrite(PIN_LED, HIGH);         
  Serial.println();
  Serial.print("WiFi conectado. IP: ");
  Serial.println(WiFi.localIP());
}

bool wifiListo() {
  if (WiFi.status() == WL_CONNECTED) return true;
  if (millis() - tIntentoWiFi > 5000) {
    tIntentoWiFi = millis();
    Serial.println("WiFi caído, reintentando...");
    WiFi.reconnect();
  }
  return false;
}

bool leerSensor() {
  VL53L0X_RangingMeasurementData_t medida;
  lox.rangingTest(&medida, false);

  if (medida.RangeStatus == 4) {       
    distanciaMm = -1;
    return false;
  }
  distanciaMm = medida.RangeMilliMeter;
  return distanciaMm < UMBRAL_MM;      
}

bool actualizarEstado(bool autoDetectado) {
  if (autoDetectado) {
    contOcupado++;                     
    contLibre = 0;                     
    if (!ocupado && contOcupado >= CONFIRMA_OCUPADO) {
      ocupado = true;                  
      return true;
    }
  } else {
    contLibre++;
    contOcupado = 0;
    if (ocupado && contLibre >= CONFIRMA_LIBRE) {
      ocupado = false;                 
      return true;
    }
  }
  return false;                        
}

void publicar() {
  if (!wifiListo()) return;            

  latido++;                            

  FirebaseJson json;                   
  json.set("estado",       String(ocupado ? "OCUPADO" : "LIBRE"));
  json.set("distancia_mm", distanciaMm);                 
  json.set("rssi",         (int)WiFi.RSSI());            
  json.set("uptime_s",     (int)(millis() / 1000));      
  json.set("cambio_s",     (int)cambioEstadoS);          
  json.set("latido",       (int)latido);                 

  if (Firebase.updateNode(firebaseData, RUTA_SENSOR, json)) {
    Serial.println("   -> Enviado a Firebase");
  } else {
    Serial.print("   -> Error Firebase: ");
    Serial.println(firebaseData.errorReason());
  }

  tUltimoLatido = millis();            
}

// ====================================================================
//  setup()
// ====================================================================
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n=== Estacionamiento UAI - Sensor avanzado ===");

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);         

  Wire.begin(PIN_SDA, PIN_SCL);        

  iniciarSensor();                     
  conectarWiFi();                      

  config.host = FIREBASE_HOST;         
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  int conAuto = 0;
  for (int i = 0; i < 3; i++) {
    if (leerSensor()) conAuto++;
    delay(100);
  }
  ocupado = (conAuto >= 2);
  if (ocupado) contOcupado = CONFIRMA_OCUPADO; else contLibre = CONFIRMA_LIBRE;
  cambioEstadoS = millis() / 1000;
  actualizarLed();

  publicar();                          
  Serial.println("Sistema listo. Monitoreando...");
}

// ====================================================================
//  loop()
// ====================================================================
void loop() {
  unsigned long ahora = millis();

  if (ahora - tUltimaLectura >= INTERVALO_LECTURA_MS) {
    tUltimaLectura = ahora;

    bool autoDetectado = leerSensor();
    bool cambio = actualizarEstado(autoDetectado);

    Serial.print("Distancia: ");
    if (distanciaMm < 0) Serial.print("fuera de rango");
    else { Serial.print(distanciaMm); Serial.print(" mm"); }
    Serial.print(" | Estado: ");
    Serial.println(ocupado ? "OCUPADO" : "LIBRE");

    if (cambio) {                      
      cambioEstadoS = millis() / 1000;
      actualizarLed();
      Serial.println(ocupado ? ">>> AUTO DETECTADO -> OCUPADO" : ">>> ESPACIO VACÍO -> LIBRE");
      publicar();
    }
  }

  if (millis() - tUltimoLatido >= INTERVALO_LATIDO_MS) {
    publicar();
  }
}