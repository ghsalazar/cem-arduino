---
title: Control de velocidad en lazo abierto para un motor de CA
...
## Modelo

![**Figura**. Diagrama esquemático de un motor a pasos (*Fuente: [How to Wire Stepper Motors](https://buildbotics.com/wiring-stepper-motors/)*).](https://buildbotics.com/content/images/2019/09/4wireMotor.png){width=50%}

![**Figura**. Diagrama esquemático del devanado A (*Fuente: [Stepper Motor](https://es.mathworks.com/help/physmod/sps/powersys/ref/steppermotor.html)*)](https://es.mathworks.com/help/physmod/sps/powersys/ref/hystm_emf.gif){width=50%}

(*Fuente para las interacciones: https://core.ac.uk/download/pdf/148670797.pdf#page=39*)

$$v_a = L_a \frac{di_a}{dt} + R_a i_a + e_a$$
$$v_b = L_b \frac{di_b}{dt} + R_b i_b + e_b$$

$$J\frac{d\omega}{dt} = \tau_D - B\omega - \tau_L$$

$$e_a = -K_m \omega \sin (p\theta)$$
$$e_b = K_m \omega \cos (p\theta)$$

$$\tau_D = K_m (−i_a sin p\theta + i_b cos p\theta)$$

## Control de velocidad en lazo abierto

## Implementación


* [How to Wire Stepper Motors](https://buildbotics.com/wiring-stepper-motors/)
* [Arduino Bipolar Stepper Motor Control](https://simple-circuit.com/arduino-bipolar-stepper-motor-control/)
* [L293D Quadruple Half-H Drivers](https://www.ti.com/lit/ds/symlink/l293d.pdf)
* [L298N Dual Full-Bridge Driver](https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf)