# Archivos OpenSCAD (Diseño Paramétrico)

## Archivos Requeridos

### Archivos en esta carpeta

El nombre del archivo no coincide con el número de versión interno del código; esta tabla los relaciona:

| Archivo | Versión interna (encabezado) | Descripción |
|---|---|---|
| `detector_laser_v7.scad` | V7 | Geometría inicial: base de anclaje + cubierta |
| `detector_laser_v8.scad` | V8 | V7 ajustada, lista para imprimir |
| `Version_8.scad` | V9 (ovalado) | Iteración ovalada con orejas de montaje externas |
| `Version_9.scad` | V13 (parabólico) | Orejas de unión integradas al contorno parabólico |
| `Version_10.scad` | V16 | Versión final: base, soporte y cubierta (planos `v10_plano_*.pdf`) |
| `csg/Version_10_base.csg`, `csg/Version_10_cubierta.csg`, `csg/Version_10_soporte.csg` | V16 | Exportaciones CSG de cada pieza de la Versión 10 |

Los archivos principales contienen el **historial de desarrollo basado en código**.

**DEBE INCLUIR:**
- Todos los componentes modelados paramétricamente mediante módulos.
- Ensamble completo funcional (activado mediante la variable `pieza = "ensamblado"`).
- Código fuente editable con variables globales.
- Colores representativos asignados a los componentes electrónicos para visualización.

---

## Estructura del Modelo

### Componentes (Módulos de OpenSCAD)
```text
Ensamble_Principal (module ensamblado)
├── module base()           // Base_Anclaje_PLA
├── module cubierta()       // Cubierta_Sellada_PLA
├── module oring_mod()      // Junta_Oring_NBR
├── module ventana_demo()   // Ventana_Polimero_Infrarrojo
├── module sensor()         // Sensor_GY530_VL53L0X
├── module esp()            // NodeMCU_ESP8266 + Battery_Shield_V3
├── module bateria()        // Bateria_18650
└── module taladro()        // Soportes, Conectores y Tornillería
```

### Uniones y Relaciones Espaciales
A diferencia de los *Joints* de Fusion 360, el modelo en OpenSCAD utiliza transformaciones matemáticas (`translate`) para mantener los componentes unidos sin movimiento relativo (ensamble rígido estático).

Las principales relaciones mecánicas definidas en el código son:
- La base de anclaje se genera desde el origen (Z=0).
- La cubierta superior se alinea con la base y se fija mediante sustracciones cilíndricas que simulan los cuatro tornillos M3 (`module taladro`).
- La junta O-ring de caucho NBR se aloja en una ranura calculada paramétricamente (`prof_ranura = 2.0`) entre la base y la cubierta para evitar el ingreso de agua.
- La ventana de plástico transmisor de infrarrojos se ubica geométricamente frente a la cota Z del sensor de distancia (`techo_z`).
- El NodeMCU ESP8266, el sensor GY-530 y el Battery Shield V3 se mantienen fijos dentro de la carcasa utilizando vectores de posición central (`esp_c`, `sen_c`).
- La batería 18650 se sitúa en el fondo de la base (`bat_c`).

### Parámetros
Listar parámetros principales utilizados en el código:
- `base_a = 94` mm (Semieje mayor del ensamble parabólico)
- `alto_cubierta = 55` mm (Altura de la cúpula)
- `h_base = 8` mm (Espesor de la base de anclaje)
- `oring_d = 2.5` mm (Sección del O-ring NBR)
- `grosor_ventana = 1.5` mm (Espesor de la plancha transmisora de IR)
- `d_insert = 4.2` mm (Diámetro para insertos térmicos M3)

---

## Instrucciones de Apertura

1. Abrir el software OpenSCAD.
2. File > Open > Seleccionar archivo `.scad` (por ejemplo `Version_10.scad`).
3. Modificar la variable `pieza` en las primeras líneas del código (ej. `"base"`, `"cubierta"`, `"ensamblado"`) según lo que se desee visualizar o exportar.
4. Presionar **F5** para previsualizar el ensamble o **F6** para renderizar la malla y exportar a STL.

---

## Versiones

| Versión | Fecha | Cambios Principales |
|---------|-------|---------------------|
| v4.0 (V16 SCAD — `Version_10.scad`) | 19-11-26 | Versión final dividida en base, soporte y cubierta; base de los planos `v10_plano_*.pdf`. |
| v3.0 (V13 SCAD — `Version_9.scad`) | 28-10-26 | Iteración parabólica con orejas integradas al contorno. |
| v2.0 (V9 SCAD — `Version_8.scad`) | [COMPLETAR fecha] | Iteración ovalada con escalones y orejas de montaje externas. |
| v1.x (V7/V8 SCAD — `detector_laser_v7.scad`, `detector_laser_v8.scad`) | V8: 30-10-26 · V7: [COMPLETAR fecha] | Geometría inicial del sensor de estacionamiento en OpenSCAD. |

---

## Contexto de Desarrollo

Durante el desarrollo del sensor de estacionamiento se elaboraron dos enfoques de modelado tridimensional, con el objetivo de mejorar la distribución de los componentes electrónicos, la estructura de la carcasa de PLA y la viabilidad de fabricación mediante impresión 3D.

**Modelado Paramétrico Inicial (OpenSCAD)**
Esta carpeta contiene los archivos de las versiones iniciales, de transición y final (V7, V8, V9, V13, V16) desarrolladas estrictamente mediante programación paramétrica en OpenSCAD. 

Estas versiones permitieron iterar rápidamente mediante código las proporciones de la carcasa, calcular las holguras para la batería 18650, el módulo Battery Shield V3 y el sensor GY-530, y validar las dimensiones de la junta de goma NBR y la ventana infrarroja. Este enfoque paramétrico sirvió como el esqueleto matemático fundacional antes de consolidar el diseño final y sus planimetrías en Autodesk Fusion 360.