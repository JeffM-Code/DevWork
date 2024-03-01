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
    // Ensure both nodes exist
    if (nodes.find(fromFilename) == nodes.end() || nodes.find(toFilename) == nodes.end())
    {
        // Handle the error or create missing nodes
        return;
    }

    nodes[fromFilename]->addEdge(nodes[toFilename]);
}

Graph::~Graph()
{
    // Make sure you are not double-deleting or deleting uninitialized pointers
    for (auto &nodePair : nodes)
    {
        delete nodePair.second->dataNode; // Only delete if you have new'ed in the corresponding GraphNode
        delete nodePair.second;           // Only delete if you have new'ed a GraphNode
    }
    nodes.clear(); // Clear the container after deleting all pointers
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
