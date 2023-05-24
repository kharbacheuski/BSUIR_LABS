#include <windows.h>
#include <iostream>

using namespace std;

int main() {
    cout << "--- Start ---" << endl << endl;

    HANDLE COM1;
    LPCTSTR name1 = L"COM3";

    COM1 = CreateFile(          // Открытие порта
        name1,
        GENERIC_WRITE,          // Задает тип доступа к файлу (0, GENERIC_READ, GENERIC_WRITE, GENERIC_READ | GENERIC_WRITE)
        0,                      // Задает параметры совместного доступа к файлу. Коммуникационные порты нельзя делать разделяемыми, поэтому данный параметр должен быть равен 0.
        NULL,                   // Задает атрибуты защиты файла. Поддерживается только в Windows NT. Однако при работе с портами должен в любом случае равняться NULL.
        OPEN_EXISTING,          // Управляет режимами автосоздания, автоусечения файла и им подобными. Для коммуникационных портов всегда должно задаваться OPEN_EXISTING.
        FILE_ATTRIBUTE_NORMAL,  // Задает атрибуты создаваемого файла. Также управляет различными режимами обработки. При работе с портом этот параметр должен быть 
                                // или равным 0, или FILE_FLAG_OVERLAPPED. Нулевое значение используется при синхронной работе с портом, а FILE_FLAG_OVERLAPPED при асинхронной, или, другими словами, при фоновой обработке ввода/вывода.
        NULL                    // Задает описатель файла-шаблона. При работе с портами всегда должен быть равен NULL.
    );

    HANDLE COM2;
    LPCTSTR name2 = L"COM4";

    COM2 = CreateFile(
        name2,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (COM1 == INVALID_HANDLE_VALUE || COM2 == INVALID_HANDLE_VALUE) {  // проверка на корректное значение COM1
        cout << "COM-port opening error!\n";
    }

    string str = "hello world"; // эту строку мы отправим в COM1

    DCB SerialParams = {};  // Структура DCB определяет настройки управления последовательным коммуникационным устройством.

    SerialParams.DCBlength = sizeof(SerialParams); // Задает длину, в байтах, структуры DCB. Используется для контроля корректности структуры при передаче ее адреса в функции настройки порта.
    SerialParams.BaudRate = CBR_4800;   // скорость передачи данных - 
    SerialParams.ByteSize = sizeof(str);          // Число переданных и принятых битов, в байтах - 8.
    SerialParams.StopBits = ONESTOPBIT; // Число используемых стоповых битов - 1
    SerialParams.Parity = NOPARITY;     // Используемая схема четности - Без проверки четности


    // читает DCB структуру.

    if (!GetCommState(COM1, &SerialParams)) { 
        cout << "Getting state error.\n";
    }

    // конфигурирует коммуникационное устройство согласно данным указанным в структуре DCB. Функция повторно инициализирует все аппаратные и 
    // управляющие настройки, но не опорожняет очереди вывода или ввода данных.

    if (!SetCommState(COM2, &SerialParams)) { 
        cout << "Error setting serial port state.\n";
    }


    DWORD size = sizeof(str);

    DWORD bytes;

    cout << "Send '" << str << "' into COM1" << endl;
    WriteFile(COM1, &str, size, &bytes, NULL);          // посылаем строку в COM1

    str = "clear string";

    if (ReadFile(COM2, &str, sizeof(str), &size, 0)) {  // читаем строку из COM2
        cout << endl << "Data from COM2: '" << str << "'";
    }

    cout << endl << endl << "--- End ---";

    return 0;
}
