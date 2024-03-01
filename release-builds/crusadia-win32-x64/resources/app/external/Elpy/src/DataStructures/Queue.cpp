#include "Queue.h"
#include <iostream>
#include <sstream>

Queue::Queue() : front(nullptr), rear(nullptr), size(0) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(const std::string& data, const std::string& filename) {
    Node* newNode = new Node(data, filename);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        newNode->prev = rear;
        rear = newNode;
    }
    size++;

    std::cout << "Enqueuing: " << data << " with filename: " << filename << std::endl;
    printQueue();
}

std::pair<std::string, std::string> Queue::dequeue() {
    if (isEmpty()) {
        std::cerr << "Queue is empty, cannot dequeue." << std::endl;
        return {"", ""};
    }
    Node* temp = front;
    std::pair<std::string, std::string> retData = {temp->data, temp->filename};
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    } else {
        front->prev = nullptr;
    }
    delete temp;
    size--;

    std::cout << "Dequeuing: " << retData.first << " with filename: " << retData.second << std::endl;
    printQueue();
    return retData;
}

bool Queue::isEmpty() const {
    return size == 0;
}

int Queue::getSize() const {
    return size;
}

void Queue::printQueue() const {
    std::stringstream ss;
    ss << "Queue size is now: " << size << " with items [";
    Node* current = front;
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
