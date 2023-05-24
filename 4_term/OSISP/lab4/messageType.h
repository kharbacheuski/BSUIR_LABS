#define PERMISSIONS 0777

enum ChildProgramType {
    CONSUMER,
    PRODUCER
}

class Message {
public:
    char type;

    short hash; // hashsum
    
    char size;

    char data[255];

    Message(){}
};

class MessagesStack {
public:
    int popCount = 0;
    int pushCount = 0;

    Message messages[255];
    
    void push(Message msg){
        messages[pushCount-popCount] = msg;
        pushCount++;
    }

    Message pop() {
        Message tmp = messages[pushCount - popCount]
        popCount++

        return tmp;
    }

    bool isEmpty(){
        return pushCount == popCount;
    }
};
