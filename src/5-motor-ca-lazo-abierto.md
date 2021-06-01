---
title: Control de velocidad en lazo abierto para un motor de CA
...
## Modelo

![**Figura**. Diagrama esquemático de un motor a pasos (*Fuente: [How to Wire Stepper Motors](https://buildbotics.com/wiring-stepper-motors/)*).](https://buildbotics.com/content/images/2019/09/4wireMotor.png){width=50%}

![**Figura**. Diagrama esquemático del devanado A (*Fuente: [Stepper Motor](https://es.mathworks.com/help/physmod/sps/powersys/ref/steppermotor.html)*)](https://es.mathworks.com/help/physmod/sps/powersys/ref/hystm_emf.gif){width=50%}

### Subsistema eléctrico

$$v_a = L_a \frac{di_a}{dt} + R_a i_a + e_a$$
$$v_b = L_b \frac{di_b}{dt} + R_b i_b + e_b$$

### Subsistema mecánico

$$J\frac{d\omega}{dt} = \tau_D - B\omega - \tau_L$$

### Interacciones

(*Fuente para las interacciones:
https://core.ac.uk/download/pdf/148670797.pdf#page=39*)

$$e_a = -K_m \omega \sin (p\theta)$$
$$e_b = K_m \omega \cos (p\theta)$$
$$\tau_D = -K_m i_a \sin p\theta + K_m i_b \cos p\theta$$

### Modelo dinámico

$$L_a \frac{di_a}{dt} + R_a i_a = v_a + K_m \omega \sin (p\theta)$$
$$L_b \frac{di_b}{dt} + R_b i_b = v_b - K_m \omega \cos (p\theta)$$
$$J\frac{d\omega}{dt} + B\omega = - K_m i_a \sin p\theta + K_m i_b \cos p\theta - \tau_L$$


## Control de velocidad en lazo abierto
Usando la linealización tecnológica

$$i_a = -I \sin p\theta$$
$$i_b = I \cos p\theta$$

$$J\frac{d\omega}{dt} + B\omega =  K_m I \sin^2 p\theta + K_m I \cos^2 p\theta - \tau_L$$

$$J\frac{d\omega}{dt} + B\omega =  K_m I - \tau_L$$

Entonces

$$v_a = -L_a I \cos p\theta - R_a I \sin p\theta - K_m \omega \sin (p\theta)$$

por otro lado

(*https://en.wikipedia.org/wiki/List_of_trigonometric_identities#Sine_and_cosine*)

$$a \cos\gamma + b\sin\gamma = c \cos(\gamma+\phi)$$

$$c = sgn(a)\sqrt{a^2+b^2}$$
$$\phi = \arctan\left(-\frac{b}{a}\right)$$

Entonces

$$v_a = -L_a i \cos p\theta - (R_a i + K_m \omega) \sin (p\theta)$$

$$v_a = V_p \cos(p\theta + phi)$$

* [Controlador Variable de Frecuencia - VFD para motores AC | Pr#98](https://youtu.be/I3MjAyZ-Tn0)

## Implementación

* [How to Wire Stepper Motors](https://buildbotics.com/wiring-stepper-motors/)
* [Arduino Bipolar Stepper Motor Control](https://simple-circuit.com/arduino-bipolar-stepper-motor-control/)
* [L293D Quadruple Half-H Drivers](https://www.ti.com/lit/ds/symlink/l293d.pdf)
* [L298N Dual Full-Bridge Driver](https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf)