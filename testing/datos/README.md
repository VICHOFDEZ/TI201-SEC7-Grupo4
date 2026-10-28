# Datos de Testing
**Última edición:** 28 de octubre de 2026

## Archivos de Datos

### `datos_cuantitativos.xlsx`
Hoja de cálculo principal con todos los datos recolectados durante las sesiones de testing del prototipo de estacionamiento con los 5 usuarios en la Universidad Adolfo Ibáñez.

**Estructura del documento:**

#### Sheet 1: Datos de Usuarios
| ID Usuario | Rango Etario | Perfil Universitario | Vehículo Habitual | Fecha Testing |
|------------|--------------|----------------------|-------------------|---------------|
| U01 | 18-22 | Estudiante | Auto Hatchback | 25-10-2026 |
| U02 | 18-22 | Estudiante | SUV | 25-10-2026 |
| U03 | 35-45 | Profesor | Auto Sedán | 25-10-2026 |
| U04 | 18-22 | Estudiante | Auto Hatchback | 26-10-2026 |
| U05 | 23-28 | Funcionario | Motocicleta | 26-10-2026 |

#### Sheet 2: Métricas de Usabilidad
| ID Usuario | Facilidad de Interfaz (1-5) | Satisfacción (1-5) | Latencia Web (seg) | Falsos Positivos |
|------------|-----------------------------|--------------------|--------------------|------------------|
| U01 | 5 | 5 | ~2.0 | 0 |
| U02 | 4 | 5 | ~2.5 | 0 |
| ... | ... | ... | ... | ... |

#### Sheet 3: Métricas de Impacto ODS (Proyectadas)
| ID Usuario | Minutos Ahorrados (Estimado) | Percepción de Reducción Estrés (1-5) | 
|------------|------------------------------|--------------------------------------|
| U01 | 7 | 5 |
| U02 | 10 | 4 |
| ... | ... | ... |

#### Sheet 4: Feedback Cualitativo
| ID Usuario | ¿Qué te gustó? | ¿Qué mejorarías? | Otros comentarios |
|------------|----------------|------------------|-------------------|
| U01 | El cambio de color en la web es súper claro. | Que se integre en la app de la UAI. | Muy útil para no subir si está lleno. |

---

### `datos_sensores_testing.csv`
Registro exportado de los datos capturados por el prototipo (Firebase / Consola Dev) durante las pruebas simuladas (interrupción del láser con la mano).

**Formato de ejemplo:**
```csv
timestamp, distancia_mm, estado, evento
2026-10-25 10:15:23, 850, LIBRE, inicio_prueba
2026-10-25 10:15:24, 120, OCUPADO, mano_detectada
2026-10-25 10:15:30, 850, LIBRE, mano_retirada
```

---

### `comparativa_versiones.xlsx`
Comparación de métricas técnicas entre las iteraciones del software (v1 Básico, v2 Avanzado, v3 Deep Sleep).

| Métrica | v1 (Básico) | v2 (Avanzado) | v3 (Deep Sleep) | Mejora Final |
|---------|-----|-----|-----|------------|
| Consumo de energía (mA) | ~70 mA continuo | ~70 mA continuo | ~20 µA (reposo) | -99.9% en reposo |
| Falsos positivos (peatones) | Altos | Nulos | Nulos | 100% mitigado |
| Estabilidad WiFi | Baja (bloqueos) | Alta (reconexión) | Alta | Óptima |

---

## Análisis Estadístico

### Estadísticos Básicos de Usabilidad (N = 5 usuarios)
- **Facilidad de Uso (1-5):** Media 4.6 | Mediana 5.0 | Mín: 4, Máx: 5
- **Satisfacción General (1-5):** Media 4.8 | Mediana 5.0 | Mín: 4, Máx: 5
- **Latencia del Sistema (seg):** Media 2.1s | Desv. Est: 0.3s

---

## Datos de Impacto ODS (Simulación a Escala Real)

### Baseline vs. Resultado (Proyectado)

**Antes de la intervención (Baseline - Hora punta UAI):**
- **Tiempo buscando plaza:** 5 a 10 minutos promedio.
- **Incertidumbre:** Alta (obligación de subir al campus físico para verificar).

**Después de la intervención (Con prototipo escalado):**
- **Tiempo buscando plaza:** < 1 minuto (el usuario ya sabe a qué sector dirigirse).
- **Incertidumbre:** Nula (verificación remota en tiempo real).

**Mejora Estimada:**
- **Ahorro de tiempo:** ~80-90% de mejora.
- **Reducción de emisiones (ralentí):** Proporcional al tiempo de búsqueda ahorrado por vehículo.

---

## Visualización de Datos

Si necesitas visualizar gráficamente los datos, exporta los gráficos desde `datos_cuantitativos.xlsx` en formato PNG y guárdalos en esta carpeta con los siguientes nombres:

- `grafico_usabilidad.png` (Barras con resultados de la escala Likert)
- `grafico_latencia.png` (Dispersión con tiempos de respuesta del sensor a Firebase)
- `grafico_consumo_energia.png` (Comparativa v1 vs v3)