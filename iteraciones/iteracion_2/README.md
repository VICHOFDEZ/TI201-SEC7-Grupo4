# Iteración 2 - Sistema Multi-Sensor

## Información General

**Fecha:** xx/xx/2026
**Versión:** v2.0
**Estado:** Prototipo beta - Validación multi-sensor y UX web
**Avance asociado:** Avance #2

---

## Descripción

Segunda versión del prototipo del sistema de monitoreo para el estacionamiento de estudiantes de la Universidad Adolfo Ibáñez (sector bajo el Gimnasio / Edificios A–F). En esta iteración se escaló el sistema para operar con dos sensores simultáneos en tiempo real, se resolvió la detección de pérdida de señal.

**Objetivo de esta iteración:**
- Validar el funcionamiento simultáneo de dos placas (`sensor_1` y `sensor_2`) enviando datos en paralelo a Firebase.
- Incorporar un sistema de latido (*heartbeat*) para detectar automáticamente sensores desconectados o sin WiFi.
---

## Componentes Utilizados

### Hardware
- Microcontrolador: ESP32 DevKit v1 (x2 unidades con WiFi integrado)
- Sensores:
  - Sensor 1 (`/sensor_1`): Sensor de distancia láser ToF VL53L0X
  - Sensor 2 (`/sensor_2`): Sensor de distancia láser ToF VL53L0X

- Otros: Protoboards, cables jumper, alimentación USB / pruebas con batería externa.

### Software
- IDE: Arduino IDE y Visual Studio Code
- Librerías y herramientas:
  - Firmware: `WiFi.h`, librería de conexión a Firebase Realtime Database y librería del sensor VL53L0X
  - Web: Firebase JS SDK v8.10.1, Leaflet 1.9.4, capa satelital Esri World Imagery y *Deep Links* a Google Maps
- Versión código: v2.0

---

## Fotos del Prototipo

Incluir en esta carpeta:
- `v2_dos_sensores.jpg`
- `v2_mapa_satelital.png`
- `v2_modo_demo_zonas.png`

---

## Resultados de Testing

### Funcionalidad Lograda
✅ Operación simultánea y estable de 2 sensores (`sensor_1` y `sensor_2`) actualizando Firebase Realtime Database en tiempo real sin interferencias.
✅ Detección automática de pérdida de señal tras 10 segundos sin recibir un nuevo `latido` desde la placa.
❌ Pruebas prolongadas en exterior con encapsulado definitivo y alimentación solar/batería autónoma (pendiente para la siguiente iteración).

### Problemas Identificados

2. **Navegación fija a un solo punto en Google Maps:**
   - Descripción: Al principio el botón de Google Maps redirigía únicamente al primer punto disponible sin dejar elegir al usuario.
   - Causa probable: Lógica de redirección automática sin selector de preferencia.
   - Solución propuesta: Se agregó un selector de destino y selección directa por clic en el mapa o en las tarjetas de pasillo, permitiendo que el estudiante elija el espacio o pasillo que prefiera y abra la ruta exacta en Google Maps.

---

## Aprendizajes

### Técnicos
- Usar una capa satelital real con coordenadas GPS (`lat, lng`) garantiza que el punto mostrado en la web coincida exactamente con el destino enviado a Google Maps, sin necesidad de pagar API Keys.
- Agregar el campo `zona` en la estructura de datos de cada sensor permitirá escalar a cientos de dispositivos sin tener que listar manualmente cada uno en el código web.

### De Diseño
- Un modelo híbrido (**Zonas con semáforo + Pines individuales**) supera ampliamente a un mapa de solo puntos rojo/verde: evita saturar la pantalla cuando haya cientos de sensores y permite al conductor decidir hacia qué pasillo doblar en 2 segundos.

---

## Plan para Iteración 3

### Mejoras Planificadas

**Hardware:**
- [ ] Implementar alimentación autónoma (batería recargable + optimización de consumo con *deep sleep*).
- [ ] Realizar pruebas de campo en estacionamiento real bajo sol directo y distintas condiciones climáticas.

**Software:**
- [ ] Guardar las coordenadas GPS y la zona de cada sensor directamente en Firebase para facilitar el despliegue masivo.
- [ ] Incorporar filtrado temporal (histéresis) en el firmware para evitar falsos positivos causados por peatones.

**Diseño:**
- [ ] Fabricar encapsulado definitivo en impresión 3D resistente a la intemperie.
- [ ] Definir sistema de fijación física del módulo en el piso o tope de estacionamiento.

---

## Archivos en esta Carpeta

- `v2_codigo.ino` - Código multi-sensor del microcontrolador (con latido y umbral de 50 cm)
- `index.html` - Interfaz web con mapa satelital, 5 pasillos, semáforo y Google Maps
- `v2_fotos/` - Fotografías del montaje con dos sensores y capturas de la interfaz web
