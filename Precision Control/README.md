#Lab 6: Precision Control

In lab 6, finer control of the PWM output is used to create an analog voltage. This can be accomplished in several ways through the use of a Digital-to-Analog Convertor, or DAC. The two DAC configurations analyzed in this part of the lab are through a low pass filter, or more specifically an integrator circuit, as well as an R2R ladder. 

##PWM Part 2

As if low pass filters aren't magical enough, one of the forms of an active low pass filter is the integrator, which takes the integral of the signal. By operating near the cutoff frequency of the low pass filter, it was observed that the circuit could take a square wave PWM signal from the MSP4305529 and convert it to a triangle waveform. This makes sense since the integral of a square wave is a triangle wave. In the picture below you can see this phenomenon. The circuit used was a third order low pass filter with a cutoff frequency of 20 Hz.

##R2R DAC

A much more sophisticated form of a DAC is through an R2R ladder. This circuit operates through the useful properties of how equivalent resistance is calculated through resistors in series and parallel. By using the ratio of resistors R and 2R, a digital signal can be converted to an analog one. An 8 bit R2R ladder was created using the circuit shown below.

Since the DAC is 8 bits, any voltage increment of Vcc/(2^8) can be outputted. Vcc of the MSP430F5529 is 3.3V, so this means the DAC can output 255 discrete analog voltages between 0 and 3.3 V in 13 mV increments. The DAC was tested using the MSP430 by incrementing a digital counter and outputting the digital signal over a GPIO pin. The video of the test can be seen below.

##Triangle Wave

Next the DAC was tested using a triangle waveform from the MSP430F5529. This was accomplished using the counter above, however once reaching Vcc, the counter was decremented to 0, repeating forever. The triangle wave had a frequency of 1 kHz and used a field to specify the direction of the counter. A picture of the resulting triangle wave and the FFT are shown in the oscilloscope screenshot below.

##Loading Effects

An interesting discovery in this lab was investigating the loading effect, which influenced the behavior of the DAC circuits. Different loads were used to drive the DAC circuits from 100 Ohms to 10 kOhms. Besides the higher value loads being more sensitive to noise, the shape of the output waveforms remained the same. What did change however, was the amplitude of the waveforms.

##Bill of Materials
x3 510 Ohm 0.25 W resistors
x1 1 MOhm 0.25 W resistor
x9 15 kOhm 0.25 W resistors
x7 7.5 kOhm 0.25 W resistors
x3 15 uF 25VDC 85 degrees C capacitors
