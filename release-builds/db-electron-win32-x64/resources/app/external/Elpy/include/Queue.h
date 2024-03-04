#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

class Queue
{
private:
    Node *front;
    Node *rear;
    int size;

public:
    Queue();
    ~Queue();
    void enqueue(const std::string &data, const std::string &filename);
    std::pair<std::string, std::string> dequeue();
    bool isEmpty() const;
    int getSize() const;
    void printQueue() const;
};

#endif
