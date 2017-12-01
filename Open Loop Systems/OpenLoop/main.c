#include <msp430.h> 


/**
 * main.c
 */
int on = 997;
int duty;
int temp;
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //UART INIT
    P3SEL |= BIT3+BIT4;                       // P3.3,4 = USCI_A0 TXD/RXD
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 6;                              // 1MHz 115200 (see User's Guide)
  UCA0BR1 = 0;                              // 1MHz 115200
  UCA0MCTL |= UCBRS_0 + UCBRF_13 + UCOS16;            // Modulation UCBRSx=1, UCBRFx=0
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

  // Configure ADC12
          REFCTL0 &= ~REFMSTR;
      ADC12CTL0 = ADC12SHT0_2 + ADC12ON + ADC12REFON;      // Sampling time, S&H=16, ADC12 on
      ADC12CTL1 = ADC12SHP;                   // Use sampling timer
      ADC12CTL2 |= ADC12RES_2;                // 12-bit conversion results
      ADC12MCTL0 |= ADC12INCH_4 + ADC12SREF_1;              // A1 ADC input select; Vref=AVCC

    //Timer setup
    TA0CTL |= TBIE;             //enable TA0 interrupt
    TA0CCTL0 |= CCIE;              //enable CCR0 interrupt
    TA0CCTL0 &= ~TAIFG;            //clear flag
    TA0CCTL1 |= CCIE;              //enable CCR1 interrupt
    TA0CCTL1 &= ~TAIFG;            //clear flag

    temp = 40;                     //baseline temperature
    if(temp <= 41) {
        duty = -14.29*temp+671.43; //equation 1 based on test data
    }
    else if(temp > 41 && temp <= 72) {
        duty = -2.226*temp+165.7541; //equation 2 based on test data
    }
    else {//temp > 72
        duty = -.3497*temp+35.1748; //equation 3 based on test data
    }
    on = duty*10;                   //convert duty cycle based on 1 kHz

    TA0CTL = TASSEL_2 + MC_1 + ID_0;           // SMCLK, upmode, clk/1
    TA0CCR1 = on;                               //duty cycle
    TA0CCR0 = 1000;                             //1 kHz signal

    P1DIR |= BIT5;       // P1.5 pin output
    P1OUT |= BIT5;      //pwm output

    //ADC pin setup
        P6SEL |= BIT4;                         // Configure P6.4 for ADC
        P1DIR |= BIT2;
        P1SEL |= BIT2;

    __bis_SR_register(GIE);  //not low power mode
    while(1){
        ADC12CTL0 |= ADC12ENC | ADC12SC; //Sample ADC
        temp1 = ((ADC12MEM0*1.5)/4096)*100; //convert to decimal temperature in celcius
        while (!(UCA0IFG&UCTXIFG));         //Transmit ready?
        UCA0TXBUF = temp1;                  //UART transmit
        __delay_cycles(1000);               //delay so there's not ten billion samples
    } //needed since not in LPM
    // Enter LPM0 w/ interrupt
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void) { //timer a0 interrupt service routine
    P1OUT |= BIT5; //turn on
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR(void) { //a1 timer interrupt
    switch(TA0IV){
    case 2://CCR1
    P1OUT &= ~BIT5; //turn off
    break;
    }
}
//UART Read Input
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) {
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    temp = UCA0RXBUF;                       //set a new temperature
}
