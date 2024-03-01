#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
public:
    std::string data;
    std::string filename; // Assuming this is for storing related file information
    Node* next;
    Node* prev; // Add a previous pointer to support doubly linked list

    Node(const std::string& data, const std::string& filename) : data(data), filename(filename), next(nullptr), prev(nullptr) {}
};

#endif // NODE_H
