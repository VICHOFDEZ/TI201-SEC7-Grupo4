# Historial de Iteraciones

## Propósito

Esta carpeta documenta la evolución del prototipo a través de las diferentes versiones desarrolladas durante el curso. Cada iteración tiene su propio README con el detalle completo.

---

## Estructura de Carpetas

```
iteraciones/
├── iteracion_1/    # Concepto inicial - Prototipo alpha (v1.0)
│   ├── v1_codigo/  #   v1_original (Versión 1), 01_sensor_basico
│   ├── v1_fotos/
│   └── v1_web.html
├── iteracion_2/    # Primera mejora - Avance #2 (v2.0)
│   ├── v2_codigo/  #   v2_mejorado (Versión 2), 01_sensor_basico, 02_prueba_diagnostico
│   ├── v2_fotos/
│   ├── v2_web.html
│   └── v2_web_dev_dashboard.html  # Consola del administrador
└── iteracion_3/    # Integración multi-sensor y modelo 3D - Avance #3 (v3.0)
    ├── v3_codigo/  #   01 a 04 + sensor_wifi_uai (+ diagnóstico)
    ├── v3_fotos/
    ├── v3_web_simple.html
    └── v3_web_satelital.html
```

---

## Tabla Comparativa de Iteraciones

| Aspecto | v1 | v2 | v3 |
|---------|----|----|----|
| **Fecha** | 06/09/2026 | 23/10/2026 | 22/11/2026 |
| **Microcontrolador** | 1 × NodeMCU ESP8266 | 1 × NodeMCU ESP8266 | 2 × NodeMCU ESP8266 |
| **Sensores** | 1 × VL53L0X | 1 × VL53L0X | 2 × VL53L0X |
| **Actuadores** | Indicador en web (verde/rojo) | Indicador en web (verde/rojo) | Mapa web + LED de la placa |
| **Conectividad** | WiFi → Firebase RTDB | WiFi → Firebase RTDB | WiFi / WPA2-Enterprise (UAI) → Firebase RTDB |
| **Encapsulado** | ❌ Protoboard | Prototipo de cartón | Impreso en 3D (PLA) |
| **Web** | Tarjetas básicas | Básica (sin cambios) | Mapa simple + mapa satelital |

---

## Evolución del Diseño

### Versión 1 (Iteración 1) — Concepto Inicial
**Fecha:** 06/09/2026 · **Estado:** Prototipo alpha — prueba de concepto
- Lectura de distancia con un VL53L0X en protoboard y envío de `LIBRE`/`OCUPADO` a Firebase con umbral de 50 cm.
- Problemas: la web mantenía el último estado si la placa se desconectaba; la interfaz no escalaba a muchos espacios.

### Versión 2 (Iteración 2) — Primera Mejora
**Fecha:** 23/10/2026 · **Estado:** Prototipo funcional con maqueta física
- Maqueta de cartón a escala real para validar volumen y abertura del sensor.
- Script de diagnóstico (`02_prueba_diagnostico`) para verificar sensor, WiFi y Firebase.
- Pendiente: inestabilidad WiFi e interfaz web sin orientación espacial.

### Versión 3 (Iteración 3) — Versión Final
**Fecha:** 22/11/2026 · **Estado:** En pruebas de integración
- Dos sensores operando en simultáneo (`/sensor_1`, `/sensor_2`).
- Filtro anti-falsas alarmas, latido y reconexión automática (`03_sensor_avanzado`), versión con Deep Sleep (`04_sensor_bajo_consumo`) y conexión a la red UAI con WPA2-Enterprise (`sensor_wifi_uai`).
- Encapsulado impreso en 3D (ver `diseño-3d/`).
- Web con mapa de puntos y propuesta satelital por pasillos.

---

## Justificación de Cambios

### Hardware
- **v1 → v2:** se adaptó el montaje del circuito a una maqueta de cartón para simular la posición real en el estacionamiento.
- **v2 → v3:** se agregó un segundo módulo de sensado y se reemplazó la maqueta por el encapsulado impreso en 3D.

### Software
- **v1 → v2:** validación del umbral de 50 cm y script de diagnóstico.
- **v2 → v3:** filtro por lecturas consecutivas, latido para detectar sensores desconectados, reconexión WiFi, Deep Sleep y soporte WPA2-Enterprise.

### Diseño 3D
- **v1 → v2:** primera maqueta de cartón.
- **v2 → v3:** iteraciones paramétricas en OpenSCAD (V7 → V16) y modelo/planos en Fusion 360.

---

## Incorporación de Feedback

### Feedback del Avance #2 → Cambios en v3
1. Pasar de 1 a múltiples sensores y evolucionar la interfaz web.
   - Acción tomada: segundo sensor armado y web con mapa del estacionamiento.
2. Reemplazar la maqueta de cartón por un encapsulado resistente y mejorar la conexión.
   - Acción tomada: encapsulado impreso en 3D y detección de pérdida de señal (latido).

### Feedback de Usuarios → Cambios en v3
- Ver `testing/` para los resultados de las sesiones con usuarios.

---

## Lecciones Aprendidas
- Firebase Realtime Database permite sincronizar hardware y web en tiempo real sin un backend propio.
- Para el conductor lo importante es ver rápido qué sector tiene espacios, no los datos técnicos (mm, dBm).
- Es necesario confirmar varias lecturas seguidas para evitar falsas alarmas (peatones).
