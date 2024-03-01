#include "Stack.h"
#include <iostream>
#include <sstream> // For string stream processing

Stack::Stack() : top(nullptr), size(0) {}

Stack::~Stack()
{
    while (!isEmpty())
    {
        pop();
    }
}

void Stack::push(const std::string& data, const std::string& filename) {
    Node* newNode = new Node(data, filename);
    newNode->next = top;
    top = newNode;
    size++;

    // Log the action and current state
    std::cout << "Pushing: " << data << " with filename: " << filename << std::endl;
    printStack(); // Call printStack here to log the stack's current state
}

std::pair<std::string, std::string> Stack::pop() {
    if (isEmpty()) {
        std::cerr << "Stack is empty, cannot pop." << std::endl;
        return {"", ""};
    }
    Node* temp = top;
    std::pair<std::string, std::string> retData = {temp->data, temp->filename};
    top = top->next;
    delete temp;
    size--;

    // Log the action and current state
    std::cout << "Popping: " << retData.first << " with filename: " << retData.second << std::endl;
    printStack(); // Call printStack here to log the stack's current state after pop
    return retData;
}

bool Stack::isEmpty() const {
    return size == 0;
}

int Stack::getSize() const {
    return size;
}

void Stack::printStack() const {
    std::stringstream ss;
    ss << "Stack size is now: " << size << " with items [";
    Node* current = top;
    while (current != nullptr) {
        ss << current->data;
        if (current->next != nullptr) {
            ss << ", ";
        }
        current = current->next;
    }
    ss << "]";
    std::cout << ss.str() << std::endl;
}
