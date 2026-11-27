# Fuentes, librerías y uso de IA

Este documento declara todo el material externo utilizado en el proyecto: librerías, código de terceros, herramientas, recursos gráficos y uso de inteligencia artificial.

---

## 1. Librerías del firmware (ESP8266)

| Librería | Autor / Fuente | Licencia | Uso en el proyecto |
|---|---|---|---|
| ESP8266 Arduino Core (`ESP8266WiFi.h`, `Wire.h`) | ESP8266 Community — https://github.com/esp8266/Arduino | LGPL-2.1 | Conexión WiFi y bus I2C |
| `wpa2_enterprise.h` (SDK de Espressif, incluido en el core) | Espressif Systems | Apache-2.0 / incluida en el core | Conexión a la red WPA2-Enterprise "UAI Alumnos" (`sensor_wifi_uai.ino`) |
| Firebase ESP8266 Client (`FirebaseESP8266.h`) | Mobizt — https://github.com/mobizt/Firebase-ESP8266 | MIT | Envío de estados a Firebase Realtime Database |
| Adafruit VL53L0X (`Adafruit_VL53L0X.h`) | Adafruit Industries — https://github.com/adafruit/Adafruit_VL53L0X | BSD | Lectura del sensor láser de distancia |

## 2. Librerías y servicios de las páginas web

| Recurso | Fuente | Uso |
|---|---|---|
| Firebase JavaScript SDK v8.10.1 | Google — `https://www.gstatic.com/firebasejs/8.10.1/` | Lectura en tiempo real de los estados de los sensores |
| Firebase Realtime Database | Google Firebase | Base de datos en la nube (`estacionamiento-uai-default-rtdb`) |
| Leaflet 1.9.4 | https://leafletjs.com (BSD-2-Clause) | Mapa interactivo en `10_web_completo_maps.html` |
| Esri World Imagery (ArcGIS Online) | `server.arcgisonline.com` | Capa satelital del mapa en `10_web_completo_maps.html` |
| Google Maps (enlaces de direcciones) | `google.com/maps/dir` | Botón "cómo llegar" a cada sector |

## 3. Herramientas de diseño

| Herramienta | Uso |
|---|---|
| Arduino IDE 2.x | Programación del ESP8266 |
| circuito.io — https://www.circuito.io/app?components=11856,219866,360216 | Esquema del circuito (`hardware/esquemas/`) |
| OpenSCAD | Modelado paramétrico del encapsulado (`diseño-3d/openscad/`) |
| Autodesk Fusion 360 (licencia educacional) | Modelo final, renders y planos (`diseño-3d/`) |

## 4. Código externo y plantillas

| Material | Origen | Licencia | Uso |
|---|---|---|---|
| Estructura de carpetas y READMEs base del repositorio | Plantilla del curso TEI201 (autor: sebasdv) | MIT | Punto de partida de la documentación |
| Ejemplos oficiales de las librerías (Firebase ESP8266 Client, Adafruit VL53L0X) | Repositorios oficiales indicados arriba | MIT / BSD | Referencia para la inicialización del sensor y de Firebase |

## 5. Recursos gráficos

| Archivo | Origen |
|---|---|
| Fotos en `hardware/fotos/`, `iteraciones/*/v*_fotos/`, `testing/evidencias/` | Tomadas por el equipo |
| Renders y planos en `diseño-3d/` | Generados por el equipo en Fusion 360 |
| `firmware/web/estacionamiento_base.jpg` | 
| `hardware/esquemas/circuito_completo.jpeg` | 

## 6. Uso de Inteligencia Artificial

| Herramienta | Para qué se usó | Archivos afectados |
|---|---|---|
| Claude (Anthropic) | Revisión y reorganización de la estructura del repositorio, corrección de nombres de archivos y actualización de los README (noviembre 2026) | READMEs, `FUENTES.md` |
 | **[Ej.: apoyo en la escritura/comentarios del código .ino, páginas web, textos de documentación]** |

> Todo el contenido generado o asistido por IA fue revisado y validado por los integrantes del equipo.
