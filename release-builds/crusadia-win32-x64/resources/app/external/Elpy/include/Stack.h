#ifndef STACK_H
#define STACK_H

#include "Node.h" // Include the common Node class

class Stack
{
private:
    Node *top;
    int size;

public:
    Stack();
    ~Stack();
    void push(const std::string &data, const std::string &filename);
    std::pair<std::string, std::string> pop();
    bool isEmpty() const;
    int getSize() const;
    void printStack() const;
};

#endif // STACK_H
