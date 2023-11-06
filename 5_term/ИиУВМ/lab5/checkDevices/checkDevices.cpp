#include <windows.h>
#include <iostream>
#include <setupapi.h>
#include <initguid.h>
#include <Usbiodef.h>
#include <clocale>
#include <thread>
#include <tchar.h>
#include <stdio.h>
#include <stringapiset.h>
#pragma comment(lib, "setupapi.lib")

using namespace std;

void printUSBDevicesInfo()
{
	SP_DEVINFO_DATA DeviceInfoData;
	ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (DeviceInfoSet == INVALID_HANDLE_VALUE) {
		wcout << L"Error: Unable to get device information set." << endl;
		return;
	}


	for (int i = 0; ; i++)
	{
		DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

		if (!SetupDiEnumDeviceInfo(DeviceInfoSet, i, &DeviceInfoData))
		{
			break;
		}

		const int PropertyBufferSize = 1024;
		wchar_t deviceID[PropertyBufferSize], deviceName[PropertyBufferSize], companyName[PropertyBufferSize];

		ZeroMemory(&deviceID, sizeof(deviceID));
		ZeroMemory(&deviceName, sizeof(deviceName));
		ZeroMemory(&companyName, sizeof(companyName));

		if (!SetupDiGetDeviceInstanceId(DeviceInfoSet, &DeviceInfoData, deviceID, sizeof(deviceID), NULL))
		{
			wcout << L"Error: Unable to get device instance ID." << endl;
			wcout << L"Error code: " << GetLastError() << endl;

			SetupDiDestroyDeviceInfoList(DeviceInfoSet);

			return;
		}

		if (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)deviceName, sizeof(deviceName), NULL))
		{
			wcout << L"Error: Unable to get device description." << endl;

			SetupDiDestroyDeviceInfoList(DeviceInfoSet);

			return;
		}

		if (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_MFG, NULL, (PBYTE)companyName, sizeof(companyName), NULL))
		{
			wcout << L"Error: Unable to get manufacturer information." << endl;

			SetupDiDestroyDeviceInfoList(DeviceInfoSet);

			return;
		}

		wstring venAndDevId(deviceID);

		wcout << L"Name: " << deviceName << endl;
		wcout << L"Vendor ID: " << venAndDevId.substr(8, 4).c_str() << endl;
		wcout << L"Device ID: " << venAndDevId.substr(17, 4).c_str() << endl << endl;
	}

	SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}

void realTimeUpdate() {
	while (1) {
		Sleep(2500);
		system("CLS");
		printUSBDevicesInfo();
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	realTimeUpdate();

	return 0;
}