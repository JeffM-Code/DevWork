#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
public:
    std::string data;
    std::string filename;
    Node *next;
    Node *prev;

    Node(const std::string &data, const std::string &filename) : data(data), filename(filename), next(nullptr), prev(nullptr) {}
};

#endif
