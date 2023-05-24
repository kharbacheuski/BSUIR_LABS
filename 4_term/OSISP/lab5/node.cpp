#pragma once
#include <string>
#include "message.cpp"

enum ThreadProgramType {
    CONSUMER,
    PRODUCER
};

class Node {
protected:
    int id;

public:
    ThreadProgramType type;

    Node(int id, ThreadProgramType type) {
        this->id = id; 
        this->type = type; 
    };

    int getId() {
        return id;
    };

    virtual bool action(QueueExtension* broker, Message*m) = 0;
};