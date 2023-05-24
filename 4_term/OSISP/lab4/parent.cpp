#include <iostream>
#include <algorithm>
#include <string>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <vector>
#include <sys/shm.h>
#include "messageType.h"

#define CHILD_PROGRAM_NAME "child"

#define SEMAPHORE_NAME "/semName"

using namespace std;


pid_t createChildProcess(char* programPath, char** argv, char** envp) {
    pid_t p = fork();
    
    if(p == 0) {
        execve(programPath, argv, envp);
    }
    else if(p > 0) {
        cout << "Parent PID = " << getpid() << endl;
    }   

    return p;
}

char** createChildProcessArgv(const char* name, ChildProgramType type) {
    size_t argument_size = 255*sizeof(char);
    char** argv = new char*[3];

    argv[0] = new char[argument_size]; 
    argv[1] = new char[argument_size]; 
    argv[2] = NULL;

    strcpy(argv[0], name);
    strcpy(argv[1], to_string(type).c_str());

    return argv;
}

int main(int argc, char** argv, char** envp) {
    int shmid = shmget(0x1234, sizeof(MessagesStack), IPC_CREAT | PERMISSIONS);

    MessagesStack *delivery = (MessagesStack*)shmat(shmid, NULL, 0);
    delivery->pushCount = delivery->popCount = 0;

    sem_t* sem = sem_open(SEMAPHORE_NAME, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR, 1);

    int childProcessesCount = 0;

    vector<pid_t> processes;

    char ch;

    while(1) {

        cout << "\n\nEnter symbol(p - provider, c - consumer): ";

        cin.clear();
        cin >> ch;
        
        ChildProgramType childProgramType; 

        switch (ch) {
            case 'p': childProgramType = PRODUCER; break; 
            case 'c': childProgramType = CONSUMER; break;
            default:
                break;
        }


        string childN = CHILD_PROGRAM_NAME + "_" to_string(childProcessesCount++); // Create child name (child_1, child_2 ....)

        char** childArgv = createChildProcessArgv(childN.c_str(), childProgramType);

        pid_t childPid = createChildProcess("./child", childArgv, envp);

        processes.push_back(childPid);
    }

    for(auto pid : processes) 
        kill(pid, SIGKILL);

    sem_close(sem);
    sem_destroy(sem);
    close(shmid);

    return 0;   
}
