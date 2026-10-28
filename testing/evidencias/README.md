# Evidencias de Testing
**Última edición:** 28 de octubre de 2026

> **Nota Técnica de Validación:** Para garantizar la integridad estructural del prototipo (carcasa impresa en 3D) y evitar el riesgo de aplastamiento bajo un vehículo de 2 toneladas, las evidencias documentan una simulación técnica validada. Se interrumpe el láser del sensor VL53L0X utilizando la mano u objetos sólidos a menos de 500 mm, lo cual replica la lógica exacta de detección del chasis de un automóvil según el código fuente.

## Contenido del Directorio

### Fotografías

#### Sesiones de Simulación
- `sesion_simulada_01.jpg`
- `sesion_simulada_02.jpg`

**Requisitos documentados en las fotos:**
- Muestran la interacción de los usuarios acercando la mano al sensor.
- Se observa el dashboard web reaccionando en un dispositivo secundario (notebook/celular).
- Rostros difuminados o ángulos cerrados en caso de no contar con consentimiento expreso.

#### Instalación y Hardware
- `instalacion_gabinete_3d.jpg`
- `conexion_hardware.jpg`

**Requisitos documentados:**
- Prototipo ensamblado con su ESP8266 y sensor láser visible.
- Referencia de escala para dimensionar la carcasa.

---

### Videos

#### Video de Demostración (Simulación)
`07_contexto_uso.mp4`

**Contenido del video:**
- Registro de la prueba de concepto operativa.
- Se documenta el momento exacto en que el usuario bloquea el láser con la mano.
- Muestra en paralelo cómo la pantalla (interfaz web básica) cambia automáticamente de Verde (LIBRE) a Rojo (OCUPADO), validando la baja latencia (aprox. 2 segundos) y la sincronización con Firebase.

---

## Privacidad y Consentimiento

### Manejo de Imágenes
- Las fotos y videos almacenados en esta carpeta son para fines estrictamente académicos (curso TEI201 - Universidad Adolfo Ibáñez).
- Se obtuvo consentimiento verbal de los participantes antes de grabar sus interacciones.
- **Anonimización:** Si los rostros de los usuarios aparecen en el registro audiovisual, se aplicó difuminado o se encuadró la cámara directamente hacia el dispositivo y la mano del usuario, priorizando la privacidad.

---

## Organización de Archivos

```text
evidencias/
├── fotos/
│   ├── sesiones_simuladas/
│   │   ├── sesion_simulada_U01_20261025.jpg
│   │   └── sesion_simulada_U02_20261025.jpg
│   └── hardware/
│       ├── instalacion_gabinete_3d.jpg
│       └── ensamble_interno.jpg
└── videos/
    └── demo_simulacion_mano_20261025.mp4
```

---

## Nomenclatura de Archivos Utilizada

Para mantener la estructura del repositorio de software, los archivos multimedia siguen el siguiente formato estándar:

**Fotos:**
`[tipo]_[descripcion]_[fecha].jpg`
*(Ej: `sesion_simulada_U01_20261025.jpg`, `hardware_gabinete_20261025.jpg`)*

**Videos:**
`[tipo]_[descripcion]_[fecha].mp4`
*(Ej: `demo_simulacion_mano_20261025.mp4`)*