# Documentación de Software
**Última edición:** 28 de octubre de 2026

## Contenido

### Diagramas de Flujo
El flujo principal del sistema sigue esta secuencia lógica continua:
1. **Lectura I2C:** El ESP8266 solicita la distancia al sensor VL53L0X.
2. **Filtrado:** Se compara la distancia con el `UMBRAL_MM` (500 mm). Si es menor, detecta un auto.
3. **Validación:** El estado solo cambia si se confirman 4 lecturas seguidas de "auto detectado" o 3 lecturas de "espacio vacío", evitando falsos positivos por peatones.
4. **Transmisión:** Si hay un cambio confirmado, se activa la conexión WiFi y se publica el estado al instante en Firebase. Adicionalmente, se envía un "latido" de vida cada 2 segundos.
5. **Ahorro de Energía (Modo Deep Sleep):** Tras publicar o confirmar que no hay cambios, el microcontrolador entra en suspensión, delegando los contadores a la memoria RTC.

---

### Documentación de Funciones

#### Funciones Principales

**leerSensor()**
- **Propósito:** Realiza una medición de distancia mediante el sensor láser de tiempo de vuelo.
- **Parámetros:** Ninguno.
- **Retorna:** `boolean` - `true` si detecta un objeto a menos de 500 mm y la medición es válida; `false` si el objeto está más lejos o fuera de rango.
- **Ejemplo de uso:**
```cpp
bool autoDetectado = leerSensor();
```

**actualizarEstado()**
- **Propósito:** Aplica un filtro anti-falsas-alarmas. Acumula lecturas consecutivas para confirmar una transición real de estado.
- **Parámetros:** `bool autoDetectado` - Resultado de la última medición del sensor.
- **Retorna:** `boolean` - `true` si el estado consolidado cambió (de LIBRE a OCUPADO o viceversa); `false` si se mantiene en el estado actual.
- **Ejemplo de uso:**
```cpp
bool cambio = actualizarEstado(autoDetectado);
if (cambio) { publicar(); }
```

**publicar()**
- **Propósito:** Empaqueta los datos telemétricos y los envía a Firebase Realtime Database.
- **Parámetros:** Ninguno. Utiliza variables globales de estado.
- **Retorna:** `void`.
- **Ejemplo de uso:**
```cpp
if (millis() - tUltimoLatido >= INTERVALO_LATIDO_MS) {
    publicar();
}
```

---

## Manual de Instalación

1. **Clonar repositorio:** Descarga los archivos locales del proyecto.
2. **Preparar Arduino IDE:** Instala el soporte para placas ESP8266 y las librerías necesarias (`FirebaseESP8266`, `Adafruit_VL53L0X`).
3. **Configurar Credenciales:** Abre el código fuente y edita las variables `WIFI_SSID`, `WIFI_PASSWORD` y `FIREBASE_AUTH`. Para pruebas en la universidad, utiliza el script con configuración WPA2-Enterprise (`wpa2_enterprise.h`).
4. **Conexión de Hardware:** Asegúrate de que los pines I2C del VL53L0X estén conectados a D1 (SCL) y D2 (SDA) del ESP8266. En el modelo de Deep Sleep, puentea el pin D0 con RST.
5. **Carga y Verificación:** Conecta la placa por USB, compila el código y verifica el Monitor Serie (115200 baudios) para confirmar la conexión a Firebase.

---

## Manual de Operación

### Encendido del Sistema
1. Conectar el ESP8266 a su fuente de alimentación (Batería LiPo o cable USB).
2. Observar el LED integrado de la placa; si parpadea, está intentando conectarse a la red WiFi.
3. Una vez conectado, el sistema realizará 3 lecturas rápidas de calibración para determinar su estado inicial sin falsos positivos.

### Operación Normal
1. El sensor medirá automáticamente la plaza de estacionamiento según el intervalo configurado.
2. **Monitorización Básica:** Abrir el archivo `05_web_basica.html` en el navegador para ver un panel semafórico (Verde = LIBRE, Rojo = OCUPADO) que reacciona en tiempo real.
3. **Monitorización Técnica:** Abrir `06_web_consola_dev.html` para auditar latencias, señal RSSI, distancia en milímetros, y un log detallado de transiciones de estado y horas exactas.

### Apagado del Sistema
1. Desconectar físicamente la fuente de energía del ESP8266.
2. El dashboard web dejará de recibir el "latido", indicando que el nodo está fuera de línea.

---

## Troubleshooting

### Problemas Comunes

**Problema 1: No conecta a WiFi**
- **Causa probable:** Credenciales incorrectas, router configurado solo en 5GHz (el ESP8266 solo soporta 2.4GHz), o problemas con el certificado de la red Enterprise de la universidad.
- **Solución:** Verificar que la variable `WIFI_SSID` apunte a una red 2.4GHz. Si se usa la red "UAI Alumnos", confirmar que las credenciales WPA2-Enterprise estén actualizadas en el código.

**Problema 2: Sensor no responde ("Error de sensor láser")**
- **Causa probable:** Cables invertidos, desconectados, o falta de energía en el bus I2C.
- **Solución:** Confirmar que SCL vaya obligatoriamente al pin D1 y SDA al pin D2. Verificar que el pin VIN del sensor reciba los 3.3V de la placa.

**Problema 3: Falsos positivos constantes**
- **Causa probable:** Lente del láser sucio o umbral de detección (`UMBRAL_MM`) configurado con un valor excesivo que detecta el suelo.
- **Solución:** Limpiar el emisor/receptor del sensor VL53L0X. Reducir el valor de la variable de 500 mm a 400 mm si el gabinete 3D está instalado muy bajo.