#pragma once
#include <queue>

class Message {
public:
    char type;
    short hash; // hashsum
    char size;
    char data[255];

    Message() {};
};

class QueueExtension {
public:
    std::queue<Message> messages;
    int inCount = 0;
    int outCount = 0;

    QueueExtension() {}
    
    void push(Message m) {
        messages.push(m);
        inCount++;
    };

    Message pop() {
        Message m = messages.front();
        messages.pop();
        outCount++;
        return m;
    };

    bool isEmpty() {
        return messages.empty();
    };
};
