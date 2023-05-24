#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <fstream> 
#include <time.h>
#include <vector>

using namespace std;

#define CICLE_ITERATIONS_COUNT  4

struct sigaction allowSignal, disallowSignal;

bool isStdoutOpen = true;

void openPrint(int signal) {
    isStdoutOpen = true;
}
void closePrint(int signal) {
    isStdoutOpen = false;
}

void signalHandlers() {
    allowSignal.sa_handler = openPrint;
    disallowSignal.sa_handler = closePrint;
    allowSignal.sa_flags = SA_RESTART;
    disallowSignal.sa_flags = SA_RESTART;
    
    sigaction(SIGUSR1, &allowSignal, NULL);
    sigaction(SIGUSR2, &disallowSignal, NULL);
}

struct Ints {
    int a = 0;
    int b = 0;
} ints;

bool contin = false;

vector<Ints> statistic;

void alarmCallback(int var) {
    statistic.push_back(ints);
    contin = !contin;
}

void printStatictic() {
    static int pars = 0;

    for(auto i: statistic) {
        if(i.a != i.b) {
            pars++;
        }
    }

    if(isStdoutOpen)  {
        pid_t id = getpid();
        cout << "\n\n--------------------------------------\n";
        cout << "All statistic: \n";
        cout << "\nCount of pars = " << pars << "\n\n" << "Child pid = " << id; 
        cout << "\n--------------------------------------\n\n";
    }

}

int main(int argc, char* argv[]) {
    int i = 0;
    signalHandlers();

    while(1) {
        if(i++ != 0 && (i % CICLE_ITERATIONS_COUNT == 0)) {
            printStatictic();
        }
        
        signal(SIGALRM, alarmCallback);
        alarm(1);

        contin = false;
        while(1) {  
            if(contin) {
                break;
            }

            ints.a = !ints.a;
            ints.b = !ints.b;
        }
    }

    return 0;
}