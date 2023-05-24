#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <functional>
#include "messageType.h"

#define SEMAPHORE_NAME "/semName"

using namespace std;

bool pushMessage(MessagesStack *d, Message m) {
    if(d->pushCount >= 255)
        return false;

    d->push(m);

    return true;
}

bool popMessage(MessagesStack *d, Message* msg) {
    if(d->isEmpty())

        return false;
    *msg = d->pop();

    return true;
}

char* randstring(int length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        
    char *randomString = NULL;

    if (length) 
    {
        randomString = new char[length+1];

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

Message generateMessage() {
    Message m;
    int num = rand();
    int size = num % 257;
    m.size = size;
    int dataSize = ((size+3)/4)*4;    

    strcpy(m.data, randstring(dataSize));

    m.hash = dataSize + m.size;
    return m;
}

void lockAction(sem_t * sem, const function<void()>& f) {
	try {
		sem_wait(sem);

		f();

		sem_post(sem);
	}
	catch (...) {
		sem_post(sem);
	}
}

int main(int argc, char** argv) {
    int shmid = shmget(0x1234, sizeof(MessagesStack), PERMISSIONS);
    MessagesStack *delivery = (MessagesStack*) shmat(shmid, NULL, 0);

    sem_t* sem = sem_open(SEMAPHORE_NAME, O_RDWR);
    
    ChildProgramType type = atoi(argv[1]);
    string typeName = type == PRODUCER ? "producer" : "consumer";
    cout << "I am " << argv[0] << " (" << typeName << ") My PID is " << getpid() << endl;

    while(1)
    {
        if(type == PRODUCER)
        {
            Message m = generateMessage();
            lockAction(sem, [&]() {
                if(tryAddMessage(delivery, m))
                    cout << argv[0] << "(PID " << getpid() << ") puts message" << endl; 
            });
        }
        else
        {
            Message m;
            lockAction(sem, [&]() {
                if(tryReadMessage(delivery, &m))
                    cout << "Message " << delivery->outCount << " readed (" << argv[0] << ") data: " << m.data << endl; 
            });
        }
        sleep(2);
    }

    return 0;
}