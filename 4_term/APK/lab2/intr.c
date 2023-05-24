#include <dos.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER_BASE_VECTOR 0x88 
#define SLAVE_BASE_VECTOR  0x08

void print_byte(char far* screen, unsigned char byte) {
  int bit;
  int i;

  for (i = 0; i < 8; ++i) {
    bit = byte % 2;
    byte = byte >> 1;
    *screen = '0' + bit; // выводим на текущую позицию видеоадаптера один бит маски
    screen += 2;
  }
}

void print(void) {
  char far* screen = (char far*)MK_FP(0xB800, 0); // возвращает дальний указатель по заданному сегменту (сегмент видеадаптера, смещение - 0)

  // Master mask
  print_byte(screen, inp(0x21)); // inp возвращает значение по заданному адресу, регистр масок ведущего контроллера
  screen += 18; // сдвиг для вывода в консоли

  // Slave mask
  print_byte(screen, inp(0xA1)); // регистр масок для ведомого контроллера

  screen += 142; // переход на следующую строку в консоли

  // Master request
  outp(0x20, 0x0A); // функции записывают данные непосредственно в порт ввода-вывода
  print_byte(screen, inp(0x20)); // регистр запроса для ведущего контроллера
  screen += 18;

  // Slave request
  outp(0xA0, 0x0A); // регистр запроса для ведомого контроллера
  print_byte(screen, inp(0xA0));

  screen += 142; // переход на следующую строку в консоли

  // Master service
  outp(0x20, 0x0B);
  print_byte(screen, inp(0x20));
  screen += 18;

  // Master service
  outp(0xA0, 0x0B);
  print_byte(screen, inp(0xA0));
}

// Master обработчики прерываний 
void interrupt (*old_irq0_handler)(void); // Системные часы, прерывание интервального таймера, возникает 18,2 раза в секунду.
void interrupt (*old_irq1_handler)(void); // прерывание от клавиатуры. Генерируется при нажатии и при отжатии клавиши. Используется для чтения данных с клавиатуры.
void interrupt (*old_irq2_handler)(void); // используется для каскадирования аппаратных прерываний в машинах класса AT.
void interrupt (*old_irq3_handler)(void); // прерывание асинхронного порта COM2
void interrupt (*old_irq4_handler)(void); // прерывание асинхронного порта COM1
void interrupt (*old_irq5_handler)(void); // прерывание от контроллера жесткого диска (только для компьютеров IBM PC/XT)
void interrupt (*old_irq6_handler)(void); // прерывание генерируется контроллером НГМД после завершения операции ввода/вывода
void interrupt (*old_irq7_handler)(void); // Генерируется, когда подключенный к адаптеру принтер готов к выполнению очередной операции. Обычно не используется

void interrupt new_irq0_handler(void) { print(); old_irq0_handler(); } // переопределение прерываний
void interrupt new_irq1_handler(void) { print(); old_irq1_handler(); }
void interrupt new_irq2_handler(void) { print(); old_irq2_handler(); } 
void interrupt new_irq3_handler(void) { print(); old_irq3_handler(); }
void interrupt new_irq4_handler(void) { print(); old_irq4_handler(); }
void interrupt new_irq5_handler(void) { print(); old_irq5_handler(); }
void interrupt new_irq6_handler(void) { print(); old_irq6_handler(); }
void interrupt new_irq7_handler(void) { print(); old_irq7_handler(); }


// Slave обработчики прерываний 
void interrupt (*old_irq8_handler)(void); // прерывание от часов реального времени
void interrupt (*old_irq9_handler)(void); // прерывание от контроллера EGA
void interrupt (*old_irq10_handler)(void); // зарезервировано
void interrupt (*old_irq11_handler)(void); // зарезервировано
void interrupt (*old_irq12_handler)(void); // зарезервировано
void interrupt (*old_irq13_handler)(void); // прерывание от арифметического сопроцессора
void interrupt (*old_irq14_handler)(void); // прерывание от контроллера жесткого диска
void interrupt (*old_irq15_handler)(void); // зарезервировано

