#include <msp430.h>

int poten_mode; // Global potentiometer mode

int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    P1DIR &= ~(BIT7); // P1.7 (S1) set as input
    P1OUT |= BIT7; // P1.7 (S1) pull-up resistor
    P1REN |= BIT7; // P1.7 (S1) enable resistor

    // P6.0 (PAD1) & P6.1 (PAD2) & P6.5 (POT) set as input
    P6DIR &= ~(BIT0 | BIT1 | BIT5);

    // device mode: P6.0 is PAD1, P6.1 is PAD2, P6.5 is POT
    P6SEL |= (BIT0 | BIT1 | BIT5);

    P1DIR |= BIT6; // P1.6 (CBOUT) set as output
    P1SEL |= BIT6; // device mode: P1.6 is CBOUT

    P8DIR |= BIT0; // P8.0 (Vcc POT) set as output
    P8SEL &= ~BIT0; // P8.0 is digital I/O
    P8OUT |= BIT0; // Set Vcc to POT

    // P1.1 (LED PAD1) & P1.2 (LED PAD2) set as output
    P1DIR |= BIT1 | BIT2;
    P1SEL &= ~(BIT1 | BIT2); // LED is digital I/O

    // Enable both comparator inputs,
    // CBIP(+) = A5 (POT), CBIM(-) = A0 (PAD1)
    CBCTL0 = CBIMEN | CBIPEN | CBIPSEL_5 | CBIMSEL_0;

    // Enable Comparator, Enable out filter 3600 ns delay
    CBCTL1 = CBON | CBF | CBFDLY_3;
    poten_mode = 1;

    P1IE |= BIT7; // P1.7 (S1) interrupt enable

    // P1.7 (S1) edge for interrupt: low-to-high
    P1IES &= ~(BIT7);
    TA0CCTL0 = CCIE; // CCR0 interrupt enabled

    // SMCLK, no divide, contmode, clear TAR
    TA0CTL = TASSEL_2 | ID_0 | MC_2 | TACLR ;
    __bis_SR_register(LPM0_bits + GIE);
    __no_operation();

    return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void) {
    poten_mode ^= BIT0; // change mode: POT or PAD2
    if(poten_mode) {
        CBCTL0 |= CBIPSEL_5; // set CBIP(+) = A5 (POT)
    }
    else {
        CBCTL0 |= CBIPSEL_1; // set CBIP(+) = A1 (PAD2)
    }

    P1IFG = 0; // reset interrupt flag
}

// Timer0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) {
    P1OUT &= ~(BIT1 | BIT2); // LED off
    
    if ( (CBCTL1 & CBOUT) == 0) {
        P1OUT |= BIT1; // LED PAD1 on
    }
    else if (!poten_mode)
        P1OUT |= BIT2; // LED PAD2 on
}
