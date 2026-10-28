# Esquemas de Circuito

## Archivos Requeridos

Ninguno de las dos plataformas permite armar un circuito con sensor VL53L0X por lo cual debimos hacerlo en otra plataforma llamada circuito.io
### Formato circuito.io
Firmwere(1).ion 
Formato.circuito.jpg


---

## Nomenclatura de Archivos
- Usar nombres descriptivos prototipo codigo
- Incluir versión: (https://www.circuito.io/app?components=11856,219866,360216)
- Fecha en formato: `28/10/2026

---

## Notas de Diseño
- **Limitación de la Plataforma:** Se utilizó `circuito.io` como herramienta de diseño y simulación por ser la única plataforma disponible que integraba de forma nativa la compatibilidad y el diagrama de conexionado para el sensor de distancia láser VL53L0X junto al NodeMCU ESP8266.
- **Ajuste en la Simulación de Batería:** Debido a restricciones del catálogo de componentes de la plataforma virtual, en el esquema digital se simuló utilizando una batería de 7.4V (o el equivalente disponible por defecto en el sistema). Sin embargo, en el diseño físico real del prototipo se implementa y respeta estrictamente una **batería recargable 18650 de 3.7V** conectada a su respectivo módulo de carga con salida USB de 5V, asegurando así el voltaje seguro y adecuado para la alimentación del microcontrolador y el sensor[cite: 1, 3].
