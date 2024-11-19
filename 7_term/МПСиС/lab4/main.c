#include <msp430.h>

#define LED1 BIT0  // P1.0
#define LED3 BIT2  // P8.2

#define PAD2 BIT1  // P6.1

#define POTENTIOMETER BIT5  // P6.5


void enLed1(int f) {

    switch (f) {
        case 0:
            P1OUT &=~LED1;
            break;
        case 1:
            P1OUT |= LED1;
            break;
    }
}

void enLed3(int f) {

    switch (f) {
        case 0:
            P8OUT &=~LED3;
            break;
        case 1:
            P8OUT |= LED3;
            break;
    }
}


void set_pins() {
    // P6.1 (PAD2) & P6.5 (POT) set as input
    P6DIR &=~(PAD2 | POTENTIOMETER);
    // // device mode: P6.4 is PAID 2, P6.5 is POT
    P6SEL |= (PAD2 | POTENTIOMETER);
    // переключаем в режим периферийных устройств
    P1DIR |= BIT6; // P1.6 (CBOUT) set as output
    P1SEL |= BIT6; // device mode: P1.6 is CBOUT

    P8DIR |= BIT0 | BIT2; // P8.0 (Vee POT) set as output
    P8SEL &=~(BIT0 | BIT2); // P8.0 is digital I/O
    P8OUT |= BIT0; // Set Vcc to PUT
    P8OUT &=~BIT2;
    // P1.0 (LED1) set as output
    P1DIR|= LED1;
    P1SEL &=~LED1; // LED is digital I/O
    P1OUT = 0;
}


void set_comp() {
    // // Enable both comparator input,
    // // CBIP(+) = A5 (POT), CBET(-) = A 1 (PAD 2)
    CBCTL0 = CBIMEN | CBIPEN | CBIPSEL_5 | CBIMSEL_1;
    // CPMIN - Разрешение входного канала на V-;
    // CBIPEN - Разрешение входного канала на V+;
    // CBIMSEL - Выбор входного канала V-;
    // CBIPSEL - Выбор входного канала V+;
    // Enable Comparator, Enable out filter 3600 ns delay
    CBCTL1 = CBON | CBF | CBFDLY_2;
    // CBON - Включение компаратора;
    // CBF - Выходной фильтр ;
    // CBFDLY - Величина задержки фильтра (0.6, 1.0, 1.8, 3.4 мкс);
}


void set_timer() {
    TA0CCTL0 = CCIE; // CCR0 interrupt enabled
    // // SMCLK, no divide, cont mode, clear TAR
    TA0CTL = TASSEL_2 | ID_0 | MC_2 | TACLR ;
    // TASSEL 2 - источник тактов SMCLK по умолчанию настроенных на работу от DC0
    // (разрешен даже при режиме энергопотребелния)
    // ID_0 - делитель частоты
    // МC_2 - реверсивный режим
}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    set_pins();
    set_timer();
    set_comp();

    __bis_SR_register(LPM0_bits + GIE);
    __no_operation();
    return 0;
}

// Timer0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) {

    // disable leds
    enLed3(0);
    enLed1(0);

    // CBCTL - Величина задержки фильтра (0.6, 1.0, 1.8, 3.4 мкс)
    // CBOUT - Выход компаратора

    if(CBCTL1 & CBOUT) {
        enLed3(1);
    }
    else {
        enLed1(1);
    }
}
