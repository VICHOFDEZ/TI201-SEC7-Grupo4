# Iteración 1 - Concepto Inicial

## Información General

**Fecha:** 06/09/2026
**Versión:** v1.0
**Estado:** Prototipo alpha - Prueba de concepto
**Avance asociado:** Planificación inicial / Avance #1

---

## Descripción

Primera versión del prototipo del sistema de monitoreo para el estacionamiento del edificio A-F-gimnasio de la universidad Adolfo Ibañez enfocada en validar la factibilidad técnica básica: detectar la presencia de un vehículo mediante un sensor de distancia y reflejar el cambio de estado ("Libre"/"Ocupado") en tiempo real en una interfaz web.

**Objetivo de esta iteración:**
- Probar la conexión y lectura de distancia con sensores en protoboard.
- Validar la comunicación WiFi del microcontrolador con Firebase Realtime Database.
- Demostrar el cambio de estado en tiempo real bajo un umbral de 50 cm .
- Levantar una primera página web sencilla para visualizar los datos recibidos.

---

## Componentes Utilizados

### Hardware
- Microcontrolador: ESP32 DevKit v1 (con módulo WiFi integrado)
- Sensores:
  - Sensor 1 (`/sensor_1`): Sensor de distancia láser ToF VL53L0X
  - Sensor 2 (`/sensor_2`): Sin uso
  *Solo se neciesito un sensor para ver la funcionalidad de los equipos. 
- Actuadores:
  - Indicadores visuales en interfaz web (verde = libre, rojo = ocupado)
- Otros: Protoboard, cables jumper, cable USB para alimentación y programación.

### Software
- IDE: Arduino IDE y Visual Studio Code
- Librerías: `WiFi.h`, librería de conexión a Firebase Realtime Database, librería del sensor de distancia y Firebase JS SDK v8.10.1
- Versión código: v1.0

---

## Fotos del Prototipo

Incluir en esta carpeta:
- `v1_circuito_protoboard.jpg`
- `v1_vista_general.jpg`
- `v1_detalle_conexiones.jpg`

---

## Resultados de Testing Inicial

### Funcionalidad Lograda
✅ Lectura de distancia en milímetros desde el sensor conectado en protoboard.
✅ Envío en tiempo real de los estados `LIBRE` y `OCUPADO` hacia Firebase Realtime Database.
✅ Visualización multi-sensor en una página web con actualización automática.
❌ Orientación espacial para el conductor (en esta etapa solo se mostraban tarjetas aisladas sin mapa del estacionamiento).

### Problemas Identificados

1. **Detección de pérdida de señal:**
   - Descripción: Si la placa perdía conexión WiFi o se apagaba, la página web mantenía visible el último estado guardado.
   - Causa probable: Ausencia de una señal periódica de actividad desde el microcontrolador.
   - Solución propuesta: Incorporar un contador de latido (`latido`) y tiempo de encendido (`uptime_s`) para marcar el sensor como "Sin señal" tras 10 segundos sin nuevos datos.

2. **Escalabilidad y experiencia de usuario en la web:**
   - Descripción: Mostrar únicamente tarjetas o puntos sueltos funciona para probar 1 o 2 sensores, pero no orienta a un estudiante cuando haya decenas o cientos de espacios.
   - Causa probable: Interfaz diseñada inicialmente solo para ver si esta libre o ocupado.
   - Solución propuesta: Desarrollar en la siguiente iteración con un sistema para detectar dos sensores a las vez y ver como se comportan.
---

## Aprendizajes

### Técnicos
- Firebase Realtime Database permite sincronizar el hardware y la web en tiempo real sin necesidad de montar un servidor backend propio.
- Definir un umbral fijo de 50 cm permite distinguir de forma estable entre espacio libre y ocupado en pruebas de escritorio.

### De Diseño
- Para un conductor que ingresa al campus, las métricas técnicas (milímetros exactos o señal dBm) son secundarias; lo prioritario es ver rápido qué pasillo tiene espacios disponibles.

---

## Plan para Iteración 2

### Mejoras Planificadas

**Hardware:**
- [ ] Consolidar pruebas simultáneas con múltiples sensores (`sensor_1`, `sensor_2`, etc.).
- [ ] Evaluar alimentación autónoma con batería para pruebas fuera del laboratorio.

**Software:**
- [ ] Implementar el uso de dos sensores para ver el comportamientos de ambos en uso simultaneo

**Diseño:**
- [ ] Iniciar diseño de encapsulado protector en impresión 3D.
- [ ] Mejorar ruteo de cables en el montaje físico.

---

## Archivos en esta Carpeta

- `v1_codigo.ino` - Código inicial del microcontrolador
- `v1_web.html` - Primera versión de la interfaz web
- `v1_fotos/` - Fotografías del montaje en protoboard