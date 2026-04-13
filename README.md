# Sistema de Liga de Futbol

**Estudiante:** Tomás Espinel Cohen

## Descripcion

Aplicacion de consola en C++ que gestiona una liga de futbol completa.
Permite registrar partidos, ver la tabla de posiciones, consultar el
historial de jornadas y listar todos los partidos jugados. El estado
de la liga persiste entre ejecuciones mediante archivos de texto.

## Compilar y ejecutar

# Desde la carpeta liga-futbol/ en Git Bash:

g++ src/main.cpp -o liga



./liga

## Formato de config.txt

El archivo usa pares clave=valor, uno por linea.
Las lineas que comienzan con # son comentarios y se ignoran.
Los equipos se listan repitiendo la clave equipo= una vez por cada equipo.

Ejemplo:

# Configuracion de la liga

nombre=AguilaLeague
victoria=10
empate=2
derrota=-5
equipo=Tombos
equipo=Rolos
equipo=Barrio
equipo=Costa
equipo=Campesinos

## Decisiones de diseño

**Tres structs separados**
Se usan ConfigLiga, Partido y Equipo para separar claramente
la configuracion, los resultados de partidos y las estadisticas
de cada equipo. Cada struct tiene una sola responsabilidad.

**Puntero en actualizarEquipo**
La funcion actualizarEquipo recibe un Equipo\* para modificar
el struct directamente en memoria, sin crear copias. Se llama
con \&tabla\[j] desde construirTabla.

**Delimitador pipe en partidos.txt**
Los campos se separan con | para evitar conflictos con espacios
en los nombres de equipos. Se parsea con getline y stringstream.

**Persistencia con registros.txt**
El contador de partidos se guarda en registros.txt al cerrar,
y se lee al iniciar, para que la liga continue donde quedo.

**Ordenamiento con desempate triple**
La tabla se ordena primero por puntos, luego por diferencia de
goles y finalmente por goles a favor, cubriendo todos los casos
de empate entre equipos.

**Deteccion de partido duplicado**
Antes de guardar un partido, ingresarPartido lee partidos.txt
y verifica que el mismo enfrentamiento no exista ya en la misma
jornada, en cualquier direccion (A vs B o B vs A).

