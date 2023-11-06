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
#include <stdlib.h>
#pragma comment(lib, "setupapi.lib")

using namespace std;

void printUSBDevicesInfo()
{
	SP_DEVINFO_DATA DeviceInfoData;
	ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (DeviceInfoSet == INVALID_HANDLE_VALUE) {
		std::wcout << L"Error: Unable to get device information set." << endl;
		return;
	}

	int i = 0;

	for (int i = 0; ; i++)
	{
		DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

		if (!SetupDiEnumDeviceInfo(DeviceInfoSet, i, &DeviceInfoData))
		{
			break;
		}

		const int PropertyBufferSize = 1024;
		wchar_t deviceName[PropertyBufferSize];
		ZeroMemory(&deviceName, sizeof(deviceName));


		if (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)deviceName, sizeof(deviceName), NULL))
		{
			std::wcout << L"Error: Unable to get device description." << endl;

			SetupDiDestroyDeviceInfoList(DeviceInfoSet);

			return;
		}

		std::wcout << i+1 << L". " << deviceName << endl;
	}

	SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}


void startDeviceCheck()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	WCHAR modulePath[] = L"..\\checkDevices\\x64\\Debug\\checkDevices.exe";

	// Start the child process. 
	if (!CreateProcess(NULL,   // No module name (use command line)
		modulePath,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		CREATE_NEW_CONSOLE,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	startDeviceCheck();

	cout << "\nEnter device that should be unconnect: \n\n";
	printUSBDevicesInfo();

	int deviceNumber;
	cin >> deviceNumber;

	return 0;
}