# Lab 6: Open Loop Systems
The MSP430F5529 was chosen due to our comfort with this board. It was the board that we simply agreed would be the easier for us to use for this open loop system.

## Voltage Regulator
A linear voltage regulator is used to convert a 12V input to drive a load at a constant 5V. The regulator used was the UA7805C. The UA7805 is a three terminal device that can take in a varying voltage and still output a constant DC voltage of 5V. However as a linear regulator, the 7805 can only operate if its input voltage is greater than its output, in this case 5V.

## Fan Control
CPU fans are generically manufactured with two different designs, with the main difference being the addition or absence of a PWM input signal. In the case of this open loop system, the PWM signal was required in order for basic control of the fans speed. Using a PWM pin, a duty cycle could be used to control the speed of the fan. An Intel meant to be utilized within an I7 desktop computer was used in this application.

## Temperature Reading
An LM35 temperature sensor outputs a voltage that is dependent on the temperature of the device. Voltage outputs are expected to be in the units of (10mv/ \degree C), and can be interpreted by the MSP430F5529 micro-controller using logical computing in C. With the LM35, data about the performance of the open system can be dynamically interpreted and transmitted over a UART serial connection. 


## System Modeling
In order to formulate our control software, we first needed to collect data on the performane of our open loop system. The CPU fan was set to PWM duty cycles ranging from 100/1000 - 900/1000 at intervals of 100 and the temperature of the Voltage regulator was measured at each duty cycle. These data gave us a plot of PWM vs. temperature that could be sectioned into 3 piece wise linear functions. Within our code, it can be seen that one of these piece wise linear functions is used if the desired temperature falls within the temperature bounds of a given function in order to set the fans PWM.

![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-quinn-and-hastings/blob/master/Open%20Loop%20Systems/Rplot01.png)

## Open Loop Control System
In order to implement this software for an open loop system such as the one shown below, the OpenLoop folder should be downloaded and the main.c code should be ran on an MSP430F5529. In order to select a desired temperature, you must manually assign the variable 'temp' to that temperature. For communicating PWM to your fan, connect the PWM pin of the CPU fan to pin P1.5. For reading over UART, connect the transmission wire to P3.3 and the read wire to P3.4. Our software allows users to enter any temperature that they want, but will treat any temperature lower than 40 as 40 and any temperature higher than 72 as 72. Once the temperature is read in, the duty cycle is set to the predicted value given by one of the three piece wise functions.

![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-quinn-and-hastings/blob/master/Open%20Loop%20Systems/openLoopCircuit.png)

## Schematic
![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-quinn-and-hastings/blob/master/Open%20Loop%20Systems/Schematic.PNG)
