# Renders de Alta Calidad

## Renders Requeridos (Mínimo 4 ángulos)

### 1. Vista Isométrica Frontal
`01_isometrica_frontal.png`
- Muestra exterior completo
- Iluminación clara
- Resolución: 1920×1080 mínimo

### Renders Opcionales (Recomendados)
- `02_detalle_sensores.png` - Close-up de sensores
- `03_ensamble_explosionado.png` - Componentes separados
- `04_variantes_color.png` - Si hay opciones de diseño

---

## Configuración de Render en Fusion 360

### Settings Recomendados
- **Render Engine:** Local / Cloud
- **Environment:** [Tipo de iluminación]
- **Resolution:** 1920×1080 o superior
- **Quality:** High
- **Exposure:** [Ajustado para visibilidad]
- **Effects:** Ambient Occlusion ON

### Materiales y Apariencias
Asignar materiales realistas:
- Plástico: PLA mate o satinado
- Electrónica: PCB verde, componentes negros
- Metales: Tornillos acero inoxidable

---

## Nomenclatura de Archivos
```
[numero]_[descripcion]_[version].png

Ejemplo:
01_isometrica_frontal_v3.png
```

---

## Checklist de Calidad

- [ ] Resolución mínima 1920×1080
- [ ] Formato PNG (con transparencia si aplica)
- [ ] Iluminación sin sombras excesivas
- [ ] Componentes internos visibles en corte
- [ ] Fondo neutro o contextual apropiado
- [ ] Sin aliasing o bordes pixelados
- [ ] Todos los componentes críticos visibles


Se realizaron cuatro renders del modelo tridimensional del sensor de estacionamiento utilizando Autodesk Fusion 360, con el objetivo de representar visualmente el diseño final desde diferentes perspectivas.

El dispositivo cuenta con una carcasa diseñada para impresión 3D en PLA, una ventana de plástico transmisor de luz infrarroja, una junta de sellado NBR y los componentes electrónicos necesarios para su funcionamiento.

Render 1: Vista isométrica frontal
Archivo: 01_isometrica_frontal_v3.png
Muestra la parte frontal del sensor de estacionamiento, permitiendo observar la forma de la carcasa, la ubicación de la ventana infrarroja y los elementos de montaje.

Render 2: Vista isométrica trasera
Archivo: 02_isometrica_trasera_v3.png
Presenta el dispositivo desde una perspectiva posterior, permitiendo apreciar la estructura de la carcasa, su profundidad y los elementos de unión y sellado.

Render 3: Vista lateral derecha
Archivo: 03_lateral_derecha_v3.png
Permite observar el perfil del dispositivo, destacando el espesor de la base y la forma de la cubierta superior.

Render 4: Vista superior
Archivo: 04_superior_v3.png
Muestra el sensor desde una perspectiva superior, permitiendo apreciar su geometría y la disposición general de la carcasa.

Configuración de renderizado
Para la generación de las imágenes se utilizó Autodesk Fusion 360 con la siguiente configuración:
Software: Autodesk Fusion 360.
Motor de renderizado: Renderizador local.
Resolución objetivo: 1920 × 1080 píxeles.
Formato de imagen: PNG sin pérdida.
Iluminación: Entorno Luz suave.
Fondo: Color sólido gris claro.
Esta configuración permite representar el dispositivo con iluminación uniforme, resaltando su geometría y los materiales utilizados.
Materiales representados
PLA: carcasa y soportes fabricables mediante impresión 3D.
Plástico transmisor de infrarrojos: ventana frontal del sensor.
Caucho NBR: junta de sellado para reducir el ingreso de agua.
Componentes electrónicos comerciales: NodeMCU ESP8266, sensor GY-530, Battery Shield V3 y batería 18650.
Acero: tornillería y elementos de fijación.
Resultado final

Los cuatro renders permiten visualizar el diseño del sensor de estacionamiento desde diferentes perspectivas y complementan el modelo paramétrico de Fusion 360 y los planos técnicos desarrollados.