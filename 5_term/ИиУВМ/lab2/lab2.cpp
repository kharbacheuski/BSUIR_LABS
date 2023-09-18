#include <stdio.h>
// #include <stdafx.h>

#include <iostream>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <locale>

#pragma comment(lib, "setupapi.lib")

int main() {
    const GUID* pciClassGuid = &GUID_DEVCLASS_SYSTEM;

    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(pciClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);

    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: SetupDiGetClassDevs failed" << std::endl;
        return 1;
    }

    SP_DEVINFO_DATA deviceInfoData = {};
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    DWORD index = 0;

    while (SetupDiEnumDeviceInfo(deviceInfoSet, index, &deviceInfoData)) {
        TCHAR deviceDesc[MAX_PATH];

        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)deviceDesc, sizeof(deviceDesc), NULL)) {
            if (wcsstr(deviceDesc, L"PCI")) {
                std::wcout << L"Device Desc: " << deviceDesc << std::endl;

                wchar_t* vendorIdPos = wcsstr(deviceDesc, L"VEN_");

                if (vendorIdPos) {
                    std::wcout << L"Vendor ID: " << std::wstring(vendorIdPos + 4, 4) << std::endl;
                }

                wchar_t* devIdPos = wcsstr(deviceDesc, L"DEV_");

                if (devIdPos) {
                    std::wcout << L"Device ID: " << std::wstring(devIdPos + 4, 4) << std::endl;
                }

                std::cout << std::endl;
            }
        }

        index++;
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);

    int a;

    std::cin >> a;

    return 0;
}
