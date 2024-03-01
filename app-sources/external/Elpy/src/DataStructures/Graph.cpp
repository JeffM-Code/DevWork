#include "Graph.h"
#include <iostream>

void Graph::addNode(std::string data, std::string filename)
{
    Node *newNode = new Node(data, filename);
    GraphNode *newGraphNode = new GraphNode(newNode);
    nodes[filename] = newGraphNode;
}

void Graph::addEdge(std::string fromData, std::string fromFilename, std::string toData, std::string toFilename)
{
    if (nodes.find(fromFilename) == nodes.end() || nodes.find(toFilename) == nodes.end())
    {
        return;
    }

    nodes[fromFilename]->addEdge(nodes[toFilename]);
}

Graph::~Graph()
{
    for (auto &nodePair : nodes)
    {
        delete nodePair.second->dataNode;
        delete nodePair.second;
    }
    nodes.clear();
}

void Graph::printGraph() const
{
    for (const auto &pair : nodes)
    {
        std::cout << pair.first << " OPERATION(S): ";
        for (const auto &[operation, data] : pair.second->operations)
        {
            std::cout << operation << ": " << data << "; ";
        }
        std::cout << "\n\n";
    }
}
