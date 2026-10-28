# Reportes de Testing
**Última edición:** 28 de octubre de 2026

Este directorio contiene los documentos finales (en formato PDF) que sintetizan los resultados de las pruebas del prototipo del sensor de estacionamiento. 

> **Nota sobre la metodología:** Debido al riesgo de dañar la carcasa impresa en 3D, todos los reportes documentan pruebas validadas mediante simulación técnica (interrupción del sensor láser con la mano a <500 mm), replicando las condiciones reales de ocupación de un cajón de estacionamiento.

---

## Formato del Reporte Principal

### `reporte_testing_simulado_v3.pdf`

**Estructura del documento final:**

1. **Introducción**
   - Objetivo del testing del prototipo IoT (Versión 3 - Deep Sleep).
   - Justificación técnica de la metodología simulada.

2. **Descripción de Participantes**
   - Perfil demográfico: 5 usuarios (estudiantes y profesores de la UAI).
   - Contexto de movilidad de la muestra.

3. **Protocolo Aplicado**
   - Pasos de la simulación de estacionamiento.
   - Demostración de las interfaces web (`05_web_basica.html` y consola dev).
   - Aplicación de encuestas de usabilidad y percepción.

4. **Resultados Cuantitativos**
   - Tabla de latencia del sistema (tiempo de actualización en Firebase).
   - Resultados de la Escala Likert de usabilidad.
   - Análisis de consumo de energía de la placa ESP8266.

5. **Resultados Cualitativos**
   - Feedback de los usuarios sobre la utilidad de la interfaz web.
   - Percepción de valor frente al problema de estacionar en la universidad.
   - Oportunidades de mejora (ej. integración con apps existentes).

6. **Validación de Impacto ODS (ODS 11 - Ciudades Sostenibles)**
   - Proyección de tiempo ahorrado en horas punta.
   - Proyección de reducción de emisiones por vehículos en ralentí.
   - Viabilidad de escalamiento en el campus Peñalolén.

7. **Conclusiones**
   - Fortalezas del filtro anti-falsas alarmas por software.
   - Limitaciones físicas del gabinete 3D actual.
   - Recomendaciones para fabricación industrial (inyección de plástico/resina).

8. **Anexos**
   - Capturas de la base de datos Firebase.
   - Tablas de datos raw y notas de campo.

---

## Reportes Complementarios

### `analisis_impacto_ods_11.pdf`
Documento enfocado exclusivamente en la proyección ambiental y de bienestar estudiantil si el sistema se implementa en el 100% de los estacionamientos de la UAI.

### `feedback_usuarios.pdf`
Compilación de comentarios, sugerencias de interfaz y validación de la experiencia de usuario (UX) del dashboard web.

### `comparativa_iteraciones.pdf`
Análisis técnico de la evolución del desempeño del código:
- **v1 Básico:** Alto consumo, latencia media.
- **v2 Avanzado:** Filtros por software, sin falsos positivos.
- **v3 Deep Sleep:** Consumo optimizado (batería), reconexión inteligente, latencia óptima.

---

## Datos a Incluir en los Reportes

### Tablas de Resultados
Ejemplo del formato utilizado en los reportes en PDF:

| ID Usuario | Perfil UAI | Facilidad Interfaz (1-5) | Latencia Observada | Comentarios Principales |
|------------|------------|--------------------------|--------------------|-------------------------|
| U01 | Estudiante | 5 | ~2.0 seg | "El verde y rojo es directo y no distrae si voy manejando." |
| U02 | Profesor (de otro ramo)  | 4 | ~2.5 seg | "Muy útil para saber si debo buscar arriba o abajo." |
| U03 | Estudiante | 5 | ~2.1 seg | "Me gustaría verlo en pantallas LED físicas." |

### Gráficos Incluidos
Los reportes integran las siguientes visualizaciones (generadas a partir de la subcarpeta `/datos`):
- **Gráfico de barras:** Resultados de la escala de satisfacción general.
- **Gráfico comparativo:** Consumo de corriente (mA) entre la versión básica continua vs. la versión Deep Sleep.
- **Proyección ODS:** Gráfico de líneas estimando el ahorro acumulado de minutos perdidos buscando estacionamiento durante un mes académico.