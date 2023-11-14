#include <iostream>
#include <winsock2.h>
#include <ws2bth.h>
#include <BluetoothAPIs.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

bool SendFileViaBluetooth(const wchar_t* filePath, const wchar_t* remoteDeviceAddress) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        wprintf(L"Failed to initialize Winsock\n");
        return false;
    }

    SOCKET bluetoothSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (bluetoothSocket == INVALID_SOCKET) {
        wprintf(L"Failed to create Bluetooth socket: %ld\n", WSAGetLastError());
        WSACleanup();
        return false;
    }

    SOCKADDR_BTH serverAddr = { 0 };
    serverAddr.addressFamily = AF_BTH;
    serverAddr.btAddr = 0; // Use server's bluetooth address (for example, obtained during device discovery)
    serverAddr.serviceClassId = RFCOMM_PROTOCOL_UUID;
    serverAddr.port = BT_PORT_ANY;

    if (bind(bluetoothSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        wprintf(L"Bind failed: %ld\n", WSAGetLastError());
        closesocket(bluetoothSocket);
        WSACleanup();
        return false;
    }

    if (listen(bluetoothSocket, 1) == SOCKET_ERROR) {
        wprintf(L"Listen failed: %ld\n", WSAGetLastError());
        closesocket(bluetoothSocket);
        WSACleanup();
        return false;
    }

    wprintf(L"Waiting for incoming Bluetooth connection...\n");

    SOCKADDR_BTH clientAddr = { 0 };

    unsigned long long h = 0x41343631314237;

    clientAddr.btAddr = h;

    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(bluetoothSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);

    if (clientSocket == INVALID_SOCKET) {
        wprintf(L"Accept failed: %ld\n", WSAGetLastError());
        closesocket(bluetoothSocket);
        WSACleanup();
        return false;
    }

    wprintf(L"Bluetooth connection established\n");

    // Open the file for reading
    FILE* file = _wfopen(filePath, L"rw");
    if (file == NULL) {
        wprintf(L"Error opening file: %d\n", GetLastError());
        closesocket(clientSocket);
        closesocket(bluetoothSocket);
        WSACleanup();
        return false;
    }

    // Read and send the file contents
    const int bufferSize = 4096;
    char buffer[bufferSize];
    int bytesRead;

    while ((bytesRead = fread(buffer, 1, bufferSize, file)) > 0) {
        int bytesSent = send(clientSocket, buffer, bytesRead, 0);

        if (bytesSent == SOCKET_ERROR) {
            wprintf(L"Send failed: %ld\n", WSAGetLastError());
            fclose(file);
            closesocket(clientSocket);
            closesocket(bluetoothSocket);
            WSACleanup();
            return false;
        }
    }

    wprintf(L"File sent successfully\n");

    // Clean up
    fclose(file);
    closesocket(clientSocket);
    closesocket(bluetoothSocket);
    WSACleanup();

    return true;
}

int wmain(int argc, wchar_t* argv[]) {
    //if (argc != 3) {
    //    wprintf(L"Usage: BluetoothSendFileServer.exe <FilePath> <RemoteDeviceAddress>\n");
    //    return 1;
    //}


    const wchar_t* filePath = L"C:\\Users\\Kiryl\\Desktop\\трекс\\something.mp3";
    const wchar_t* remoteDeviceAddress = L"A4611B7";

    if (SendFileViaBluetooth(filePath, remoteDeviceAddress)) {
        return 0;
    }
    else {
        return 1;
    }
}