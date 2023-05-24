#include <iostream>
#include <string>
#include <string.h>
#include "node.cpp"

using namespace std;

class Consumer : public Node {
public:

    Consumer(int id): Node(id, ThreadProgramType::CONSUMER) {
        this->id = id;
    };

    int getId() {
        return this->id;
    };

    bool action(QueueExtension *broker, Message* msg) override {
        if(broker->isEmpty())
            return false;

        *msg = broker->pop();

        cout << "\nMessage " << to_string(broker->outCount) << " readed\n";
        return true;
    };
};
