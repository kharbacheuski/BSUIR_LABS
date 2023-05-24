#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

#include <conio.h>

typedef enum { false, true } bool;

#define KEYBOARD_INTERRUPT 0x09
#define KEYBOARD_LIGHTS_CODE 0xED // Для управления индикаторами через 60h отправляется код EDh. 

#define NONE 0x00
#define SCROLL_LOCK 0x01
#define NUM_LOCK 0x02
#define CAPS_LOCK 0x04

typedef unsigned char byte;

int command_succeeded = 0;

void interrupt (*old_handler)(void);

void interrupt new_handler(void) {
  byte scan_code = inp(0x60);
  // FA – байт обработан успешно,
  // FE – произошла ошибка.
  printf("%X\n", scan_code);



  command_succeeded = (scan_code == 0xFA);

  old_handler();
}

void set_mask(byte mask) {
  int i = 0;

  while (!command_succeeded) {
    // 60 - регистр данных, 64 - регистр состояния
    // Ждем пока буфер освободится
    while ((inp(0x64) & 0x02));

    outp(0x60, KEYBOARD_LIGHTS_CODE); // посылаем в регистр данных код, для управления клавиатурой

    // Ждем пока буфер освободится
    while ((inp(0x64) & 0x02));
    outp(0x60, mask); // посылаем в регистр данных код клавиши

    // В случае ошибки передачу байта нужно повторить. Пересылка выполняется до 3 раз, 
    // если ошибка не исчезла, нужно вывести сообщение и выйти из программы. 

    if (++i == 3) {
      fputs("Failed to set mask 3 times in a row\n", stderr);
      setvect(KEYBOARD_INTERRUPT, old_handler);
      exit(EXIT_FAILURE);
    }
  }
  command_succeeded = 0;
}

int main(void) {
  old_handler = getvect(KEYBOARD_INTERRUPT); // получаем старый обработчик
  setvect(KEYBOARD_INTERRUPT, new_handler); // устанавливаем по адресу новый обработчик

  puts("\nSTART\n\n");

  set_mask(NUM_LOCK); // зажигаем нум лок
  delay(1500);
  set_mask(CAPS_LOCK); // зажигаем капс лок
  delay(1500);
  set_mask(SCROLL_LOCK); // зажигаем скролл лок
  delay(1500);
  set_mask(NONE); // тушим всё
  delay(1500);
  set_mask(SCROLL_LOCK | NUM_LOCK | CAPS_LOCK); // зажигаем все
  delay(1500);
  set_mask(NONE);
  delay(1500);
  set_mask(NONE); // тушим всё
  delay(1500);
  set_mask(SCROLL_LOCK | NUM_LOCK | CAPS_LOCK); // зажигаем все
  delay(1500);
  set_mask(NONE);

  setvect(KEYBOARD_INTERRUPT, old_handler); // возвращаем на место старый обработчик

  return EXIT_SUCCESS;
}
