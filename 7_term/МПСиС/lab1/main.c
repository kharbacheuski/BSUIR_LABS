#include <msp430.h>

#define LED1 BIT1  // P1.0 - светодиод 1
#define S1   BIT7  // P1.7 - кнопка S1
#define S2   BIT2  // P2.2 - кнопка S2

void delay_ms(unsigned int ms) {
    while (ms--) {
        __delay_cycles(1000);  // Задержка на 1 мс при 1 МГц тактовой частоте
    }
}

void init_GPIO() {
    // Настраиваем диод как выходы
    P1DIR |= LED1;
    P1OUT &= ~LED1;  // Отключаем все диоды

    // Настраиваем кнопку S1 как вход с подтягивающим резистором
    P1DIR &= ~S1;   // Кнопка на вход
    P1REN |= S1;    // Включаем подтягивающий резистор
    P1OUT |= S1;    // Подтягиваем к Vcc

    P2DIR &= ~S2;   // Кнопка на вход
    P2REN |= S2;    // Включаем подтягивающий резистор
    P2OUT |= S2;    // Подтягиваем к Vcc
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // Останавливаем Watchdog Timer

    init_GPIO();  // Инициализация портов

    unsigned int s1buttonState = 1;
    unsigned int s2buttonState = 1;     // Текущее состояние кнопки (начальное состояние — отпущена)

    while (1) {
        // Читаем состояние кнопки S1 (логический 0 — кнопка нажата, логическая 1 — отпущена)
        s1buttonState = (P1IN & S1) ? 1 : 0;
        s2buttonState = (P2IN & S2) ? 1 : 0;

        if (s1buttonState == 0) {
            P1OUT |= LED1;
        } else if (s2buttonState == 0) {
            P1OUT &= ~LED1;
        }

        // Задержка для стабилизации опроса кнопки (дребезг)
        delay_ms(50);
    }
}
