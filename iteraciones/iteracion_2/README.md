# Iteración 2 - Primera Mejora Significativa

## Información General

**Fecha:** 23/10/2026  
**Versión:** v2.0  
**Estado:** Prototipo funcional con maqueta física (Avance #2)  
**Avance asociado:** Avance #2

---

## Descripción

Segunda versión del prototipo presentada en el Avance #2 del curso. En esta etapa se mantuvo la operación con un solo sensor de distancia (50 cm de alcance) y la página web básica de la iteración anterior, incorporando un primer prototipo físico de cartón para validar las dimensiones y el concepto de lo que será el encapsulado en 3D.

**Objetivos de esta iteración:**
- Realizar la presentación del Avance #2 planificada en el curso.
- Revalidar el funcionamiento del sensor y su alcance de 50 cm en pruebas en vivo.
- Construir una maqueta de cartón que represente la forma y el calce del futuro modelo 3D.
- Identificar mejoras críticas de conectividad, escalabilidad y visualización web para la versión final.

---

## Cambios Respecto a v1

### Hardware
**Agregado:**
- Ningún componente electrónico nuevo (se continuó trabajando con 1 placa NodeMCU ESP8266 y 1 sensor VL53L0X).

**Modificado:**
- Montaje físico del circuito - Razón: adaptarlo dentro de la maqueta de cartón para simular su posición real en el estacionamiento.

**Removido:**
- Ninguno.

### Software
**Nuevas funcionalidades:**
- Se mantuvo la misma interfaz web básica de la Iteración 1, enfocada únicamente en mostrar el estado del sensor en tiempo real.

**Optimizaciones:**
- Validación continua del umbral de detección a 50 cm.
- Versión 2 del firmware (`v2_mejorado.ino`): Deep Sleep con la radio apagada al despertar y espera máxima de 15 s para el WiFi, para reducir el consumo de batería.

**Bugs corregidos:**
- Ninguno mayor en software; se priorizó la validación de la presentación y el prototipo físico.

### Diseño Mecánico
- Construcción de un **prototipo de cartón** a escala real para representar lo que será el encapsulado impreso en 3D.
- Evaluación inicial de la abertura para el sensor láser y el espacio interno para la placa y cables.

---

## Fotos del Prototipo v2

En la carpeta `v2_fotos/`:
- `v2_prototipo_carton.png`
- `v2_circuito_integrado.png`

*Aclaración: No usamos una presentación como tal para exponer en esta evaluación dos, por eso no hay foto de presentación.*
---

## Resultados de Testing

### Funcionalidad Lograda
✅ El sensor funciona correctamente y detecta cambios de estado (`LIBRE` / `OCUPADO`) dentro del rango de 50 cm.  
✅ Presentación del Avance #2 completada según lo planificado en el curso.  
✅ Validación física del volumen y geometría básica mediante el prototipo de cartón.  
⚠️ Conexión WiFi inestable en determinados momentos durante las pruebas.  
⚠️ Interfaz web aún demasiado básica para orientar a un conductor real.

### Feedback del Avance #2

**Comentarios del profesor/ayudante:**
1. Es necesario dar el salto de 1 sensor a múltiples sensores simultáneos y evolucionar la interfaz web para que sea útil en un estacionamiento real.
   - Acción: Armar el segundo sensor y rediseñar la web evaluando nuevas formas de visualización espacial para la v3.

2. Pasar de la maqueta de cartón a un encapsulado resistente y mejorar la estabilidad de la conexión.
   - Acción: Modelar e imprimir la carcasa en 3D y agregar detección de pérdida de señal WiFi en la v3.

---

## Problemas Pendientes

1. **Inestabilidad en la conexión WiFi:**
   - Descripción: En ciertos momentos la placa pierde conexión con la red WiFi, interrumpiendo la actualización de datos en tiempo real.
   - Prioridad: Alta
   - Plan para v3: Implementar reconexión automática en el firmware y un indicador de "Sin señal" en la web cuando el sensor deje de enviar latidos.

2. **Interfaz web básica y falta de orientación espacial:**
   - Descripción: La web actual sigue siendo igual de básica que en la Iteración 1 y no permite saber en qué lugar físico del campus se encuentra el espacio libre.
   - Prioridad: Alta
   - Plan para v3: Evaluar e implementar un nuevo diseño web (comparando dos modelos propuestos: un mapa simple de puntos rojo/verde vs. un mapa satelital completo por pasillos con semáforo y Google Maps).

3. **Cómo vincular la ubicación física con la señal del sensor:**
   - Descripción: Al proyectar el sistema a múltiples espacios, surge el desafío de definir la mejor forma de visualizar el funcionamiento de cada sensor: si basta con asociar su ubicación fija y, a partir de la señal recibida, mostrar dónde está y si se encuentra ocupado o libre.
   - Prioridad: Alta
   - Plan para v3: Definir una arquitectura de mapeo (coordenadas asociadas a cada ID de sensor) que permita escalar de 2 sensores a decenas sin saturar al usuario.

---

## Comparación v1 vs v2

| Aspecto | v1 | v2 | Evolución |
|---------|----|----|-----------|
| Sensores activos | 1 | 1 | Igual (validación) |
| Alcance de detección | 50 cm | 50 cm | Estable ✅ |
| Estabilidad WiFi | Funcional | Con cortes intermitentes | Por mejorar ⚠️ |
| Interfaz web | Básica | Básica (sin cambios) | Pendiente v3 |
| Encapsulado | ❌ Sin carcasa | Prototipo de cartón | ✅ Primer avance físico |

---

## Plan para Iteración 3 (Versión Final)

### Mejoras Críticas

**Hardware:**
- [ ] Armar e integrar el **segundo sensor** para operar ambos en simultáneo.
- [ ] Mejorar la estabilidad de la conexión WiFi y probar alimentación autónoma.

**Software:**
- [ ] Mejorar la página web evaluando los **dos modelos de interfaz** desarrollados:
  - *Modelo A (Simple):* Mapa dentro de la web con puntos rojo/verde por sensor.
  - *Modelo B (Completo):* Mapa satelital real del sector Gimnasio dividido en 5 pasillos con semáforo de congestión (verde, amarillo, rojo) y conexión directa a Google Maps.
- [ ] Definir el método de visualización de sensores basado en su ubicación y señal de estado (saber dónde está ubicado cada sensor y si está libre u ocupado).

**Diseño:**
- [ ] Pasar del prototipo de cartón al diseño 3D definitivo del encapsulado.
- [ ] Mejorar el ruteo interno de cables y el sistema de montaje.

**Testing:**
- [ ] Validar el funcionamiento simultáneo de los 2 sensores en la nueva interfaz web.
- [ ] Realizar pruebas con estudiantes para elegir la mejor experiencia de usuario.

---

## Archivos en esta Carpeta

- `v2_codigo/v2_mejorado/v2_mejorado.ino` - **Versión 2 (mejorada)**: Deep Sleep optimizado (radio apagada al despertar, WiFi no persistente, espera máxima de 15 s para conectar)
- `v2_codigo/01_sensor_basico/` y `v2_codigo/02_prueba_diagnostico/` - Código de prueba y diagnóstico utilizado en el Avance #2
- `v2_web.html` - Interfaz web básica utilizada en la presentación
- `v2_web_dev_dashboard.html` - Segunda página web: consola para el administrador (estado, datos crudos de Firebase y registro de eventos)
- `v2_fotos/` - Fotografías del prototipo de cartón y pruebas de la presentación