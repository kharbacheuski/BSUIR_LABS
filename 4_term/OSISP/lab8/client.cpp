#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>
#define SOCKET_BIND_PORT -1
#define SERVER_PORT 8081
#define MESSAGE_BUFFER_SIZE 8096

using namespace std;

sockaddr* getServerSocketAddress(long serverIp, int serverPort) {
    sockaddr_in* serverSocketAddress = new sockaddr_in;
    
    serverSocketAddress->sin_family = AF_INET;
    serverSocketAddress->sin_port = htons(serverPort);
    serverSocketAddress->sin_addr.s_addr = htonl(serverIp);

    return (sockaddr*)serverSocketAddress;
}

int connectToServer(sockaddr* serverSocketAddress) {
    // создаем сокет
    int socketDesc = socket(AF_INET, SOCK_STREAM, 0); 

    if(socketDesc < 0) {
        perror("socket");
        exit(1);
    }
    // подключаемся к серверу
    if(connect(socketDesc, serverSocketAddress, sizeof(sockaddr)) != 0) {
        perror("connect");
        exit(1);
    }
    cout << endl << "---Linked to server---" << endl;

    return socketDesc;
}


void sendRequest(sockaddr* serverSocketAddress, string data) {
    int socketDesc = connectToServer(serverSocketAddress);

    // отправляем на сервер сообщение
    send(socketDesc, data.c_str(), data.size() + 1 , 0);
    cout << endl << "Input data: " << data << " len:" << data.size() << " are sended" << endl;

    char* messageBuf = new char[MESSAGE_BUFFER_SIZE];

    ssize_t count;

    // принимаем сообщения с сервера пока они есть
    while ((count = recv(socketDesc, messageBuf, MESSAGE_BUFFER_SIZE, 0)) > 0) {
        cout << endl << "Answer: " << messageBuf << endl;
    }

    free(messageBuf);
    close(socketDesc);
}

int main() {
    // получаем адрес сервера
    sockaddr* serverSocketAddress = getServerSocketAddress(INADDR_LOOPBACK, SERVER_PORT);

    while(1) {
        string message;

        cout << endl << " > ";

        getline(cin, message);
        
        sendRequest(serverSocketAddress, message);
    }

    return 0;
}