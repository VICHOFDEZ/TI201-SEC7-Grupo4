# Testing y Validación
**Última edición:** 28 de octubre de 2026

## Objetivo
Validar el funcionamiento del prototipo IoT de monitoreo de estacionamientos, evaluar la experiencia de usuario y proyectar el impacto cuantitativo en la problemática ODS seleccionada, garantizando la integridad estructural del dispositivo durante las pruebas.

---

## 📁 Carpetas

#### `reportes/`
Documentos con los resultados de las encuestas y métricas de latencia de Firebase.

#### `evidencias/`
Fotos y videos de las sesiones. **Nota de Testing:** Para evitar el riesgo de aplastamiento estructural del gabinete 3D bajo el peso de un vehículo (2 toneladas), la detección de los chasis se simuló acercando la mano u objetos sólidos a menos de 50 cm del sensor, replicando exactamente la misma lógica de rebote láser del VL53L0X.

#### `datos/`
Hojas de cálculo con los tiempos de latencia y respuestas de la escala de usabilidad.

---

## Metodología de Testing

### Grupo Objetivo
- **Perfil de usuarios:** Estudiantes y profesores de la Universidad Adolfo Ibáñez (UAI) que conducen regularmente al campus.
- **Cantidad mínima:** 5 usuarios.
- **Ubicación:** Entorno controlado simulando un cajón de estacionamiento real.

### Protocolo de Testing
1. **Briefing** (5 min)
   - Explicar el propósito del sistema de monitoreo.
   - Aclarar la restricción mecánica y la simulación del vehículo mediante la interrupción del láser con la mano.
2. **Sesión de Uso** (15 min)
   - El usuario simula la acción de estacionar bloqueando el sensor láser.
   - Observación de la velocidad de actualización en el dashboard web (`05_web_basica.html`).
3. **Entrevista Post-Testing** (10 min)
   - Preguntas sobre la utilidad de tener esta información antes de llegar a la universidad.
   - Sugerencias sobre el formato visual de la página web.
4. **Encuesta Cuantitativa** (5 min)
   - Evaluación en Escala Likert (1-5) sobre la experiencia del prototipo.

---

## Métricas de Evaluación

### Usabilidad
- Facilidad de interpretación del dashboard web (1-5).
- Percepción de utilidad del sistema (1-5).
- Nivel de confianza en la precisión del sensor (1-5).

### Impacto ODS (Proyectado)
- **Tiempo ahorrado:** Minutos estimados de reducción en la búsqueda de estacionamiento.
- **Reducción de emisiones:** Disminución proyectada de gases de combustión en ralentí.
- **Eficiencia de flujo:** Reducción de la congestión vehicular en las vías internas del campus.

### Desempeño Técnico
- **Tiempo de respuesta:** Latencia entre la detección del "auto" (mano) y la actualización en Firebase.
- **Falsos positivos:** Eficacia del filtro por software (4 lecturas confirmadas) frente a interrupciones rápidas (ej. una persona caminando).
- **Precisión del sensor:** Capacidad del VL53L0X para detectar consistentemente el obstáculo a <500 mm.

---

## Análisis de Resultados (Simulación)

### Cuantitativo
- **Latencia del sistema:** El tiempo promedio desde la interrupción del láser hasta el cambio visual en la web es de ~2 segundos, lo cual es óptimo para el caso de uso.
- **Tasa de precisión:** El sensor logra un 100% de precisión simulada bajo los 50 cm establecidos en el código.

### Cualitativo
- **Feedback recurrente:** Los usuarios valoran mucho la simplicidad de la interfaz web básica (verde/rojo).
- **Sugerencias de mejora:** Los usuarios sugieren integrar este sistema directamente en una aplicación móvil de la universidad o en paneles LED físicos en la entrada de los estacionamientos.

---

## Validación de Impacto ODS

**ODS Seleccionado:** 11 - Ciudades y comunidades sostenibles

**Meta específica del proyecto:** Reducir la huella de carbono local y optimizar el tiempo de los estudiantes eliminando el tránsito ocioso de vehículos buscando estacionamientos libres en el campus.

**Indicadores de impacto (Proyectados a escala real):**
1. **Tiempo de búsqueda de estacionamiento** - Baseline: 5-10 minutos en hora punta. Meta: < 2 minutos.
2. **Distancia ociosa recorrida** - Baseline: 1-2 km adicionales dando vueltas. Meta: Tránsito directo al espacio disponible.

**Proyección de impacto a escala:**
Si el prototipo se despliega y escala a todos los cajones de estacionamiento de la UAI, los estudiantes podrían consultar la disponibilidad antes de subir por la ruta hacia la universidad (ej. desde Pie Andino o Avenida Grecia). Esto eliminaría miles de horas anuales de motores en ralentí, disminuyendo drásticamente la contaminación acústica y atmosférica, y mitigando el estrés de la comunidad estudiantil.