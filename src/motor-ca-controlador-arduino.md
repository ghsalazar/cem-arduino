---
title:  Implementación de un inversor bifásico con Arduino
author: Gastón Hugo Salazar Silva
...

Los motores de corriente alterna (CA) son los motores que más se usan en la
industria. Usualmente se utilizan para mantener una velocidad constante. Para
ello, utilizamos [controladores de frecuencia
variable](https://es.wikipedia.org/wiki/Variador_de_frecuencia) (VFD, por sus
siglas en inglés), también llamados variadores de frecuencia. Estos
controladores operan en lazo abierto.

A continuación, presentaremos una implementación simple de un inversor bifásico
para un motor a pasos. Utilizamos una tarjeta [Arduino
UNO](https://store.arduino.cc/usa/arduino-uno-rev3) para desarrollar la
aplicación. Hay que recordar que un motor a pasos es un motor de corriente
alterna síncrono bifásico.

## Circuito

![**Figura 1**. Circuito de inversor bifásico para un motor a pasos.](https://github.com/ghsalazar/cem-arduino/raw/main/assets/static/cem-two-phase-inverter.PNG)

En la figura 1, podemos ver el circuito de inversor bifásico para un motor a
pasos. Por limitaciones de la plataforma, tuvimos que sustituir cada devanado
del motor a pasos con un inductor y una resistencia. Como ya mencionamos,
utilizamos una tarjeta Arduino UNO. Para la etapa de potencia, nos valimos del
circuito integrado [L293D](https://www.ti.com/lit/ds/symlink/l293d.pdf), que
contiene 4 medios puentes H.

Para ver el circuito y el código del modelo de la figura 3, pueden revisar el
siguiente [enlace en
TinkerCAD.](https://www.tinkercad.com/things/f8KcIgQaXO9-fantastic-luulia-albar/editel?sharecode=zhruNH-anu7aVYLOEv2M0_MduvVZuNjC5G45cn84JnY)

## Código para Arduino UNO

Si bien es posible desarrollar código para Arduino en el lenguaje C, tenemos que
es más accesible usar la entorno [Wiring](http://wiring.org.co/) empleado por la
tarjeta. Sin embargo, Wiring se soporta por medio del lenguaje C++ y
aprovecharemos algunas de las capacidades propias del mismo lenguaje.

Presentamos el código desarrollado en el siguiente listado.

<script src="http://gist-it.appspot.com/https://github.com/ghsalazar/cem-arduino/raw/main/examples/two-phase-inverter.ino"></script>

A continuación, explicaremos con detalle el código. Primeramente, tenemos el
encabezado, que simplemente es un comentario para identificar el código y su
autoría, así como explicar brevemente de que se trata.

<<two-phase-inverter.ino>>=
/// @file   two-phase-inverter.ino
/// @author Gastón Hugo Salazar Silva <ghsalazar@ipn.mx>
/// @date   2021-06-03
/// @brief  Implementación de un inversor simple 
///         sobre la tarjeta Arduino UNO

@

Como empleamos el circuito integrado
[L293D](https://www.ti.com/lit/ds/symlink/l293d.pdf) para la etapa de potencia,
tenemos que debemos usar el pin 1 del integrado para habilitar dos medios
puentes H por medio de la salida digital D6 de Arduino. Cómo D6 se encuentra en
el bit con la séptima posición en el puerto D del microcontrolador
[ATmega328p](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf),
utilizamos la constante `ENABLE_1` para especificar eso.

<<two-phase-inverter.ino>>=
const int ENABLE_1 = 1 << 6;
@

Utilizamos una constante en lugar un símbolo definido (`#define`), porque nos
permite identificar errores por medio de los mecanismos propios del compilador y
el depurador.

Luego, empleamos la constante `ENABLE_2` para habilitar los otros dos medios
puentes H, por medio del pin 9 del L293D y la salida digital D7 del puerto D del
ATmega328p, como se encuentra en la octava posición del puerto D.

<<two-phase-inverter.ino>>=
const int ENABLE_2 = 1 << 7;
@

Además, más adelante tendremos que registrar en la variable DDRD que salidas
utilizaremos. Para ello usaremos la máscara `OUTPUTS`. Como usaremos los cuatro
medios puentes H, necesitaremos cuatro salidas digitales de la tarjeta Arduino
UNO. Seleccionamos las salidas digitales que van de D2 a D5 para ellos. 

<<two-phase-inverter.ino>>=
const int OUTPUTS  = 0b1111 << 2;

@

No produciremos una señal sinusoidal como tal; sino aproximaremos la señal
sinusoidal por medio de una onda cuadrada. Como necesitamos dos fases para el
motor a pasos, usaremos dos ondas cuadradas con 90° eléctricos de separación.

Además, cada inversor requiere de un puente H completo, por lo que necesita dos
señales para activarlo. El arreglo `output` contiene valores constantes que al
ser referenciados en secuencia produce las señales necesarias para producir las
formas de onda requeridas por los devanados del motor a pasos. 

<<two-phase-inverter.ino>>=
const int output[] { 
  0b1001 << 2,
  0b1010 << 2,
  0b0110 << 2,
  0b0101 << 2
};

@

La constante `STATES` es una máscara que utilizaremos para acotar el número de
estados que puede generar el programa.

<<two-phase-inverter.ino>>=
const int STATES   = 0b11;

@

Como estamos trabajando con el entorno de Wiring, debemos tener dos funciones
definidas: `setup` y `loop`. En la función `setup`, sólo registraremos en la
variable `DDRD` que elementos del puerto D son salidas. En este caso, están
definidos por las constantes `ENABLE_1`, `ENABLE_2` y `OUTPUTS`.

<<two-phase-inverter.ino>>=
void setup()
{
  DDRD = ENABLE_2 | ENABLE_1 | OUTPUTS;         //Setting pins for output
}

@

La siguiente función que se debe definir de forma obligatoria es `loop`.

<<two-phase-inverter.ino>>=
void loop()
{
@

Diseñamos el programa para operar como un [autómata
temporizado](https://en.wikipedia.org/wiki/Timed_automaton). En la figura 2,
podemos ver el grafo con el conjunto de los estados posibles y sus transiciones.

![**Figura 2**. Grafo de estados del inversor.](https://github.com/ghsalazar/cem-arduino/raw/main/assets/figures/two-phase-inverter-states.png)

Establecemos en qué estado está el autómata por medio de la variable `state`. Es
una [variable
estática](https://es.wikipedia.org/wiki/Variable_est%C3%A1tica#%C3%81mbito) de
la función `loop`; esto quiere decir que es como una variable global pero solo
puede ser accedida desde el ámbito de la propia función. Se inicializa con un
valor cero.

<<two-phase-inverter.ino>>=
  static int state = 0;

@

Es importante que recalquemos que la variable `state` es la que lleva el ritmo
de trabajo del inversor.

El siguiente estado se define incrementando en 1 el estado actual y
enmascarándolo con la constante `STATES`.

<<two-phase-inverter.ino>>=
  state = (++state) & STATES;                   // State update
@

Los pines de salida se actualizan en una sola operación al asignarle a `PORTD`
los bits que se deben encender y apagar. El arreglo output determina a partir
del estado que medio puente se enciende o apaga. 

<<two-phase-inverter.ino>>=
  PORTD = ENABLE_2 | ENABLE_1 | output[state];  // Output setting
@

Finalmente, la frecuencia de las señales cuadradas se determina a partir de la
pausa que se da. En este caso son 1 000 ms para cada estado, por lo que la
frecuencia es 0.25 Hz.

<<two-phase-inverter.ino>>=
  delay(1000);                                  // Waiting time in milliseconds
}
@

## Conclusiones

Mostramos una implementación simple de un inversor bifásico
para un motor a pasos con una tarjeta Arduino
UNO.

Hay que recordar que un motor a pasos es un motor de corriente alterna síncrono
bifásico, y este ejemplo nos sirve para entender el funcionamiento básico de un
VFD. Los VFD se utilizan en la industria para controlar la velocidad de los
motores en la industria.

## Para saber más

* [How to Wire Stepper Motors](https://buildbotics.com/wiring-stepper-motors/)
* [Arduino Bipolar Stepper Motor Control](https://simple-circuit.com/arduino-bipolar-stepper-motor-control/)
* [L293D Quadruple Half-H Drivers](https://www.ti.com/lit/ds/symlink/l293d.pdf)
* [L298N Dual Full-Bridge Driver](https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf)