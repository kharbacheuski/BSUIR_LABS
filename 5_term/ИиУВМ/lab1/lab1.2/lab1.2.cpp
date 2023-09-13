#include <iostream>
#include <windows.h>
#include <powrprof.h>
#include <winbase.h>
#include <batclass.h>
#include <cstdlib>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>

#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "Powrprof.lib")

using namespace std;

void printInfo() {
    cout << "1 - Показать информацию" << endl;
    cout << "2 - Перейти в режим сна" << endl;
    cout << "3 - Перейти в режим гибернации" << endl;
    cout << "4 - Обновить данные" << endl;
    cout << "0 - Выход" << endl << endl;
}

void chargingStatus(int state) {
    switch (state) {
        case 0: cout << "Зарядка не подключена" << endl; break;
        case 1: cout << "Зарядка подключена" << endl; break;
        case 255: cout << "Нет данных" << endl; break;
        default: break;
    }
}

void battaryProcent(int procent) {
    if (procent != 255) {
        cout << "Батерея заряжена на " << procent << "%" << endl;
    }
    else cout << "Данные о заряде не найдены" << endl;
}

void statusOfBattary(int statusBattary) {
    switch (statusBattary) {
        case 0: cout << "Режим энергосбережения выключен." << endl; break;
        case 1: cout << "Режим энергосбережения включен." << endl; break;
        default: break;
    }
}

void displayInformationAboutBatteryType() {

    HDEVINFO hdev = SetupDiGetClassDevs(
        &GUID_DEVCLASS_BATTERY,
        0,
        0,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
    );

    if (INVALID_HANDLE_VALUE == hdev) {
        cout << "INVALID_HANDLE_VALUE";
        return;
    }

    SP_DEVICE_INTERFACE_DATA did = { 0 };

    did.cbSize = sizeof(did);

    bool condition = !SetupDiEnumDeviceInterfaces(hdev,
        0,
        &GUID_DEVCLASS_BATTERY,
        0,
        &did
    );

    if(condition) {
        cout << "unknown error 1";
        return;
    }

    DWORD cbRequired = 0;

    SetupDiGetDeviceInterfaceDetail(hdev,
        &did,
        0,
        0,
        &cbRequired,
        0
    );

    if (ERROR_INSUFFICIENT_BUFFER != GetLastError()) {
        cout << "ERROR_INSUFFICIENT_BUFFER";
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }

    PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, cbRequired);


    if (!pdidd) {
        cout << "unknown error 3";
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }

    pdidd->cbSize = sizeof(*pdidd);

    condition = !SetupDiGetDeviceInterfaceDetail(hdev,
        &did,
        pdidd,
        cbRequired,
        &cbRequired,
        0
    );

    if(condition) {
        cout << "unknown error 4";
        return;
    }

    HANDLE hBattery = CreateFile(pdidd->DevicePath,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if(INVALID_HANDLE_VALUE == hBattery) {
        cout << "ERROR_INSUFFICIENT_BUFFER";
        LocalFree(pdidd);
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }

    BATTERY_QUERY_INFORMATION bqi = { 0 };
    DWORD dwWait = 0;
    DWORD dwOut;

    if (!DeviceIoControl(hBattery,
        IOCTL_BATTERY_QUERY_TAG,
        &dwWait,
        sizeof(dwWait),
        &bqi.BatteryTag,
        sizeof(bqi.BatteryTag),
        &dwOut,
        NULL)
        && bqi.BatteryTag
    ) {
        cout << "unknown error 5";
        CloseHandle(hBattery);
        LocalFree(pdidd);
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }

    BATTERY_INFORMATION bi = { 0 };
    bqi.InformationLevel = BatteryInformation;

    if (!DeviceIoControl(hBattery,
        IOCTL_BATTERY_QUERY_INFORMATION,
        &bqi,
        sizeof(bqi),
        &bi,
        sizeof(bi),
        &dwOut,
        NULL))
    {
        cout << "unknown error 6";
        CloseHandle(hBattery);
        LocalFree(pdidd);
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }

    cout << "Тип батареи: " << bi.Chemistry << "\n";
    CloseHandle(hBattery);
    LocalFree(pdidd);
    SetupDiDestroyDeviceInfoList(hdev);
    return;
}


SYSTEM_POWER_STATUS getState(SYSTEM_POWER_STATUS& computer) {
    if (!GetSystemPowerStatus(&computer)) {
        cout << "truble with getting data from powrprof" << endl;
        exit(1);
    }

    return computer;
}

void printState(SYSTEM_POWER_STATUS computer) {
    cout << "\n";
    battaryProcent(computer.BatteryLifePercent);
    chargingStatus(computer.ACLineStatus);
    statusOfBattary(computer.SystemStatusFlag);
    displayInformationAboutBatteryType();

    if (!computer.ACLineStatus) {
        cout << "\nОставшееся время работы аккумулятора: " << (double)computer.BatteryLifeTime / 60 / 60 << " часов" << "\n";
    }
  
    cout << "Выключенный ноутбук с заряженным аккумулятором продержится: " << (double)computer.BatteryFullLifeTime / 60 / 60 / 24 << " дней"  << "\n\n\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    SYSTEM_POWER_STATUS computer{};

    computer = getState(computer);

    int work;

    while (true) {
        printInfo();

        cout << "\n\nВыберите действие: ";

        cin >> work;

        switch (work) {
            case 1: printState(computer); break;
            case 2: SetSuspendState(FALSE, FALSE, FALSE); break;
        
            case 3: SetSuspendState(TRUE, FALSE, FALSE); break;

            case 4: {
                cout << "Обновлено" << endl;
                computer = getState(computer);
                break;
            }

            default: break;
        }

        if (work == 0) break;
    }

    return 0;
}

