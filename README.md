# Robot Laberinto
Este proyecto de robot laberinto contiene el codigo base para testear los sensores ultrasonicos, así como tambien el diagrama de conexión.

## En la carpeta de fritzing:

Se encuentra el proyecto de fritzing, así como las partes que se usaron para realizar el circuito.
Además allí se encuentra la foto del esquema de conexión.

![Esquema de conexion](https://github.com/jjcampis/robot_laberinto/blob/main/Fotos/conexion_laberinto.png?raw=true)

## Códigos
En esta carpeta se encuentran los archivos ".ino" necesarios para probar los sensores como para el robot laberinto en si.
En caso de ser necesario se deben cambiar o bien los pines o la programación de las funciones avanzar, izquierda etc, en el caso de que no funcionen correctamente por favor testear esto antes de probar el robot en un entorno real.

**TODO:**
Se puede mejorar la parte de giros controlando con pines PWM los ENA y ENB del driver L298N.
Se puede mejorar aun más dividiendo la parte de los sensores con otro MCU ejemplo un ESP8266 o 32.
Se pueden añadir mas sensores (giroscopio, sensores de seguidor de linea).

