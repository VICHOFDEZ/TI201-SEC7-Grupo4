# Hardware - Documentación

## Contenido
Esta carpeta contiene toda la documentación técnica del hardware del proyecto.

### 📁 Carpetas

#### `esquemas/`
Diagramas de circuitos y esquemáticos del sistema

#### `bom/`
Bill of Materials (Lista de materiales):
NodeMCU ESP8266
Sensor de Distancia VL53L0X
Batería 18650
Portabatería 18650 con Módulo de Carga
Cables de conexión

#### `fotos/` 
- 02_vista_general.jpg
Fotografías de alta resolución del prototipo ensamblado

---

## Instrucciones de Ensamble

### Componentes Principales
1. NodeMCU ESP8266 - Placa de desarrollo con microcontrolador y conectividad Wi-Fi para procesar y enviar los datos.
2. Sensor de distancia VL53L0X (ToF - I2C) - Sensor láser de alta precisión para medición de distancias cortas.
3. Portabatería 18650 con salida USB de 5V - Módulo de carga tipo power bank equipado con una batería recargable de 3.7V.

### Pasos de Ensamblaje
1. Colocar el NodeMCU ESP8266 y el módulo sensor VL53L0X.
2. Conecta el pin VIN del sensor al pin 3V3 del NodeMCU (cable rojo).
3. Conecta el pin GND del sensor al pin GND del NodeMCU (cable negro)
4. Conecta el pin SCL del sensor al pin D1 (GPIO5) del NodeMCU (cable amarillo).
5. Conecta el pin SDA del sensor al pin D2 (GPIO4) del NodeMCU (cable morado/violeta).
6. Alimentación del sistema: Conecta la salida USB de 5V del módulo de la batería 18650 hacia la entrada micro-USB del NodeMCU utilizando un cable USB.

### Precauciones
- ⚠️ Alimentación del sistema: Conecta la salida USB de 5V del módulo de la batería 18650 hacia la entrada micro-USB del NodeMCU utilizando un cable USB.
- ⚠️ Asegurarse de que el sensor VL53L0X esté alimentado al pin de 3V3 y no a un voltaje superior para proteger el componente.
---

## Especificaciones Técnicas

**Alimentación:** Alimentación: 3.7V (Batería 18650 recargable) / 5V DC (Salida USB del módulo de carga y entrada micro-USB) 
**Consumo:** ~80 mA a 250 mA (variable según el uso del Wi-Fi en el NodeMCU) 
**Dimensiones:** 150mm x 150mm x 30mm (Módulo de batería y placa base ensamblados dentro de la caja)
**Peso:** Aprox 80gr con bateria

---

## Troubleshooting

| Problema | Posible Causa | Solución |
|----------|---------------|----------|
| El sensor VL53L0X no responde | Conexión incorrecta de los pines de datos o desconeccion de algun cable | Verificar que el pin SCL esté conectado a D1 y el pin SDA a D2 en el NodeMCU
 |
| El NodeMCU no enciende al conectarlo a la batería | Batería descargada o interruptor del portabatería apagado | Cargar la batería 18650 mediante el puerto USB del módulo o comprobar el estado del interruptor. |
