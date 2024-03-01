#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "Node.h"
#include <vector>
#include <string>
#include <utility>

class GraphNode
{
public:
    Node *dataNode;
    std::vector<GraphNode *> adjacents;

    std::vector<std::pair<std::string, std::string>> operations;

    GraphNode(Node *dataNode) : dataNode(dataNode) {}

    void addEdge(GraphNode *node)
    {
        adjacents.push_back(node);
    }

    void addOperation(const std::string &operation, const std::string &data)
    {
        operations.emplace_back(operation, data);
    }
};

#endif
