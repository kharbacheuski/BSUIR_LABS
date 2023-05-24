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
#include <dirent.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <signal.h>

using namespace std;

#define PROC_DIRECTORY "/proc/"

char * CHILD_PATH = getenv("CHILD_PATH");
vector<pid_t> allProcesses;

enum ProcessesActions {
    killAll,
    showAll,
    allowStdoutForAll,
    readFromDir
};

int IsNumeric(const char* ccharptr_CharacterList) {
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}

void readProcessesFromDir() {
    struct dirent* dirEntity = NULL;
    DIR* dir_proc = NULL;

    dir_proc = opendir(PROC_DIRECTORY);
    if (dir_proc == NULL) {
        perror("Couldn't open the " PROC_DIRECTORY " directory") ;
    }

    while ((dirEntity = readdir(dir_proc)) != 0) {

        if (dirEntity->d_type == DT_DIR && IsNumeric(dirEntity->d_name)) {
            string path = string(PROC_DIRECTORY) + dirEntity->d_name + "/cmdline";

            ifstream cmdLineFile(path.c_str());
            string cmdLine;

            if (cmdLineFile) 
                getline(cmdLineFile, cmdLine);
            if(!strcmp(cmdLine.c_str(), "./par"))
                cout << "pid: " << dirEntity->d_name << " " << cmdLine << endl << endl;
        }
    }
    closedir(dir_proc);
}

void forkProcess(char* argv[], char* envp[]) {
    pid_t pid = fork();

    if(pid == -1) {
        cout << "Error when create new process";
        exit(1);
    }
    if(pid == 0){
        execve(CHILD_PATH, argv, envp);  // запускаем программу
    }
    if(pid > 0) {
        cout << "\nI am parent, I create new process\n";
    }

    allProcesses.push_back(pid);
}

void action(ProcessesActions actionFlag, bool isAllow = false) {
    switch (actionFlag) {
        case 0: {
            cout << "\nAll child process killed\n";
            for(auto i: allProcesses) {
                kill(i, SIGKILL);
            }
        }; break;

        case 1: {
            cout << "\nAll processes pids";
            if(allProcesses.size() > 0) {
                for(auto i: allProcesses)
                    cout << "\n - " << i;
            }
            else {
                cout << "\nEmpty...";
            }
        }; break;

        case 2: {
            if(isAllow) {
                cout << "\nAllow";
            }
            else cout << "\nDisallow";

            cout  << " print for all children\n";

            for(auto i: allProcesses) {
                kill(i, isAllow?SIGUSR1:SIGUSR2);
            }
        }; break;

        case 3: {
            cout << "\nAll processes\n";
            readProcessesFromDir();
        }; break;

        default:
            break;
    }
}


int main(int argc, char* argv[], char* envp[]) {
    while (1) {
        cout  << "\n\nEnter symbol(+, -, l, k, s, g, s<num>, g<num>, p<num>, q - exit): ";

        string symbol;

        cin.clear();
        cin >> symbol;

        if(symbol == "+") forkProcess(argv, envp);
        if(symbol == "-") {
            cout << "\nLast child process killed\n";
            if(allProcesses.size() > 0)
                kill(allProcesses[allProcesses.size() -1], SIGKILL);
        }

        if(symbol == "l") action(readFromDir);
        if(symbol == "k") action(killAll);
        if(symbol == "s") action(allowStdoutForAll, false);
        if(symbol == "g") action(allowStdoutForAll, true);
        if(symbol == "c") action(showAll);
        if(symbol == "q") {
            action(killAll);
            break;
        }

        if(symbol.length() > 1) {
            char f = symbol[0];
            int number = stoi(symbol.erase(0, 1));

            if(number > 0) {
                if(f == 's') {
                    cout << "Disallow print for " << number - 1 << " child";
                    kill(allProcesses[number-1], SIGUSR2);
                }
                if(f == 'g') {
                    cout << "Allow print for " << number - 1 << " child";
                    kill(allProcesses[number-1], SIGUSR1);
                }
                if(f == 'p') {
                    action(allowStdoutForAll, false);
                    kill(allProcesses[number-1], SIGUSR1);
                }
            }
        }
    }
    
    return 0;
}