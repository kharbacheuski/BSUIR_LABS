#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <thread>
#include <signal.h>
#include <cstring>
#include <fcntl.h>
#include <functional>
#include <fstream>
#include <vector>
#include "functions.cpp"

#define SOCKET_BIND_PORT 8081
#define REQUEST_QUEUE_SIZE 128
#define MESSAGE_BUFFER_SIZE 8096

using namespace std;

int listenerSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0); // создаем сокет

sockaddr* getAddressForBindListenerSocket(long ip, int port) {
    sockaddr_in* addr = new sockaddr_in;
    
    addr->sin_family = AF_INET;
    addr->sin_port =  htons(port);
    addr->sin_addr.s_addr = htonl(ip);

    return (sockaddr*)addr;
}

/// @return new socket descriptor 
int acceptRequest(int listenerSocketDescriptor) {
    int newSocketDescriptor = accept(listenerSocketDescriptor, NULL, NULL); 
    // функция accept возвращает новый сокет-дескриптор, через который и происходит общение клиента с сервером

    if(newSocketDescriptor < 0) {
        perror("accept");
        exit(3);
    }
    else {
        cout << "---Request are accepted---";
    }

    return newSocketDescriptor;
}

void bindSocketTo(int listenerSocketDescriptor, sockaddr *address) {
    int len = sizeof(sockaddr);

    // присваиваем адресс сокету, для связи клиентов с сервером
    if(bind(listenerSocketDescriptor, address, len) != 0) {
        perror("bind");
        exit(1);
    }
    cout << "---Socket are binded---" << endl;
}



string getPath(const char* buffer) {
    string requestPath = getWord(string(buffer), 1);

    return requestPath;
}

string getData(const char* buffer) {
    string data = getWord(string(buffer), 2);
    
    return data;
}

void handleRequest(int socketDesc) {
    char* messageBuf = new char[MESSAGE_BUFFER_SIZE];

    // принимаем сообщение из нового сокет-дескриптора
    recv(socketDesc, messageBuf, MESSAGE_BUFFER_SIZE, 0);

    string path = getPath(messageBuf);
    string data = getData(messageBuf); 
    
    free(messageBuf);

    if(path[0] == '@') 
        runInstructionsFromFile(socketDesc, path, listenerSocketDescriptor);
    if(!path.compare("/ECHO")) 
        echoRequestHandler(socketDesc, data);
    if(!path.compare("/INFO"))
        infoRequestHandler(socketDesc);
    if(!path.compare("/LIST")) 
        listRequestHandler(socketDesc, data);
    if(!path.compare("/CD")) 
        cdRequestHandler(socketDesc, data);
    if(!path.compare("/QUIT")) {
        quitRequestHandler(socketDesc, listenerSocketDescriptor);
    }

    close(socketDesc);
}

int main() {

    if(listenerSocketDescriptor < 0) {
        perror("socket");
        exit(1);
    }
    else {
        cout << "---Socket are created---" << endl;
    }

    // получаем адрес для биндинга сокета
    sockaddr* listenerSocketAddress = getAddressForBindListenerSocket(INADDR_LOOPBACK, SOCKET_BIND_PORT);

    // присваем адрес сокету
	bindSocketTo(listenerSocketDescriptor, listenerSocketAddress);

    const int enable = 1;
    if (setsockopt(listenerSocketDescriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");
    if (setsockopt(listenerSocketDescriptor, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    // переводим сокет в режим прослушки
    if(listen(listenerSocketDescriptor, REQUEST_QUEUE_SIZE) != 0) {
        perror("listen");
        exit(1);
    }
    else {
        cout << "---Server listening---" << endl;
    }

    vector<std::thread> threads;

    while(1) {
        // создаем новый сокет-дескриптор на каждый запрос клиента
        int newSocketDescriptor = acceptRequest(listenerSocketDescriptor);

        threads.emplace_back(handleRequest, newSocketDescriptor);
        threads.back().detach();
    }

    // закрываем сокет
    close(listenerSocketDescriptor);

    return 0;
}