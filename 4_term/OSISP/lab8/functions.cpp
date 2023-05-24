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

string getWord(string SrcStr , int n) {
    vector<string> tokens;
    string delim = " ";
    size_t prev = 0, pos = 0;
    do
    {
        pos = SrcStr.find(delim, prev);
        if (pos == string::npos) pos = SrcStr.length();
        string token = SrcStr.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < SrcStr.length() && prev < SrcStr.length());
    if (n <= tokens.size())
       return tokens[n - 1];
    else
       return "";
}

void find(string dirname, vector<string> &files) {
    DIR* directory;
    struct dirent* de;

	directory = opendir(dirname.c_str()); 

    if(directory != NULL) {
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
    }
    else files.push_back("Error open directory");

    closedir(directory); // закрытие директории
}

void echoRequestHandler(int socketDesc, string data) {
    send(socketDesc, data.c_str(), data.size() + 1, 0);
}

void quitRequestHandler(int socketDesc, int listenerSocket) {
    string quitMessage = "Closing session";
    send(socketDesc, quitMessage.c_str(), quitMessage.size()+1, 0);
    close(socketDesc);
    close(listenerSocket);
    exit(EXIT_SUCCESS);
}

void infoRequestHandler(int socketDesc) {
    ifstream fin("/home/kiryl/osisp/lab8/server-info.txt");

    string serverInfo;
    string NotOK = "Open file error";

    if(fin.bad()) {
        send(socketDesc, NotOK.c_str(), NotOK.size() + 1, 0);

        return;
    }

    while(getline(fin, serverInfo)) {
        send(socketDesc, serverInfo.c_str(), serverInfo.size() + 1, 0);
    };

    fin.close();
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

    if(dirname[0] == '/') 
        result == -1;
    else result = chdir(dirname.c_str());
    
    string OK = "We are in new directory";
    string NotOK = "Cant move to " + dirname;

    if(result != 0)
        send(socketDesc, NotOK.c_str(), NotOK.size() + 1, 0);
    else send(socketDesc, OK.c_str(), OK.size() + 1, 0);
}

void runInstructionsFromFile(int socketDesc, string path, int listenerSocket) {
    string fileName = path.erase(0, 1);

    ifstream fin(fileName);

    string OK = "All good";
    string NotOK = "Open file error";

    if(fin.bad()) {
        send(socketDesc, NotOK.c_str(), NotOK.size() + 1, 0);
        return;
    }

    string serverInfo;

    while(1) {
        if(!getline(fin, serverInfo) || !serverInfo.length() || serverInfo[0] == EOF || fin.bad() || fin.eof()) break;

        string command = getWord(serverInfo, 1);

        if(!command.compare("/ECHO")) 
            echoRequestHandler(socketDesc, getWord(serverInfo, 2));
        if(!command.compare("/INFO"))
            infoRequestHandler(socketDesc);
        if(!command.compare("/LIST")) 
            listRequestHandler(socketDesc, getWord(serverInfo, 2));
        if(!command.compare("/CD")) 
            cdRequestHandler(socketDesc, getWord(serverInfo, 2));
        if(!command.compare("/QUIT")) {
            quitRequestHandler(socketDesc, listenerSocket);
        }
    };

    fin.close();
}
