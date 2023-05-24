#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <dos.h>

#define TIMER_REG_AMOUNT 3
#define TIME_REG_AMOUNT 6

typedef unsigned char byte;

enum time_registers { // адреса регистров ЧРВ
  sec        = 0x00,
  sec_timer  = 0x01, 
  min        = 0x02,
  min_timer  = 0x03,
  hour       = 0x04,
  hour_timer = 0x05,
  day        = 0x07,
  month      = 0x08,
  year       = 0x09, // последние две цифры года (2012 = 12)
};

enum state_registers {
  // 7 - часы заняты

  // 4-6 - делитель фазы (010 — 32 768 KHz — по 	умолчанию)

  // 0-3 выбор частоты периодического прерывания (0110, что соответствует выходной частоте прямоугольных колебаний 1.024 Кгц и интервалу времени между периодическими прерываниями 976.562 мкс.
  A = 0x0A,
  // 7 - запрещено обновление часов (устанавливают перед записью новых значений в регистры даты и часов)

  // 6 - вызов периодического прерывания (IRQ8)

  // 5 - вызов прерывания при срабатывании будильника

  // 4 - вызов прерывания по окончании обновления времени

  // 3 - включена генерация прямоугольных импульсов

  // 2 - 1/0 — формат даты и времени двоичный/BCD

  // 1 - 1/0 — 24-часовой/12-часовой режим

  // 0 - автоматический переход на летнее время в апреле и октябре

  B = 0x0B,
  // 7 - произошло прерывание

  // 6 - разрешено периодическое прерывание

  // 5 - разрешено прерывание от будильника

  // 4 - разрешено прерывание по окончании обновления часов

  // 0-3 - всегда 0
  C = 0x0C,

  // 7 - VRB - cостояние батареи (1 - норма, 0 - батарейка разряжена, время не достоверно)
  D = 0x0D, 
};

unsigned time[TIME_REG_AMOUNT];
const byte time_registers[TIME_REG_AMOUNT] = {sec, min, hour, day, month, year};
const byte timer_registers[TIMER_REG_AMOUNT] = {sec_timer, min_timer, hour_timer};

unsigned bcd_to_dec(unsigned bcd) { return (bcd / 16 * 10) + (bcd % 16); }
unsigned dec_to_bcd(unsigned dec) { return (dec / 10 * 16) + (dec % 10); }

void print_time(void) {
  int i;
  for (i = 0; i < TIME_REG_AMOUNT; ++i) {
    outp(0x70, A); // будем читать режим состояния A

    // Не читаем пока часы не закончили обновление (бит 7)
    if (inp(0x71) & 0x80) { 
      i--;
      continue;
    }

    //  1.	записать адрес считываемого регистра в порт 70h;
    //  2.	считать данные регистра из порта 71h.
    outp(0x70, time_registers[i]);
    time[i] = inp(0x71);

    time[i] = bcd_to_dec(time[i]);
  }

  printf("%02u:%02u:%02u %02u.%02u.20%02u\n",
    time[2], time[1], time[0], time[3], time[4], time[5]); // выводим время
}

void set_time(void) {
  int i;

  puts("Enter time in format hours:min:sec");
  if (scanf("%u:%u:%u", &time[2], &time[1], &time[0]) != 3) {
    fprintf(stderr, "Failed to enter time\n");
  }
  puts("Enter date in format day.month.year");
  if (scanf("%u.%u.%u", &time[3], &time[4], &time[5]) != 3) {
    fprintf(stderr, "Failed to enter date\n");
  }

  for (i = 0; i < TIME_REG_AMOUNT; ++i) {
    time[i] = dec_to_bcd(time[i]);
  }

  disable(); // выключаем прерывания

  // Не читаем пока часы не закончили обновление (бит 7)
  do {
    outp(0x70, A);
  } while (inp(0x71) & 0x80); 01111111

  // Выключаем обновление часов
  outp(0x70, 0x0B);// будем записывать в B
  outp(0x71, inp(0x71) | 0x80); // 7 бит в 1 (запрещаем обновление часов)

  for (i = 0; i < TIME_REG_AMOUNT; i++) {
    outp(0x70, time_registers[i]); // обращаемся к регистру времени (сек, мин, часы)
    outp(0x71, time[i]); // записываем новое значение времени
  }

  // Включаем обновление
  outp(0x70, 0x0B);
  outp(0x71, inp(0x71) & 0x7F); // 01111111 разрешаем прерывания

  enable(); // включаем прерывания
}

void interrupt(*old_interrupt)(void); // обработчик для будильника

void interrupt new_interrupt(void) {
  puts("New alarm handler called");

  outp(0x70, 0x0C); // будем читать регистр состояний C
  if (inp(0x71) & 0x20) { // проверяем что прерывание вызвал будильник 11011111
    puts("5 bit in C register is set");
  }

  // Заканчиваем прерывание
  outp(0x20, 0x20); // EOI а мастер
  outp(0xA0, 0x20); // EOI в слэйв

  // Переключить на старый обработчик
  disable(); // выключаем прерывания
  setvect(0x70, old_interrupt); // возвращаем старый обработчик
  enable(); // включаем прерывания

  // тут прерывание доотрабатывает

  outp(0x70, 0x0B);
  outp(0x71, inp(0x71) & 0xDF); // запрещаем прерывание будильника 11011111
}

void set_alarm(void) {
  int i;

  puts("Enter time in format hours:min:sec");
  if (scanf("%u:%u:%u", &time[2], &time[1], &time[0]) != 3) {
    fprintf(stderr, "Failed to enter time\n");
  }
  for (i = 0; i < TIMER_REG_AMOUNT; ++i) {
    time[i] = dec_to_bcd(time[i]);
  }

  disable();

  
  old_interrupt = getvect(0x70); // Получаем прошлый обработчик
  setvect(0x70, new_interrupt);  // Устанавливаем новый

  outp(0xA1, (inp(0xA0) & 0xFE)); // 11111110 снимаем маску будильника с контроллера прерываний ) бит 0 в 0, чтобы разрешить прерывания от ЧРВ

  // Ждем пока 7-ой бит станет 0
  do {
    outp(0x70, 0x0A);
  } while (inp(0x71) & 0x80); // 10000000

  // Записываем значения будильника
  for (i = 0; i < TIMER_REG_AMOUNT; i++) {
    outp(0x70, timer_registers[i]);
    outp(0x71, time[i]);
  }

  enable();

  
  outp(0x70, 0x0B);
  outp(0x71, inp(0x71) | 0x20); // 00100000 Разрешаем прерывания будильника

  puts("Timer set");
}

void set_delay(void) {


  disable(); // выключаем прерывания

  // Не читаем пока часы не закончили обновление (бит 7)
  do {
    outp(0x70, A);
  } while (inp(0x71) & 0x80);


  outp(0x70, A); // будем записывать в A
  outp(0x71, inp(0x71) | 0x07); // последние 4 бита в 0111 соответсвует 512гц

  enable();
  puts("delay = 512Hz");
}

int main(void) {
  while (1) {
    puts("1 - print time");
    puts("2 - set time");
    puts("3 - set alarm");
    puts("4 - set delay");
    puts("0 - exit");

    switch (getch()) {
      case '1':
        print_time();
        break;

      case '2':
        set_time();
        break;

      case '3':
        set_alarm();
        break;
      case '4':
        set_delay();
        break;

      case '0':
        exit(EXIT_SUCCESS);

      default:
        break;
    }
  }
}
