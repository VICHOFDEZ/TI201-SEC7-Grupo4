# Archivos Fusion 360

## Archivos Requeridos

### `modelo_completo_v3.f3d`
Archivo principal con **historial de cambios completo**

**DEBE INCLUIR:**
-  Todos los componentes modelados
-  Ensamble completo funcional
-  Historial de diseño (timeline)
-  Materiales asignados
-  Constraints y relaciones

---

## Estructura del Modelo

### Componentes (Components)
```
Ensamble_Principal
├── Base_Anclaje_PLA
├── Cubierta_Sellada_PLA
├── Junta_Oring_NBR
├── Ventana_Polimero_Infrarrojo
├── Sensor_GY530_VL53L0X
├── NodeMCU_ESP8266
├── Battery_Shield_V3
└── Bateria_18650
├── Soportes_y_Conectores
└── Tornilleria
```

### Uniones (Joints)
Documentar las juntas principales y sus restricciones
El modelo del sensor de estacionamiento utiliza un ensamble rígido denominado R01_Ensamble_Estatico_Fijo, creado en Fusion 360.

Este grupo mantiene los componentes unidos sin movimiento relativo, ya que el sensor de estacionamiento es un dispositivo estático.

Las principales relaciones mecánicas son:

La base de anclaje permanece fija.

La cubierta superior se une a la base mediante cuatro tornillos M3.

La junta O-ring de caucho NBR se ubica entre las partes de la carcasa para evitar el ingreso de agua.

La ventana de plástico transmisor de infrarrojos se instala frente al sensor de distancia.

El NodeMCU ESP8266, el sensor GY-530 y el Battery Shield V3 se mantienen fijos dentro de la carcasa.

La batería 18650 se coloca en su soporte correspondiente.

El ensamble utiliza un grupo rígido global, sin juntas móviles. Las relaciones anteriores describen la disposición mecánica de los componentes.
### Parámetros
Listar parámetros principales utilizados:
-diametro_brida = 150 mm
-altura_total_prototipo = 40 mm
-espesor_base = 8 mm
-seccion_oring = 2.5 mm
-diametro_oring_medio = 103 mm
-espesor_ventana = 2 mm

---

## Instrucciones de Apertura

1. Abrir Fusion 360
2. File > Open > Seleccionar archivo `.f3d`
3. Verificar que todas las referencias están cargadas
4. Revisar timeline para ver historial

---

## Versiones

| Versión | Fecha | Cambios Principales |
|---------|-------|---------------------|
| v3.0 | [28-10-26] | Versión final para Avance #3 |
| v2.1 Reconstrucción Fusion 360 | [21-10-26] | Reconstrucción paramétrica y organización del ensamble en Fusion 360. |
| v1.0 Modelo inicial OpenSCAD V7 | [Fecha] | Desarrollo de la geometría inicial del sensor de estacionamiento. |

---


Durante el desarrollo del sensor de estacionamiento se elaboraron dos modelos tridimensionales, con el objetivo de mejorar la distribución de los componentes electrónicos, la estructura de la carcasa y la viabilidad de fabricación mediante impresión 3D.

Modelo 1: Diseño inicial en OpenSCAD

El primer modelo fue desarrollado en OpenSCAD y corresponde al archivo detector_laser_v7.scad.

Esta versión permitió establecer la geometría inicial del dispositivo, incluyendo la carcasa, el espacio destinado al sensor de distancia y la disposición general de los componentes internos.

El diseño sirvió como punto de partida para evaluar la estructura del dispositivo e identificar aspectos que debían mejorarse para su fabricación y ensamblaje.

Modelo 2: Diseño final en Fusion 360

El segundo modelo fue desarrollado en Autodesk Fusion 360, utilizando como referencia el diseño inicial e incorporando mejoras en la organización de los componentes y el ensamblaje.

Esta versión incluye:

-Carcasa y soportes diseñados para impresión 3D en PLA.

-Placa NodeMCU ESP8266.

-Sensor de distancia infrarrojo GY-530 (VL53L0X).

-Módulo de alimentación Battery Shield V3.

-Batería recargable 18650.

-Ventana de plástico transmisor de luz infrarroja.

-Junta de goma NBR (O-ring) para el sellado.

-Tornillería y elementos de fijación.
Se seleccionó el segundo modelo como versión final del proyecto debido a que permite documentar el ensamblaje, los materiales y las operaciones de diseño en Fusion 360.
