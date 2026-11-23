# Iteración 3 - Integración Multi-Sensor y Modelo 3D

## Información General

**Fecha:** 22/11/2026  
**Versión:** v3.0  
**Estado:** En pruebas de integración  
**Avance asociado:** Avance #3 / Versión Final

---

## Descripción

Tercera iteración del prototipo del sistema de monitoreo para el estacionamiento de la Universidad Adolfo Ibáñez (sector Edificios A–F y Gimnasio). En esta etapa se completó el armado de los dos sensores operando en conjunto, se diseñó el modelo 3D definitivo del encapsulado y se obtuvieron pruebas positivas con la interfaz web basada en mapa de puntos, mientras se evalúa la integración de la versión web avanzada con vista satelital por pasillos y Google Maps.

**Objetivos de esta iteración:**
- Completar la construcción y puesta en marcha de los dos sensores en simultáneo (`sensor_1` y `sensor_2`).
- Validar el funcionamiento conjunto de ambos sensores en la plataforma web.
- Pasar del prototipo de cartón al modelo 3D del encapsulado.
- Evaluar la migración hacia la interfaz web completa (mapa satelital por zonas y Google Maps) y optimizar el consumo energético.

---

## Cambios Respecto a v2

### Hardware
**Agregado:**
- Segundo módulo completo de sensado (NodeMCU ESP8266 + sensor de distancia láser ToF VL53L0X).

**Modificado:**
- Integración física de los componentes - Razón: preparar el montaje definitivo dentro de la carcasa 3D.

**Removido:**
- Maqueta de cartón utilizada en el Avance #2 - Razón: reemplazada por el modelo 3D.

### Software
**Nuevas funcionalidades:**
- Pruebas exitosas de los dos sensores en la interfaz web con mapa simple (visualización por punto rojo/verde).
- Desarrollo paralelo de un segundo modelo de interfaz web (mapa satelital real de los 5 pasillos de estudiantes, semáforo de congestión y enlaces directos a Google Maps), actualmente en evaluación de implementación.

**Optimizaciones:**
- Validación de lectura simultánea sin interferencia entre nodos en Firebase Realtime Database.

**Bugs corregidos:**
- Estabilización del envío de datos desde dos placas hacia la base de datos en tiempo real.

### Diseño Mecánico
- **Modelo 3D realizado** para el encapsulado protector del circuito y el sensor, reemplazando el prototipo de cartón de la Iteración 2.

---

## Fotos del Prototipo v3

En la carpeta `v3_fotos/`:
- `v3_dos_sensores.png`
- `v3_encapsulado_cerrado.png`
- `v3_encapsulado_abierto.png`

---

## Resultados de Testing

### Funcionalidad Lograda
✅ Dos sensores armados y operativos.  
✅ Pruebas positivas de detección y visualización en la página web de mapa simple (punto rojo/verde).  
✅ Modelo 3D del encapsulado completado.  
⚠️ Evaluación en curso para implementar la segunda propuesta de página web (mapa satelital por pasillos + Google Maps).  
❌ Modo de bajo consumo (*deep sleep*) del sensor para ahorro de batería aún sin resolver.

---

## Problemas Pendientes

1. **Modo de ahorro de batería (*Deep Sleep*) no resuelto:**
   - Descripción: No se ha logrado implementar correctamente la función para que el sensor/microcontrolador entre en modo reposo y despierte periódicamente sin perder estabilidad en la conexión o en las lecturas.
   - Prioridad: Alta
   - Plan de acción: Revisar la rutina de *deep sleep* en el ESP8266 (despertar por temporizador cada ciertos segundos, medir, enviar a Firebase y volver a dormir) para reducir el consumo energético en operación con batería.

2. **Integración de la interfaz web avanzada:**
   - Descripción: Aunque la web simple de un punto ya arroja pruebas positivas, aún se está evaluando cómo integrar el segundo modelo de web (mapa satelital con 5 pasillos, semáforo y Google Maps) con los datos reales de los sensores.
   - Prioridad: Media
   - Plan de acción: Conectar las rutas `/sensor_1` y `/sensor_2` de Firebase a la interfaz satelital y definir cuál modelo se presentará como versión final.

3. **Pruebas integrales del sistema completo:**
   - Descripción: Queda pendiente probar todos los elementos funcionando en conjunto (2 sensores + encapsulado 3D + web definitiva) de forma continua.
   - Prioridad: Alta
   - Plan de acción: Ejecutar una jornada de pruebas integradas simulando el uso real en estacionamiento.

---

## Comparación v2 vs v3

| Aspecto | v2 | v3 | Evolución |
|---------|----|----|-----------|
| Sensores armados | 1 | 2 | ✅ +100% |
| Interfaz web | Básica (sin mapa) | Mapa simple probado ✅ + Mapa satelital en evaluación | ✅ |
| Encapsulado | Prototipo de cartón | Modelo 3D realizado | ✅ |
| Ahorro de batería (*Deep Sleep*) | ❌ | ❌ (pendiente) | En desarrollo ⚠️ |

---

## Próximos Pasos (Cierre de Pruebas)

- [ ] Completar pruebas de funcionamiento de todo el sistema en conjunto (hardware + encapsulado 3D + web).
- [ ] Definir e implementar la integración final de la página web avanzada (mapa satelital + Google Maps).
- [ ] Solucionar la rutina de reposo (*deep sleep*) en el firmware para optimizar la duración de la batería.

---

## Archivos en esta Carpeta

- `v3_codigo/` - Código de esta iteración (`01_sensor_basico`, `02_prueba_diagnostico`, `03_sensor_avanzado`, `04_sensor_bajo_consumo`, `sensor_wifi_uai`, `sensor_wifi_uai_diagnostico`). La versión más actualizada de cada sketch está en [`firmware/src/`](../../firmware/src/README.md).
- `v3_web_simple.html` - Página web con mapa de puntos (pruebas positivas)
- `v3_web_satelital.html` - Propuesta de página web con mapa satelital, 5 pasillos y Google Maps
- `v3_fotos/` - Fotografías de los dos sensores y del encapsulado impreso
- Modelo 3D del encapsulado: ver [`diseño-3d/`](../../diseño-3d/README.md) (`fusion360/modelo_completo_v3.f3d` y `openscad/Version_10.scad`)