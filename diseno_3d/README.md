# Diseño 3D - Documentación

## ⚠️ REQUISITO CRÍTICO
El modelo tridimensional corresponde a un sensor de estacionamiento que utiliza tecnología infrarroja para medir distancias.

### Componentes del prototipo

- Carcasa exterior de PLA.
- Placa NodeMCU ESP8266.
- Sensor de distancia GY-530 (VL53L0X).
- Batería recargable 18650.
- Módulo Battery Shield V3.
- Ventana de plástico transmisor de infrarrojos.
- Junta de sellado NBR.
- Soportes, conectores y tornillería.
---

## Carpetas

#### `fusion360/`
Archivos nativos de Fusion 360 (.f3d)

#### `renders/`
Imágenes renderizadas de alta calidad

#### `planos/`
Planos técnicos con cotas

---

## Especificaciones
Software: Autodesk Fusion 360

Unidades: Milímetros (mm)

Escala del modelo CAD: 1:1

Escala de los planos técnicos: 1:2

Dimensiones nominales del conjunto:

Diámetro exterior: 150 mm.

Profundidad total: 40 mm.

Peso estimado: Pendiente de determinar mediante las propiedades físicas del modelo y la batería real.

Material de fabricación de la carcasa: PLA.

Otros materiales: Plástico transmisor de infrarrojos, caucho NBR y componentes electrónicos comerciales.

---

## Consideraciones de Diseño

### Funcionales
-Integración del sensor infrarrojo en la parte frontal del dispositivo.
-Espacio interior destinado al NodeMCU ESP8266 y al módulo de alimentación.
-Incorporación de una batería recargable 18650.
-Ventana frontal para permitir el paso de luz infrarroja.
-Junta de sellado NBR para reducir el ingreso de agua.
-Sistema de montaje mediante tornillos.
-Acceso a alimentación y conexiones eléctricas sujeto a verificación en el prototipo.
-Distribución definitiva del cableado pendiente de validación.

### Fabricación
-Carcasa diseñada para fabricación mediante impresión 3D en PLA.
-Base y cubierta superior modeladas como componentes independientes.
-Tolerancia general propuesta: ±0,5 mm.
-Tolerancia de encajes propuesta: ±0,2 mm.
-Diseño paramétrico que permite modificar dimensiones y geometrías.
-Las tolerancias deberán comprobarse mediante pruebas de impresión y ensamblaje

---

## Configuración de Impresión 3D (si fue utilizada)

**Impresora:** [Modelo]  
**Material:** [PLA]  
**Calidad de capa:** 0.2mm  
**Relleno:** 20-30%  
**Soportes:** [Sí/No - dónde]  
**Temperatura nozzle:** [°C]  
**Temperatura cama:** [°C]  
**Velocidad:** [mm/s]

**Tiempo estimado de impresión:** [X horas]  
**Peso de material:** [X gramos]
