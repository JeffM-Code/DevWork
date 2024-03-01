#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "Node.h"
#include <vector>
#include <string>
#include <utility> // For std::pair to store operation and data together

class GraphNode {
public:
    Node* dataNode; // Pointer to the actual data node
    std::vector<GraphNode*> adjacents; // Adjacency list for connected nodes
    // Vector to store operations and the data involved in those operations
    std::vector<std::pair<std::string, std::string>> operations;

    // Constructor that initializes the node with the data node
    GraphNode(Node* dataNode) : dataNode(dataNode) {}

    // Method to add an edge from this node to another node
    void addEdge(GraphNode* node) {
        adjacents.push_back(node);
    }

    // Method to add an operation performed on this node, along with the specific data involved
    void addOperation(const std::string& operation, const std::string& data) {
        operations.emplace_back(operation, data);
    }
};

#endif // GRAPHNODE_H
