# Planos Técnicos

## Planos Requeridos

### 1. Plano de Conjunto
`v3_plano_conjunto.pdf`

Incluir:
- Vistas principales (frontal, lateral, superior)
- Escala apropiada
- Cotas principales externas
- Tabla de piezas

### 2. Planos de Detalle
Para cada componente crítico del encapsulado:
- Cotas completas
- Tolerancias importantes
- Notas de fabricación

---

## Estándares de Planos

### Vistas Ortogonales Requeridas
- Vista Frontal
- Vista Superior
- Vista Lateral Derecha
- Vista Isométrica (referencia)

### Cortes
- Corte A-A: Sección transversal mostrando interior
- Corte B-B: (si es necesario para claridad)

---

## Formato de Planos

**Tamaño de hoja:** A3  
**Orientación:** Según convenga  
**Escala:** 1:1, 1:2, o según sea necesario  
**Unidades:** Milímetros (mm)

### Información en Cajetín
- Título del proyecto
- Nombre de la pieza/ensamble
- Escala
- Material
- Fecha
- Versión
- Integrantes del equipo

---

## Acotación

### Reglas Generales
- Cotas en milímetros sin unidad
- Líneas de cota finas
- Texto legible (mín. 2.5mm de altura)
- Cotas críticas resaltadas

### Tolerancias
Indicar tolerancias para:
- Orificios de tornillos: ±0.1mm
- Encajes: +0.2mm / +0.0mm
- Dimensiones generales: ±0.5mm

---

## Exportación desde Fusion 360

```
Opción 1: Drawing (Plano tradicional)
1. Create Drawing
2. Configurar vistas y cotas
3. Export como PDF

Opción 2: Export directo
File > Export > Formato PDF/DWG
```

---

## Archivos a Entregar

- `v3_plano_conjunto.pdf` - Plano principal


Planos técnicos realizados

Se elaboraron los planos técnicos del sensor de estacionamiento utilizando Autodesk Fusion 360, tomando como referencia el modelo tridimensional final del dispositivo.

Los planos fueron desarrollados en formato A3, siguiendo la norma ISO y utilizando milímetros como unidad de medida.

Plano 1: Conjunto general
Se incluyeron las vistas frontal, superior, lateral derecha e isométrica del sensor de estacionamiento.
Se incorporaron las principales dimensiones del dispositivo, incluyendo el diámetro exterior de 150 mm, la profundidad total de 40 mm y los agujeros de montaje.
Además, se realizó un corte transversal A-A para representar la distribución interna del ensamblaje.

Plano 2: Lista de componentes
Se elaboró una tabla de piezas que identifica los 18 componentes del modelo, incluyendo los elementos estructurales, electrónicos y de fijación.

Plano 3: Base de anclaje
Se desarrolló el plano de fabricación de la base de anclaje, diseñada para impresión 3D en PLA.
Se incorporaron vistas frontal y lateral, cotas de fabricación y notas técnicas con tolerancias propuestas.

Plano 4: Cubierta superior
Se realizó el plano de fabricación de la cubierta superior, también diseñada para impresión 3D en PLA.
Se incluyeron las dimensiones principales, las vistas necesarias y las notas de fabricación correspondientes.
Archivo final
Los cuatro planos se agruparon en un documento PDF para facilitar su revisión y entrega.
Archivo requerido: v3_plano_conjunto.pdf
Las tolerancias de fabricación indicadas son propuestas y deberán verificarse durante la impresión y el montaje del prototipo.

-------------------------------o-------------------------------------

## Segundo prototipo: Versión 10 (modelo en OpenSCAD `Version_10.scad`, planos en Fusion 360)
El diseño fue modelado en OpenSCAD, importado a Autodesk Fusion 360 para generar los planos, y está compuesto por tres piezas principales: base, soporte y cubierta.

Los componentes están diseñados para fabricarse mediante impresión 3D utilizando PLA (ácido poliláctico).

Los planos técnicos permiten visualizar la geometría de cada pieza, sus dimensiones, tolerancias y características necesarias para la fabricación y el ensamblaje.

Integrantes del equipo
Mateo Soliz
Gaspar Rosales
Vicente Fernández
Renato Díaz

