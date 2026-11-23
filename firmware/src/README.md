# Código Fuente
**Última edición:** 23 de noviembre de 2026

## Archivos Principales

El proyecto no utiliza un único `main.ino`, sino que está estructurado en versiones incrementales para facilitar el desarrollo, pruebas y despliegue final. Cada sketch está en una carpeta con su mismo nombre (requisito de Arduino IDE).

### Códigos de ESP8266 (.ino)
- `01_sensor_basico/01_sensor_basico.ino`: Versión inicial de prueba de concepto. Mide y envía a Firebase en bucle continuo.
- `02_prueba_diagnostico/02_prueba_diagnostico.ino`: Script de revisión paso a paso para verificar memoria RTC, sensor láser, WiFi y conexión a Firebase.
- `03_sensor_avanzado/03_sensor_avanzado.ino`: Versión con filtro anti-falsas alarmas, latido de red y envío condicional (para WiFi estándar).
- `04_sensor_bajo_consumo/04_sensor_bajo_consumo.ino`: Versión optimizada con Deep Sleep para funcionar con baterías (requiere puente D0–RST).
- `sensor_wifi_uai/sensor_wifi_uai.ino`: Código final para conectar a la red de la universidad ("UAI Alumnos") mediante WPA2-Enterprise.
- `sensor_wifi_uai_diagnostico/sensor_wifi_uai_diagnostico.ino`: Variante del Paso 3 usada en pruebas con el hotspot del celular (mismo código que `03_sensor_avanzado`, solo cambia la red WiFi).

Las versiones anteriores del firmware (Versión 1 `v1_original.ino` y Versión 2 `v2_mejorado.ino`) están en `iteraciones/iteracion_1/` e `iteraciones/iteracion_2/`.

> Las credenciales (`TU_WIFI`, `TU_CLAVE_WIFI`, `TU_FIREBASE_SECRET`, `usuario@alumnos.uai.cl`) están reemplazadas por marcadores. Completarlas localmente antes de subir el código a la placa y **no** hacer commit de las claves reales.

### Interfaces Web
Ubicadas en la carpeta [`../web/`](../web/):
- `05_web_basica.html`: Dashboard visual simple tipo semáforo (Verde = LIBRE, Rojo = OCUPADO).
- `06_web_consola_dev.html`: Panel para desarrolladores con datos JSON crudos de Firebase y log de eventos con timestamps.
- `07_web_presentacion.html`: Monitor en vivo usado para la presentación.
- `08_web_multisensor.html`: Panel visual para monitorear múltiples sensores al mismo tiempo.
- `09_web_mapa_uai.html`: Mapa simple del estacionamiento con puntos rojo/verde por sensor.
- `10_web_completo_maps.html`: Mapa satelital del sector Gimnasio (5 pasillos, semáforo de congestión y enlaces a Google Maps).
- `11_web_disponibilidad_v10.html`: Versión 10 (más reciente) de la página de disponibilidad sobre el mapa.
- `12_mapa_cliente.html`: Vista de disponibilidad para el usuario final, sobre `estacionamiento_base.jpg`.
- `13_marcador_plazas.html`: Herramienta para marcar la posición de cada plaza sobre `estacionamiento_base.jpg`.
- `estacionamiento_base.jpg`: Imagen aérea del estacionamiento usada por los archivos 12 y 13.

---

## Estándares de Código

### Comentarios
El código está documentado en español para facilitar su lectura y comprensión académica:
```cpp
// Comentarios en español
// Explicar QUÉ hace y POR QUÉ (no solo el CÓMO)

/**
 * Función: leerSensor
 * Descripción: Realiza una medición de distancia con el VL53L0X y descarta lecturas inválidas.
 * Retorna: bool - true si hay un auto a menos de 500mm, false si está libre.
 */
bool leerSensor() {
  // código
}
```

### Nombres de Variables
- **Variables:** `camelCase` (ej. `distanciaMm`, `cambioEstadoS`)
- **Constantes:** `UPPER_SNAKE_CASE` (ej. `UMBRAL_MM`, `INTERVALO_LECTURA_MS`)
- **Funciones:** `camelCase()` (ej. `actualizarEstado()`)

---

## Testing y Debugging

### Monitor Serial
Para visualizar el comportamiento del ESP8266 en tiempo real, se debe utilizar el Monitor Serie del Arduino IDE por conexión USB:
- **Baudrate:** `115200` baudios.

### Formato de Mensajes de Debugging
El sistema envía indicadores visuales claros a través del terminal en lugar de prefijos estándar:
- **Inicialización:** `=== Estacionamiento UAI - Sensor avanzado ===`
- **Estados OK:** `-> Firebase OK` o `-> Enviado a Firebase`
- **Transiciones y Alertas:** `>>> AUTO DETECTADO -> OCUPADO`
- **Errores:** `Error de sensor láser. Revisa cables D1 (SCL) y D2 (SDA).`