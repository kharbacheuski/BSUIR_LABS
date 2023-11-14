#include <windows.h>
#include <iostream>
#include <setupapi.h>
#include <initguid.h>
#include <Usbiodef.h>
#include <clocale>
#include <thread>
#include <functional>
#include <vector>
#include <map>
#include <chrono>
#include <Cfgmgr32.h>
#pragma comment(lib, "setupapi.lib")

using namespace std;

map<wstring, wstring> devices;
map<wstring, DWORD> devicesINST;

CONFIGRET EjectVolume(DEVINST devInst)
{
	CONFIGRET result = CM_Request_Device_EjectW(devInst, nullptr, nullptr, NULL, NULL);

	if (result != CR_SUCCESS) {
		std::wcout << L"Error: ejecting denied." << endl;
	}

	return result;
}

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

	if (isInitial && devices.size()) {
		devices.clear();
		devicesINST.clear();
	}

	int i = 0;
	for (; ; i++)
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
			std::wcout << L"\n\t\t\tName: " << deviceName << endl;
			std::wcout << L"\t\t\tVendor ID: " << venAndDevId.substr(8, 4).c_str() << endl;
			std::wcout << L"\t\t\tDevice ID: " << venAndDevId.substr(17, 4).c_str() << endl << endl;
		}

		if (isInitial) {
			wstring devId = venAndDevId.substr(17, 4);

			devices[devId] = deviceName;
			devicesINST[devId] = DeviceInfoData.DevInst;
		}
	}

	SetupDiDestroyDeviceInfoList(DeviceInfoSet);

	return i;
}

int findElement(vector<wstring> v, wstring value) {
	auto it = find(v.begin(), v.end(), value);

	if (it != v.end()) {
		int index = it - v.begin();
		return index;
	}
	else return -1;
}

wstring findConnectedDevice(map<wstring, wstring> tmp) {
	for (const auto& pair : devices) {

		const wstring& key = pair.first;
		const wstring& value = pair.second;

		if (tmp.find(key) == tmp.end()) {
			return value;
		}
	}
}

wstring findDisconnectedDevice(map<wstring, wstring> tmp) {
	for (const auto& pair : tmp) {
		const wstring& key = pair.first;
		const wstring& value = pair.second;

		if (devices.find(key) == devices.end()) {
			return value;
		}
	}
}

void checkDevices() {
	int devicesCount = printUSBDevicesInfo(false, true);

	while (1) {
		devicesCount = printUSBDevicesInfo(false, false);

		if (devicesCount > devices.size()) {
			map<wstring, wstring> tmp = devices;

			printUSBDevicesInfo(false, true);

			wstring connectedDevice = findConnectedDevice(tmp);

			wcout << "\nDevice " << connectedDevice << " connected\n";
		}
		else if (devicesCount < devices.size()) {
			map<wstring, wstring> tmp = devices;

			wstring disconnectedDevice;

			printUSBDevicesInfo(false, true);

			disconnectedDevice = findDisconnectedDevice(tmp);
			
			wcout << "\nDevice " << disconnectedDevice << " disconnected\n";
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

void localization() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}


void ejectDevice() {
	string deviceId;

	cout << "\nEnter deviceId that should be unconnect: ";
	cin >> deviceId;

	CONFIGRET result = EjectVolume(devicesINST[wstring(deviceId.begin(), deviceId.end())]);
}

void menu() {
	char key = '0';

	cout << "\n\t\t\t================== Menu ==================\n";
	cout << "\n\t\t\t[i] - Print connected devices information";
	cout << "\n\t\t\t[e] - Eject connected device\n";
	cout << "\n\t\t\t==========================================\n\n";

	while (1) {
		cout << "\n\nEnter action (i/e): ";
		cin >> key;

		switch (key) {
			case 'i': printUSBDevicesInfo(true, false); break;
			case 'e': ejectDevice(); break;
			default: break;
		}
	}
}

int main() {
	localization();

	interval(checkDevices, 500);
	menu();

	return 0;
}