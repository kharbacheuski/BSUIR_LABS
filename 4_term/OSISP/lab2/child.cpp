#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <fstream> 

using namespace std;

int main(int argc, char* argv[]) {
    cout << "\nHello, i am child! \n" << "My pid = " << getpid() << "\n";

    ifstream file(argv[1]); // создаем объект класса ifstream

    cout << "ENVS FROM FILE: \n";

    if(file.is_open() && !file.bad()) {
        string env;

        while(!file.eof()) {
            getline(file, env);
            cout << "\t\n" << env << "-" << getenv(env.c_str()) << "\n";
        }

        file.close();
    }

    cout << "\n\n";

    return 0;
}