### Lab 6: "High Power" Control

In lab 6, pulse width modulation was used to control the switching of a relay and a high side switch for high power. With respect to the MSP, high power is anything that can damage the microprocessor. That is why it is important for devices like relays and mosfets to isolate something high such as 12V. High power is necessary when the MSP430 is not sufficient to provide the necessary voltage or current draw of the external circuit. The MSP430G2553 was used to create a square wave PWM signal with an assigned duty cycle.

## Switching

For this lab, two different devices are used to control switching. The first is the relay, which is an electro-mechanical device. The other is the well-known and beloved mosfet, in this case the 2N7000 N-MOS configured as a high side switch. 

## Relays

A relay is an electro-mechanical system which can open and close a switch based on an input. Since they physically rely on the movement of a switch, the switching speed is limited by how fast the switch can move from terminal to terminal. You can see this effect in the video below where the PWM frequency is increased and decreased.

By experimentation, it was determined that the maximum switching speed of the relay is 180 Hz, as shown in the picture below.

## MOSFET Switching

The MOSFET high side switch is a circuit that is tied to Vcc, or in this case 12V, and drives a load when the PWM signal is high. MOSFET's not only provide a much greater maximum switching speed, they also require an input current of 0A which is extremely useful since this removes any chance of drawing too much current from the MSP430. In the video below it was experimentally determined that the MOSFET could achieve a maximum switching speed of 20 kHz. 

