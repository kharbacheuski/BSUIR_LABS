#include <msp430.h>

// Определение кнопок и светодиодов
#define BUTTON1 BIT1       // Кнопка 1
#define BUTTON2 BIT2       // Кнопка 2
#define LED1 BIT0          // LED для индикации активного режима
#define LED3 BIT1          // LED для индикации режима пониженного энергопотребления
#define LED4 BIT2          // LED для индикации высокого напряжения
#define LED5 BIT3          // LED для индикации низкого напряжения
#define LED8 BIT7          // LED, управляемый таймером

// Функция настройки тактовой частоты DCO и ACLK
void configureClocks() {
    // Настройка Vcore и тактовой частоты DCO на 0.3 МГц
    PMMCTL0_H = PMMPW_H;                // Разблокировать управление PMM
    PMMCTL0_L = PMMCOREV_0;             // Установить Vcore = 1.8V
    
    UCSCTL3 = SELREF_2;                 // Установка FLL для работы с REFO
    UCSCTL4 = SELA_1;                   // ACLK выбирает источник VLOCLK
    
    __bis_SR_register(SCG0);            // Отключить FLL для настройки
    UCSCTL0 = 0x0000;                   // Установить DCOx и MODx
    UCSCTL1 = DCORSEL_0;                // Настройка диапазона для 0.3 МГц
    UCSCTL2 = FLLD_1 + 30;              // Настроить DCOCLK на 0.3 МГц (при помощи FLL)
    __bic_SR_register(SCG0);            // Включить FLL
}

// Настройка таймера для визуального отображения частоты
void configureTimer() {
    TA0CTL = TASSEL_1 + MC_1 + TACLR;   // ACLK, Up Mode
    TA0CCR0 = 12000;                    // Установка периода таймера для видимой частоты
    TA0CCTL0 |= CCIE;                   // Включить прерывание от таймера
}

// Основная функция
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;           // Остановка Watchdog Timer
    
    // Настройка портов для светодиодов и кнопок
    P1DIR |= LED1 + LED3 + LED4 + LED5; // Светодиоды как выходы
    P1OUT &= ~(LED1 + LED3 + LED4 + LED5); // Сброс значений светодиодов
    
    P2DIR &= ~(BUTTON1 + BUTTON2);      // Кнопки как входы
    P2REN |= BUTTON1 + BUTTON2;         // Включить подтягивающие резисторы
    P2OUT |= BUTTON1 + BUTTON2;         // Установить резисторы как pull-up

    configureClocks();                  // Настройка тактовой частоты
    configureTimer();                   // Настройка таймера
    
    __enable_interrupt();               // Включить прерывания
    
    while (1) {
        if (!(P2IN & BUTTON1)) {        // Если нажата кнопка 1
            P1OUT ^= LED1;              // Переключение светодиода LED1 (активный режим)
            P1OUT ^= LED3;              // Переключение светодиода LED3 (режим пониженного потребления)
            
            if (P1OUT & LED1) {
                configureClocks();      // Настройка частоты для активного режима
                P1OUT |= LED4;          // Включить LED4 при высоком напряжении
                P1OUT &= ~LED5;         // Отключить LED5
            } else {
                P1OUT |= LED5;          // Включить LED5 при низком напряжении
                P1OUT &= ~LED4;         // Отключить LED4
                __bis_SR_register(LPM0_bits + GIE); // Войти в режим LPM0
            }
        }
        
        if (!(P2IN & BUTTON2)) {        // Если нажата кнопка 2
            __bic_SR_register_on_exit(LPM0_bits);   // Выйти из LPM0
        }
    }
}

// Обработчик прерывания таймера
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void) {
    P1OUT ^= LED8;                      // Переключение светодиода LED8 для визуализации частоты
}
