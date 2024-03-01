#include "DataStructureManager.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

DataStructureManager::DataStructureManager()
{
    setupPaths();
}

void DataStructureManager::setupPaths(const std::string &baseReadPath, const std::string &baseWritePathSuffix)
{
    char *userPath = nullptr;
    size_t pathSize = 0;
    std::filesystem::path homePath;

    if (_dupenv_s(&userPath, &pathSize, "USERPROFILE") == 0 && userPath != nullptr)
    {
        homePath = userPath;
    }
    else
    {
        if (_dupenv_s(&userPath, &pathSize, "HOME") == 0 && userPath != nullptr)
        {
            homePath = userPath;
        }
    }

    if (userPath != nullptr)
    {
        free(userPath);
    }

    homePath = homePath / "Documents" / "release-builds" / "crusadia-win32-x64" / "resources" / "app";

    if (baseReadPath.empty())
    {
        readPath = homePath / "external" / "Pisty" / "processed_data";
    }
    else
    {
        readPath = baseReadPath;
    }

    writePath = homePath / "processed_data_streamlining";

    fs::create_directories(writePath);

    std::cout << "Write directory set to: " << writePath << "\n\n";

    std::filesystem::path workflowPath = homePath / "workflow";

    directoryTree = new DirectoryTree(workflowPath.string());
}

void DataStructureManager::loadData()
{
    for (const auto &entry : std::filesystem::directory_iterator(readPath))
    {
        if (!entry.is_regular_file() || entry.path().extension() != ".txt")
        {
            continue;
        }

        std::ifstream file(entry.path());
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << entry.path() << std::endl;
            continue;
        }

        std::string filename = entry.path().stem().string();
        std::string line;

        std::cout << "Loading data for: " << filename << " ..."
                  << "\n\n";

        while (std::getline(file, line))
        {
            std::string queueFilename = filename + "_queue_enqueued";
            std::string stackFilename = filename + "_stack_pushed";

            queue.enqueue(line, queueFilename);
            stack.push(line, stackFilename);

            if (dataGraph.nodes.find(queueFilename) == dataGraph.nodes.end())
            {
                dataGraph.addNode("", queueFilename);
            }
            dataGraph.nodes[queueFilename]->addOperation("Data Enqueued", line);

            if (dataGraph.nodes.find(stackFilename) == dataGraph.nodes.end())
            {
                dataGraph.addNode("", stackFilename);
            }
            dataGraph.nodes[stackFilename]->addOperation("Data Pushed", line);

            std::cout << "Loaded, Queued, and Pushed: " << line << " for " << filename << std::endl;
        }

        std::cout << "\n\n* Data loading completed for: " << filename << "\n\n\n";

        file.close();
    }
}

void DataStructureManager::processQueueData()
{
    std::cout << "Processing queue data..."
              << "\n\n";

    while (!queue.isEmpty())
    {
        auto [data, filename] = queue.dequeue();
        std::string dequeuedFilename = filename + "_dequeued";

        std::filesystem::path outputPath = writePath / (dequeuedFilename + ".txt");
        std::ofstream outFile(outputPath, std::ios_base::app);
        if (!outFile)
        {
            std::cerr << "Failed to write to file: " << outputPath << std::endl;
            continue;
        }

        outFile << data << std::endl;

        if (dataGraph.nodes.find(dequeuedFilename) == dataGraph.nodes.end())
        {
            dataGraph.addNode("", dequeuedFilename);
        }
        dataGraph.nodes[dequeuedFilename]->addOperation("Data Dequeued", data);

        std::cout << "Data Dequeued and Written: " << data << " to -> " << dequeuedFilename << "\n";
    }
    std::cout << "\n\n* Queue processing completed."
              << "\n\n\n";
}

void DataStructureManager::processStackData()
{
    std::cout << "Processing stack data..."
              << "\n\n";

    while (!stack.isEmpty())
    {
        auto [data, filename] = stack.pop();
        std::string poppedFilename = filename + "_popped";

        std::filesystem::path outputPath = writePath / (poppedFilename + ".txt");
        std::ofstream outFile(outputPath, std::ios_base::app);
        if (!outFile)
        {
            std::cerr << "Failed to write to file: " << outputPath << std::endl;
            continue;
        }

        outFile << data << std::endl;

        if (dataGraph.nodes.find(poppedFilename) == dataGraph.nodes.end())
        {
            dataGraph.addNode("", poppedFilename);
        }
        dataGraph.nodes[poppedFilename]->addOperation("Data Popped", data);

        std::cout << "Data Popped and Written: " << data << " to -> " << poppedFilename << "\n";
    }
    std::cout << "\n\n* Stack processing completed."
              << "\n\n\n";
}

void DataStructureManager::printDirectoryTree()
{
    if (directoryTree)
    {
        directoryTree->build();
        directoryTree->print();
    }
    else
    {
        std::cerr << "Directory Tree is not initialized.\n";
    }
}
