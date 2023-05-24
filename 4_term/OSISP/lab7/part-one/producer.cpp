#include <iostream>
#include <string>
#include <string.h>
#include "message.cpp"
#include "node.cpp"

using namespace std;

class Producer: public Node {
private:

    static char* randstring(int length) {
        static char charset[] = "123456789";        
        char *randomString = NULL;

        if (length) {
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
    };

public:
    Producer(int id) : Node(id, ThreadProgramType::PRODUCER) {
        this->id = id;
    };

    int getId() {
        return this->id;
    };

    bool action(QueueExtension *broker, Message* m) {
        cout << "\nPuts " << to_string(broker->inCount) << " message - " << m->data << "\n";
        broker->push(*m);
        return true;
    };

    static Message* generateMessage() {
        Message* m = new Message();
        int num = rand();
        int size = num % 257;
        m->size = size;
        int dataSize;
        
        while(!(dataSize = ((size+3)/4)*4));    

        strcpy(m->data, randstring(dataSize));

        m->hash = dataSize + m->size;
        
        return m;
    };
};
