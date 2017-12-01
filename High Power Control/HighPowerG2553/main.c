#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    //Timers Config
    P1DIR |= BIT0;                                // Set Pin as output
    P1OUT |= BIT0;
    TA0CCTL0 = CCIE;                              // TACCR0 interrupt enabled
    TA0CCR0 = 15000;                              //15 kHz
    TA0CTL = TASSEL_1 | MC_1;                     // ACLK, up mode
     __bis_SR_register(GIE);
     while(1);
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void)
{
    P1OUT ^= BIT0;                                  //Turn on and off aka square wave
}
