# Estacionamiento UAI — Sensor IoT de disponibilidad de estacionamientos

**Curso:** TEI201 — Sección 7 — Grupo 4 · Facultad de Ingeniería y Ciencias · Universidad Adolfo Ibáñez
**Repositorio:** https://github.com/VICHOFDEZ/TI201-SEC7-Grupo4

---

## Información del Equipo

| Integrante | Rol principal |
|---|---|
| Gaspar Rosales | Diseño 3D |
| Vicente Fernández | Software / Web |
| Renato Díaz | Hardware |
| Mateo Soliz | Hardware |

- **ODS seleccionado:** ODS 11 — Ciudades y comunidades sostenibles
- **Problema a resolver:** En la Universidad Adolfo Ibáñez no existe información en tiempo real sobre la disponibilidad de estacionamientos en los distintos sectores del campus. Los conductores dan vueltas buscando un espacio libre, lo que genera pérdida de tiempo, congestión y emisiones innecesarias.

---

## Descripción del Proyecto

Diseñamos un sistema IoT compuesto por un sensor que se instala en cada cajón de estacionamiento. Un sensor de distancia láser **VL53L0X** conectado a una placa **NodeMCU ESP8266** detecta si hay un vehículo sobre el dispositivo. Cuando el cambio se confirma (filtro anti-falsas alarmas), la placa publica el estado (`LIBRE` / `OCUPADO`) en **Firebase Realtime Database**, y una página web muestra en tiempo real qué espacios están disponibles sobre un mapa del estacionamiento.

El dispositivo va dentro de un encapsulado impreso en 3D (PLA), alimentado por una batería 18650 recargable.

---

## Estado del Proyecto

- **Versión actual:** Iteración 3 — Avance #3 / entrega final
- **Última actualización:** 23/11/2026
- **Estado:** Prototipo funcional en pruebas de integración (2 sensores + encapsulado 3D + web)

---

## Estructura del Repositorio

```
├── firmware/       # Código del ESP8266 (.ino), páginas web y librerías
│   ├── src/        #   Sketches de Arduino (cada uno en su carpeta)
│   ├── web/        #   Interfaces web conectadas a Firebase
│   ├── librerias/  #   Librerías necesarias
│   └── docs/       #   Manual de instalación, operación y funciones
├── hardware/       # Esquemas del circuito, BOM y fotos del prototipo
├── diseño-3d/      # Modelos OpenSCAD / Fusion 360, STL, renders y planos
├── testing/        # Datos, evidencias y reportes de validación con usuarios
├── docs/           # Reporte final y presentación
├── iteraciones/    # Historial de las versiones v1, v2 y v3
├── FUENTES.md      # Librerías, código externo y uso de IA declarados
└── LICENSE
```

---

## Inicio Rápido

### Requisitos
- [Arduino IDE 2.x](https://www.arduino.cc/en/software)
- Paquete de placas **ESP8266** (NodeMCU 1.0 ESP-12E)
- Librerías: **Firebase ESP8266 Client** (Mobizt) y **Adafruit VL53L0X**
- Navegador web moderno (para las interfaces web)
- OpenSCAD y/o Autodesk Fusion 360 (solo para abrir los modelos 3D)

### Instalación del firmware
1. Clonar el repositorio:
   ```bash
   git clone https://github.com/VICHOFDEZ/TI201-SEC7-Grupo4.git
   ```
2. En Arduino IDE agregar la URL de placas `http://arduino.esp8266.com/stable/package_esp8266com_index.json` e instalar **ESP8266** desde el Gestor de tarjetas.
3. Instalar las librerías (ver [`firmware/librerias/`](firmware/librerias/README.md)).
4. Abrir el sketch deseado desde [`firmware/src/`](firmware/src/README.md) (por ejemplo `03_sensor_avanzado/03_sensor_avanzado.ino`).
5. Reemplazar `TU_WIFI`, `TU_CLAVE_WIFI` y `TU_FIREBASE_SECRET` por los datos reales (**no subir esas claves al repositorio**).
6. Seleccionar la placa **NodeMCU 1.0 (ESP-12E Module)**, el puerto COM, compilar y subir.
7. Abrir el Monitor Serie a **115200 baudios** para verificar la conexión.

### Conexión del sensor VL53L0X
| VL53L0X | NodeMCU |
|---|---|
| VIN | 3V3 |
| GND | GND |
| SCL | D1 (GPIO5) |
| SDA | D2 (GPIO4) |

Esquema completo en [`hardware/esquemas/`](hardware/esquemas/README.md).

### Visualización web
Abrir en el navegador cualquier archivo de [`firmware/web/`](firmware/src/README.md#interfaces-web). La más simple es `05_web_basica.html`; la versión con mapa del estacionamiento es `09_web_mapa_uai.html` / `11_web_disponibilidad_v10.html`.

---

## Entregables

| Área | Contenido | Ubicación |
|---|---|---|
| Hardware | Esquema (circuito.io), BOM, fotos | [`hardware/`](hardware/README.md) |
| Firmware | Código comentado, librerías, manual | [`firmware/`](firmware/README.md) |
| Diseño 3D | Fusion 360 (.f3d/.step), OpenSCAD, STL, renders, planos | [`diseño-3d/`](diseño-3d/README.md) |
| Testing | Datos cuantitativos, evidencias, reportes | [`testing/`](testing/README.md) |
| Documentación | Reporte final y presentación | [`docs/`](docs/README.md) |
| Iteraciones | v1, v2, v3 | [`iteraciones/`](iteraciones/README.md) |

---

## Licencia
Proyecto desarrollado para el curso TEI201 — Facultad de Ingeniería y Ciencias — Universidad Adolfo Ibáñez. Distribuido bajo licencia MIT (ver [`LICENSE`](LICENSE)). Fuentes externas declaradas en [`FUENTES.md`](FUENTES.md).
