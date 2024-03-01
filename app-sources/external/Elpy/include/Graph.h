#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"
#include <unordered_map>
#include <string>
#include <vector>

class Graph
{
public:
    std::unordered_map<std::string, GraphNode *> nodes;

    void addNode(std::string data, std::string filename);
    void addEdge(std::string fromData, std::string fromFilename, std::string toData, std::string toFilename);
    void printGraph() const;

    ~Graph();
};

#endif
