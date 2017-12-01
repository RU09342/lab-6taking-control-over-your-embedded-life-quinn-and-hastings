# Lab 6: Open Loop Systems
The MSP430F5529 was chosen due to our comfort with this board. It was the board that we simply agreed would be the easier for us to use for this open loop system.

## Voltage Regulator
A UA7805C 5v voltage regulator was used within this system.

## Fan Control
For this application, we used a PWM signal from the F5529 to control the speed of the CPU fan. This PWM is automatically set based on the desired temperature.

## Temperature Reading
The temperature of the 5v regulator is measured by an LM35 temperature sensor and outputted as a voltage that is deciphered as being 10mv/degree celcius.


## System Modeling
In order to formulate our control software, we first needed to collect data on the performane of our open loop system. The CPU fan was set to PWM duty cycles ranging from 100/1000 - 900/1000 at intervals of 100 and the temperature of the Voltage regulator was measured at each duty cycle. These data gave us a plot of PWM vs. temperature that could be sectioned into 3 piece wise linear functions. Within our code, it can be seen that one of these piece wise linear functions is used if the desired temperature falls within the temperature bounds of a given function in order to set the fans PWM.

## Open Loop Control System
In order to implement this software for an open loop system such as the one shown below, the OpenLoop folder should be downloaded and the main.c code should be ran on an MSP430F5529. In order to select a desired temperature, you must manually assign the variable 'temp' to that temperature. For communicating PWM to your fan, connect the PWM pin of the CPU fan to pin P1.5. For reading over UART, connect the transmission wire to P3.3 and the read wire to P3.4. Our software allows users to enter any temperature that they want, but will treat any temperature lower than 40 as 40 and any temperature higher than 72 as 72. Once the temperature is read in, the duty cycle is set to the predicted value given by one of the three piece wise functions.

![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-quinn-and-hastings/blob/master/Open%20Loop%20Systems/openLoopCircuit.png)


## Deliverables
Your README needs to contain schematics of your system, the plot of the temperature and input voltages at the 5C steps, and a brief talk about why you chose the processor you did along with the control technique for the fan. As always, you should include a brief description of the code you generated to run the experiment. You need to also include information on how to use your control software, including what inputs it is expecting and what range of values you are expecting. At this time you are not going to need to user-proof the system, but you will for the milestone, so keep it in the back of your head.


### What your README and code doesn't need
For starters, note the fact I ask you to do this with only one board. You also do not need to give me all of your code in the README, just tell me functionally what is going on along with showing off any functions you may have made.

Your code *DOES NOT* need to perform any sort of closed loop control. Save that for the milestone. This means that your system does not need to try to actively change the fan speed without your help. You are going to essentially make your microcontroller one big Convert-o-Box to turn a desired temperature into a controllable signal, and then be able to read a temperature.