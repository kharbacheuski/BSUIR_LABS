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
#include <stdio.h>
#include <string.h>  
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>

#define MESSAGE_BUFFER_SIZE 8096

using namespace std;

void find(string dirname, vector<string> &files) {
    DIR* directory;
    struct dirent* de;

	directory = opendir(dirname.c_str()); 
        
    while (de = readdir(directory)) {
        // проверка, что имя каталога не равно «.» и «..»
        if (!strcmp(".", de->d_name) || !strcmp("..", de->d_name))
            continue;

        string file = de->d_name;

        if(de->d_type == DT_LNK) {
            file.append("-->");
        }
        if(de->d_type == DT_DIR) {
            file.append("/");
        }

        files.push_back(file);
    }

    closedir(directory); // закрытие директории
}

void echoRequestHandler(int socketDesc, string data) {
    send(socketDesc, data.c_str(), data.size()+1, 0);
}

void infoRequestHandler(int socketDesc) {
    ifstream fin("server-info.txt");

    string serverInfo;

    while(getline(fin, serverInfo)) {
        send(socketDesc, serverInfo.c_str(), serverInfo.size() + 1, 0);
    };
}

void listRequestHandler(int socketDesc, string dirname) {
    vector<string> files; 
    find(dirname, files);
    string output;

    for(auto file: files) {
        output.append("\n").append(file);
    }

    send(socketDesc, output.c_str(), output.size() + 1, 0);
}

void cdRequestHandler(int socketDesc, string dirname) {
    int result;
    result = chdir(dirname.c_str());

    string OK = "We are in new directory";

    if(result != 0)
        cout << "Cant move to " << dirname;
    else send(socketDesc, OK.c_str(), OK.size() + 1, 0);
}
