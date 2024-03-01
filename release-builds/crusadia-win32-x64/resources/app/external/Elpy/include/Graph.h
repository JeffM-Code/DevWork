#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"
#include <unordered_map>
#include <string>
#include <vector>

class Graph {
public:
    std::unordered_map<std::string, GraphNode*> nodes;

    // Add a node to the graph
    void addNode(std::string data, std::string filename);

    // Add an edge between two nodes
    void addEdge(std::string fromData, std::string fromFilename, std::string toData, std::string toFilename);
    
    // Additional methods as needed
    void printGraph() const;

    // Destructor to clean up dynamically allocated nodes
    ~Graph();
};

#endif // GRAPH_H
