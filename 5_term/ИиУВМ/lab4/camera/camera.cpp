#include <format>
#include <mutex>
#include <thread>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <setupapi.h>
#include <devguid.h>
#include <direct.h>
#include <opencv2\opencv.hpp>
#include <Windows.h>
#include <winuser.h>
#pragma comment(lib, "setupapi.lib")

using namespace cv;
using namespace std;

#define EXT_KEY VK_MENU
#define CAPTURE 0x43
#define EXIT 0x51
#define INFO 0x58

void printCameraInfo()
{
	SP_DEVINFO_DATA DeviceInfoData;
	ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_CAMERA, L"USB", NULL, DIGCF_PRESENT);

	if (DeviceInfoSet == INVALID_HANDLE_VALUE) {
		wcout << L"Error: Unable to get device information set." << endl;
		return;
	}

	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	if (!SetupDiEnumDeviceInfo(DeviceInfoSet, 0, &DeviceInfoData))
	{
		wcout << L"Error: Unable to enumerate device information." << endl;
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
		return;
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
	wcout << L"Manufacture: " << companyName << endl;
	wcout << L"Vendor ID: " << venAndDevId.substr(8, 4).c_str() << endl;
	wcout << L"Device ID: " << venAndDevId.substr(17, 4).c_str() << endl << endl;

	SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}

void capture()
{
	Mat frame;
	SYSTEMTIME time;

	try
	{
		VideoCapture cap(0);

		if (cap.isOpened())
		{
			cap.set(CAP_PROP_FRAME_WIDTH, 1920);
			cap.set(CAP_PROP_FRAME_HEIGHT, 1080);

			cap.read(frame);

			GetSystemTime(&time);
		}
	}
	catch (...) {}

	if (!frame.empty())
	{
		string filePath = "D:/Education/BGUIR__LABS/5_term/ИиУВМ/lab4/photos/";
		string fileName = "camera-" + std::to_string(time.wDay) + std::to_string(time.wMinute) + std::to_string(time.wMilliseconds) + ".png";

		imwrite(filePath + fileName, frame);

		cout << "Photo saved successfully in " << filePath << endl << endl;
	}
}

bool shift = false;
bool ctrl = false;

void GetKEY()
{
	if (GetAsyncKeyState(0x10)) shift = true;
	else shift = false;

	if (GetAsyncKeyState(0x11)) ctrl = true;
	else ctrl = false;
}

int main() {
	setlocale(LC_ALL, "Russian");

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOW);

	bool isSecretMode = false;
	char answer = 'n';

	cout << "Enter to secret mode (y/n): ";

	cin >> answer;

	if (answer == 'y') {
		isSecretMode = true;
		ShowWindow(hWnd, SW_HIDE);
	}


	if (!isSecretMode) {
		cout << "\n\nPress shift to make photo!\n";
		cout << "Press ctrl to get camera info!\n\n";
	}
	 
	while (1) {
		Sleep(100);
		GetKEY();

		if (isSecretMode) {
			ShowWindow(hWnd, SW_HIDE);
			Sleep(1000);
			capture();
		}

		if (shift) {
			capture();
		}
		if (ctrl) {
			if (isSecretMode) ShowWindow(hWnd, SW_SHOW);

			printCameraInfo();
		}
	}

	return 0;
}