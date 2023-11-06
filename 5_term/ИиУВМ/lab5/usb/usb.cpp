#include <windows.h>
#include <iostream>
#include <setupapi.h>
#include <initguid.h>
#include <Usbiodef.h>
#include <clocale>
#include <thread>
#include <functional>
#include <tchar.h>
#include <stdio.h>
#include <stringapiset.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#pragma comment(lib, "setupapi.lib")

using namespace std;

vector<wstring> devices;

int printUSBDevicesInfo(bool isPrint = false, bool isInitial = false)
{
	SP_DEVINFO_DATA DeviceInfoData;
	ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (DeviceInfoSet == INVALID_HANDLE_VALUE) {
		std::wcout << L"Error: Unable to get device information set." << endl;
		return NULL;
	}

	if (isInitial) {
		devices.clear();
	}

	int i = 0;
	for (i = 0; ; i++)
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
			std::wcout << L"Error: Unable to get device instance ID." << endl;
			std::wcout << L"Error code: " << GetLastError() << endl;

			SetupDiDestroyDeviceInfoList(DeviceInfoSet);

			return NULL;
		}

		if (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)deviceName, sizeof(deviceName), NULL))
		{
			std::wcout << L"Error: Unable to get device description." << endl;

			SetupDiDestroyDeviceInfoList(DeviceInfoSet);

			return NULL;
		}

		if (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_MFG, NULL, (PBYTE)companyName, sizeof(companyName), NULL))
		{
			std::wcout << L"Error: Unable to get manufacturer information." << endl;

			SetupDiDestroyDeviceInfoList(DeviceInfoSet);

			return NULL;
		}

		wstring venAndDevId(deviceID);

		if (isPrint) {
			std::wcout << L"Name: " << deviceName << endl;
			std::wcout << L"Vendor ID: " << venAndDevId.substr(8, 4).c_str() << endl;
			std::wcout << L"Device ID: " << venAndDevId.substr(17, 4).c_str() << endl << endl;
		}

		if (isInitial) {

			wstring devId = venAndDevId.substr(17, 4);

			devices.push_back(devId);
		}
	}

	SetupDiDestroyDeviceInfoList(DeviceInfoSet);

	return i;
}

void checkDevices() {
	int devicesCount = printUSBDevicesInfo(true, true);

	while (1) {
		devicesCount = printUSBDevicesInfo(false, false);

		if (devicesCount > devices.size()) {
			printUSBDevicesInfo(false, true);
			wcout << "\nDevice " << devices[devices.size() - 1] << " connected\n";
		}
		else if (devicesCount < devices.size()) {
			wcout << "\nDevice " << devices[devices.size() - 1] << " disconnect\n";
			printUSBDevicesInfo(false, true);
		}
	}
}

void interval(std::function<void(void)> func, unsigned int interval) {
	std::thread([func, interval]()
	{
		while (true)
		{
			auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
			func();
			std::this_thread::sleep_until(x);
		}
	}).detach();
}


int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	interval(checkDevices, 2000);

	cout << "\nEnter device that should be unconnect: \n\n";

	int deviceNumber;
	cin >> deviceNumber;

	return 0;
}