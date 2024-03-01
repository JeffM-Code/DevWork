#ifndef DATASTRUCTUREMANAGER_H
#define DATASTRUCTUREMANAGER_H

#include "Queue.h"
#include "Stack.h"
#include "Graph.h"
#include "DirectoryTree.h"

#include <string>
#include <filesystem>

class DataStructureManager
{
private:
    Queue queue;
    Stack stack;
    std::filesystem::path readPath;
    std::filesystem::path writePath;
    DirectoryTree* directoryTree;

public:
    Graph dataGraph;
    DataStructureManager(); // Constructor to setup paths
    void setupPaths(const std::string &baseReadPath = "", const std::string &baseWritePathSuffix = "");
    void loadData(); // Combined loading for both queue and stack
    void processQueueData();
    void processStackData(); // New method for stack processing
    void printDirectoryTree();
};

#endif // DATASTRUCTUREMANAGER_H