void interrupt new_irq8_handler(void) { print(); old_irq8_handler(); }
void interrupt new_irq9_handler(void) { print(); old_irq9_handler(); }
void interrupt new_irq10_handler(void) { print(); old_irq10_handler(); }
void interrupt new_irq11_handler(void) { print(); old_irq11_handler(); }
void interrupt new_irq12_handler(void) { print(); old_irq12_handler(); }
void interrupt new_irq13_handler(void) { print(); old_irq13_handler(); }
void interrupt new_irq14_handler(void) { print(); old_irq14_handler(); }
void interrupt new_irq15_handler(void) { print(); old_irq15_handler(); }
//-----------------------------------------------------------------------------

void init_new_handlers(void) {
  old_irq0_handler = getvect(0x08); // принимаем старый(дефолтный) обработчик прерывания
  setvect(MASTER_BASE_VECTOR, new_irq0_handler); // устанавливаем по этому вектору переопределенный обработчик  

  old_irq1_handler = getvect(0x09);
  setvect(MASTER_BASE_VECTOR + 1, new_irq1_handler);

  old_irq2_handler = getvect(0x0A);
  setvect(MASTER_BASE_VECTOR + 2, new_irq2_handler);

  old_irq3_handler = getvect(0x0B);
  setvect(MASTER_BASE_VECTOR + 3, new_irq3_handler);

  old_irq4_handler = getvect(0x0C);
  setvect(MASTER_BASE_VECTOR + 4, new_irq4_handler);

  old_irq5_handler = getvect(0x0D);
  setvect(MASTER_BASE_VECTOR + 5, new_irq5_handler);

  old_irq6_handler = getvect(0x0E);
  setvect(MASTER_BASE_VECTOR + 6, new_irq6_handler);

  old_irq7_handler = getvect(0x0F);
  setvect(MASTER_BASE_VECTOR + 7, new_irq7_handler);

  old_irq8_handler = getvect(0x70);
  setvect(SLAVE_BASE_VECTOR, new_irq8_handler);

  old_irq9_handler = getvect(0x71);
  setvect(SLAVE_BASE_VECTOR + 1, new_irq9_handler);

  old_irq10_handler = getvect(0x72);
  setvect(SLAVE_BASE_VECTOR + 2, new_irq10_handler);

  old_irq11_handler = getvect(0x73);
  setvect(SLAVE_BASE_VECTOR + 3, new_irq11_handler);

  old_irq12_handler = getvect(0x74);
  setvect(SLAVE_BASE_VECTOR + 4, new_irq12_handler);

  old_irq13_handler = getvect(0x75);
  setvect(SLAVE_BASE_VECTOR + 5, new_irq13_handler);

  old_irq14_handler = getvect(0x76);
  setvect(SLAVE_BASE_VECTOR + 6, new_irq14_handler);

  old_irq15_handler = getvect(0x77);
  setvect(SLAVE_BASE_VECTOR + 7, new_irq15_handler);

  // Выключаем контроллер
  _disable();

  // Инициализируем новые обработчики. После завершения инициализации контроллеры начинают обрабатывать поступающие запросы прерываний.
  // outp функция записывают данные непосредственно в порт ввода-вывода

  outp(0x20, 0x11);        // ICW1 
  outp(0x21, 0x88);        // ICW2
  outp(0x21, 0x04);        // ICW3
  outp(0x21, 0x01);        // ICW4

  // Initialize slave
  outp(0xA0, 0x11);        // ICW1 
  outp(0xA1, 0x08);        // ICW2
  outp(0xA1, 0x02);        // ICW3
  outp(0xA1, 0x01);        // ICW4

  // Стартуем котроллер
  _enable();
}

int main(void) {
  unsigned far* fp;

  init_new_handlers();
  system("cls");

  puts("                   -  MASK");
  puts("                   -  REQUEST");
  puts("                   -  SERVICE");
  puts("MASTER    SLAVE");

  // Делаем программу резидентной
  // Резидентная программа активизируется каждый раз при возникновении прерывания, вектор которого эта программа изменила на адрес одной из своих процедур.

  FP_SEG(fp) = _psp; // возвращает сегмент дальнего указателя fp.
  FP_OFF(fp) = 0x2c; // возвращает смещение указателя
  _dos_freemem(*fp);
  _dos_keep(0, (_DS - _CS) + (_SP / 16) + 1); // первый параметр - условие выхода из резидентной программы, второй парметр - кол-во выделенной памяти

  // размер памяти в параграфах, сегмент стека в байтах, поэтому его мы делим на 16 и + 1 
  return EXIT_SUCCESS;
}
