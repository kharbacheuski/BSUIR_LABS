#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#include "node.cpp"
#include "consumer.cpp"
#include "producer.cpp"
#include <thread>
#include <unistd.h>
#include <mutex>
#include <functional>
#include <condition_variable>

using namespace std;

std::mutex g_lock;
std::condition_variable cond_var;
bool isClosed = false;


void action(Node* node, QueueExtension* broker) {
    while(1) {
        Message* msg = node->type == ThreadProgramType::PRODUCER ? Producer::generateMessage() : new Message();

        std::unique_lock<std::mutex> locker(g_lock);

        try{
            cond_var.wait(locker, []{ return !isClosed;});
            isClosed = true;

            node->action(broker, msg);
            
            isClosed = false;
            locker.unlock();
            cond_var.notify_one();

            free(msg);
            sleep(2);
        }
        catch (...) {
            isClosed = false;
            locker.unlock();
            cond_var.notify_one();
        }
    }
}

Node* createNode(char type, int producersCount, int consumersCount) {
    if(type == 'p')
        cout << "\n" << "Producer thread " << producersCount << " created";
    else cout << "\n" << "Consumer thread " << consumersCount << " created";
    
    Node* node = type == 'p' ?  (Node*)new Producer(producersCount) : (Node*)new Consumer(consumersCount);
    return node;
}

int main(int argc, char** argv, char** envp) {
    QueueExtension *broker = new QueueExtension();
    broker->inCount = broker->outCount = 0;

    char ch;
    int consumerCount = 0;
    int producerCount = 0;

    vector<thread> threads;

    while(1)
    {
        cout << endl << endl << "Input character(c - consumer, p - producer, q - exit): ";

        cin.clear();
        cin >> ch;

        if(ch == 'q') break;
        
        Node* node = createNode(ch, producerCount, consumerCount);

        threads.emplace_back(action, node, broker);
    }

    for(int i = 0; i < threads.size(); i++)
        threads[i].detach();

    return 0;   
}
