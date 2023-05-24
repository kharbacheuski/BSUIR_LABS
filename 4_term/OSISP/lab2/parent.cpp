#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

bool comp(const std::string& s1, const std::string& s2) {
  return s1[s1.size()-2] < s2[s2.size()-2];
}

void forkProcess(char* argv[], char* envp[], char * ch_p, pid_t pid) {
    pid = fork();

    if(pid == -1) {
        cout << "Error when create new process";

        exit(1);
    }
    if(pid == 0){
        execve(ch_p, argv, envp);  // запускаем программу
    }
    if(pid > 0) {
        cout << endl << "Parent pid = " << getpid();
        wait(NULL);
    }
}

int main(int argc, char* argv[], char* envp[]) {
    pid_t pid;
    int wstatus;

    vector<string> envs_vect;
    string temp;

    for(int i = 0; envp[i] != nullptr; i++) {
        temp = envp[i];
        envs_vect.push_back(temp);
    }

    sort(envs_vect.begin(), envs_vect.end(), comp);

    cout << "\n\nENVS: \n";
    for(auto i: envs_vect) {
        cout << "\t - " << i << "\n";
    }
    cout << "\n";

    while (1) {
        cout  << "\n\nEnter symbol(+, *, &, q - exit): ";

        string symbol;

        cin.clear();
        cin >> symbol;

        if(symbol == "q")
            break;
        else if(symbol == "+") { 
            char* CHILD_PATH = getenv("CHILD_PATH"); // получаем путь к child используя переменную окружения
            forkProcess(argv, envp, CHILD_PATH, pid);
        } 
        else if(symbol == "*") {
            string CHILD_PATH_ENV;
            string str;

            for(int i = 0; envp[i] != nullptr; i++) {
                str = envp[i];

                if(str.find("CHILD_PATH") != string::npos) {
                    CHILD_PATH_ENV = str.erase(0, 11);
                    break;
                }
            }

            char* CHILD_PATH = new char[CHILD_PATH_ENV.length() + 1]; // получаем путь к child используя переменную окружения
            strcpy(CHILD_PATH, CHILD_PATH_ENV.c_str());

            forkProcess(argv, envp, CHILD_PATH, pid);
        }
        else if(symbol == "&") {
            extern char** environ;

            char* CHILD_PATH;
            string CHILD_PATH_ENV;
            string str;

            for(int i = 0; environ[i] != nullptr; i++) {
                str = environ[i];

                if(str.find("CHILD_PATH") != string::npos) {
                    CHILD_PATH_ENV = str.erase(0, 11);
                    break;
                }
            }

            char* CHILD_PATH = new char[CHILD_PATH_ENV.length() + 1]; // получаем путь к child используя переменную окружения
            strcpy(CHILD_PATH, CHILD_PATH_ENV.c_str());

            forkProcess(argv, envp, CHILD_PATH, pid);
        }
    }
    
    return 0;
}