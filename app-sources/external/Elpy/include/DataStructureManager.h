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
    DirectoryTree *directoryTree;

public:
    Graph dataGraph;
    DataStructureManager();
    void setupPaths(const std::string &baseReadPath = "", const std::string &baseWritePathSuffix = "");
    void loadData();
    void processQueueData();
    void processStackData();
    void printDirectoryTree();
};

#endif
