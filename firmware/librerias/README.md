# Librerías

## Librerías Estándar (Arduino IDE)

Instalar desde el Library Manager de Arduino IDE:

1. **Firebase ESP8266 Client** (por Mobizt)
   - **Propósito:** Permite la comunicación en tiempo real entre el microcontrolador ESP8266 y Firebase Realtime Database.
   - **Instalación:** `Programa > Incluir Librería > Administrar Bibliotecas > Buscar "Firebase ESP8266 Client"`

2. **Adafruit VL53L0X** (por Adafruit)
   - **Propósito:** Controladores y funciones de comunicación I2C para operar el sensor de distancia láser de tiempo de vuelo.
   - **Instalación:** `Programa > Incluir Librería > Administrar Bibliotecas > Buscar "Adafruit VL53L0X"`

---

## Librerías Personalizadas/Modificadas

Si hay librerías modificadas o descargadas manualmente en formato `.zip` que no se instalaron desde el gestor (por ejemplo, versiones específicas o parches para `wpa2_enterprise.h`), deben incluirse descomprimidas en esta carpeta.

### Estructura
```text
librerias/
├── Adafruit_VL53L0X/        (Ejemplo si se descargó manual)
├── Firebase_ESP8266_Client/ (Ejemplo si se descargó manual)
└── README.md
```

### Instalación Manual (Windows)
1. Copiar las carpetas de las librerías que estén aquí.
2. Pegarlas en la ruta local de librerías de Arduino:
   `C:\Usuarios\TuUsuario\Documentos\Arduino\libraries\`

---

## Dependencias Completas

Listado de TODAS las librerías necesarias para compilar el código del sensor:

| Librería | Versión recomendada | Fuente | Obligatoria |
|----------|---------|--------|-------------|
| `ESP8266WiFi` | Built-in | ESP8266 Core | ✅ |
| `Wire` | Built-in | ESP8266 Core | ✅ |
| `Firebase ESP8266 Client` | 4.3.x o superior | Arduino Library Manager | ✅ |
| `Adafruit_VL53L0X` | 1.2.x o superior | Arduino Library Manager | ✅ |
| `wpa2_enterprise.h`| Built-in | ESP8266 Core SDK | ✅ (Solo para red UAI) |