2. Planos requeridos
2.1. Plano de conjunto
Archivo: v10_plano_conjunto.pdf
El plano de conjunto representa el dispositivo ensamblado e incluye:

Vista frontal.
Vista superior.
Vista lateral derecha.
Vista isométrica de referencia.
Cotas principales externas.
Escala correspondiente.
Corte A-A para visualizar el interior del encapsulado.
Tabla de piezas del ensamblaje.

2.2. Planos de detalle
Se realizaron planos individuales de los principales componentes del encapsulado.
Base: v10_plano_base.pdf
Contiene las vistas ortogonales, vista isométrica, dimensiones generales, perforaciones y notas técnicas de fabricación.

Soporte: v10_plano_soporte.pdf
Presenta las dimensiones del soporte, separación entre perforaciones, diámetros, vistas principales y notas técnicas.

Cubierta: v10_plano_cubierta.pdf
Incluye las vistas del componente, dimensiones principales, geometría exterior y especificaciones técnicas.

Los planos de detalle permiten identificar las características geométricas de cada componente para su fabricación y posterior ensamblaje.

3. Estándares de los planos

3.1. Vistas ortogonales

Los planos consideran las siguientes vistas:

Vista frontal.
Vista superior.
Vista lateral derecha.
Vista isométrica como referencia tridimensional.

3.2. Cortes

Corte A-A: sección transversal destinada a mostrar la disposición y las características interiores del encapsulado.

Corte B-B: se incorpora únicamente cuando es necesario representar detalles que no sean suficientemente claros en las vistas principales.

4. Formato de los planos
Las especificaciones generales utilizadas son:
Tamaño de hoja: A3.
Orientación: horizontal.
Escala: 1:1, 1:2 o según corresponda.
Unidades: milímetros (mm).
Material: PLA.
Proceso de fabricación: impresión 3D.
Software: Autodesk Fusion 360.

4.1. Información del cajetín
Cada plano debe contener:
Título del proyecto.
Nombre de la pieza o ensamblaje.
Escala utilizada.
Material.
Fecha de elaboración.
Versión o revisión.
Integrantes del equipo.

5. Acotación y tolerancias

5.1. Reglas generales
Todas las dimensiones se expresan en milímetros.
Las cotas se presentan sin repetir la unidad junto a cada valor.
Las líneas de cota deben ser finas.
El texto debe ser legible, con una altura mínima de 2,5 mm.
Las dimensiones críticas deben estar claramente identificadas.

5.2. Tolerancias
Las tolerancias especificadas para el diseño son:
Dimensiones generales: ±0,5 mm.
Orificios de tornillos: ±0,1 mm.
Encajes entre componentes: +0,2 / +0,0 mm.
Estas tolerancias corresponden a los requisitos dimensionales del diseño y deben comprobarse durante la fabricación y el ensamblaje.

6. Notas de fabricación

Los componentes principales se consideran fabricados mediante impresión 3D utilizando PLA.
Durante la fabricación se deben respetar las dimensiones especificadas en los planos técnicos, especialmente las perforaciones y superficies de encaje.
También se debe verificar que las piezas puedan ensamblarse correctamente y que no existan interferencias entre los componentes.

7. Generación y exportación de planos

Los planos técnicos se elaboraron utilizando las herramientas de dibujo de Autodesk Fusion 360.
El procedimiento general consiste en:
Abrir el modelo tridimensional correspondiente.
Seleccionar la herramienta Drawing (Dibujo).
Configurar el estándar ISO y las unidades en milímetros.
Seleccionar el formato de hoja A3.
Generar las vistas ortogonales.
Incorporar la vista isométrica.
Agregar las cotas y tolerancias necesarias.
Completar el cajetín y las notas técnicas.
Exportar el dibujo en formato PDF.

8. Archivos de entrega

La documentación técnica contempla los siguientes archivos:
v10_plano_conjunto.pdf: plano general del ensamblaje.
v10_plano_base.pdf: plano de detalle de la base.
v10_plano_soporte.pdf: plano de detalle del soporte.
v10_plano_cubierta.pdf: plano de detalle de la cubierta.

README.md: documentación de los planos técnicos.