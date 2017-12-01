#include <msp430.h> 


/**
 * main.c
 */
int counter = 0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    TA0CTL |= TBIE;             //enable TA0 interrupt
    TA0CCTL0 |= CCIE;              //enable CCR0 interrupt
    TA0CCTL0 &= ~TAIFG;            //clear flag

    TA0CTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK, upmode, clk/1
    TA0CCR0 = 10000;                             //100 Hz signal

    P1DIR |= BIT0;                                  //output pin 1.0
    P3DIR |= BIT5 | BIT6;                           //output pin 3.5 and 3.6
    P6DIR |= BIT0 | BIT1 | BIT2 | BIT3 | BIT4;      //output pin 6.0 - 6.4
    P7DIR |= BIT0;                                  //output pin 7.0

    __bis_SR_register(GIE);  //not low power mode
    while(1){
    } //needed since not in LPM
    // Enter LPM0 w/ interrupt
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void) { //timer a0 interrupt service routine
    P1OUT ^= BIT0; //blink led 1.0
    int bit0 = counter & BIT0;      //represents 2^0
    int bit1 = counter & BIT1;      //represents 2^1
    int bit2 = counter & BIT2;      //represents 2^2
    int bit3 = counter & BIT3;      //represents 2^3
    int bit4 = counter & BIT4;      //represents 2^4
    int bit5 = counter & BIT5;      //represents 2^5
    int bit6 = counter & BIT6;      //represents 2^6
    int bit7 = counter & BIT7;      //represents 2^7
    if(bit0) {
        P3OUT |= BIT5;  //turn on 3.5
    }
        else {
            P3OUT &= ~BIT5; //turn off 3.5
        }
    if(bit1) {
            P3OUT |= BIT6;  //turn on 3.6
    }
        else {
            P3OUT &= ~BIT6;  //turn off 3.6
        }
    if(bit2) {
            P7OUT |= BIT0;   //turn on 7.0
        }
        else {
            P7OUT &= ~BIT0;  //turn off 7.0
        }
    if(bit3) {
            P6OUT |= BIT4;  //turn on 6.4
        }
        else {
            P6OUT &= ~BIT4;  //turn off 6.4
        }
    if(bit4) {
            P6OUT |= BIT3;  //turn on 6.3
        }
        else {
            P6OUT &= ~BIT3;  //turn off 6.3
        }
    if(bit5) {
            P6OUT |= BIT2;   //turn on 6.2
        }
        else {
            P6OUT &= ~BIT2;  //turn off 6.2
        }
    if(bit6) {
            P6OUT |= BIT1;   //turn on 6.1
        }
        else {
            P6OUT &= ~BIT1;   //turn off 6.1
        }
    if(bit7) {
            P6OUT |= BIT0;   //turn on 6.0
        }
        else {
            P6OUT &= ~BIT0;  //turn off 6.0
        }
    counter++;               //increment 8bit counter
}




