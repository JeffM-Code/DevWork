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

    // Attempt to get USERPROFILE environment variable
    if (_dupenv_s(&userPath, &pathSize, "USERPROFILE") == 0 && userPath != nullptr)
    {
        homePath = userPath;
    }
    else
    {
        // If USERPROFILE is not found, try HOME
        if (_dupenv_s(&userPath, &pathSize, "HOME") == 0 && userPath != nullptr)
        {
            homePath = userPath;
        }
    }

    // It's important to free the allocated memory by _dupenv_s
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

    // Ensure the write directory exists
    fs::create_directories(writePath);

    // Log the write path for verification
    std::cout << "Write directory set to: " << writePath << "\n\n";
    
    // "C:\Users\jeffe\Documents\release-builds\crusadia-win32-x64\resources\app\workflow"
    // Additional setup for DirectoryTree
    std::filesystem::path workflowPath = homePath / "workflow";

    directoryTree = new DirectoryTree(workflowPath.string());
}

void DataStructureManager::loadData()
{
    for (const auto &entry : std::filesystem::directory_iterator(readPath))
    {
        // Skip non-txt files
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

        std::string filename = entry.path().stem().string(); // Extract filename without extension
        std::string line;                                    // Store each line read from the file

        std::cout << "Loading data for: " << filename << " ..."
                  << "\n\n";

        while (std::getline(file, line))
        {
            // Assuming 'queue' and 'stack' are your abstract data structures
            std::string queueFilename = filename + "_queue_enqueued";
            std::string stackFilename = filename + "_stack_pushed";

            // Perform enqueue and push operations
            queue.enqueue(line, queueFilename);
            stack.push(line, stackFilename);

            // Log operations with specific data
            if (dataGraph.nodes.find(queueFilename) == dataGraph.nodes.end())
            {
                dataGraph.addNode("", queueFilename); // Add node if it doesn't exist, using "" for data since filename is used as key
            }
            dataGraph.nodes[queueFilename]->addOperation("Data Enqueued", line);

            if (dataGraph.nodes.find(stackFilename) == dataGraph.nodes.end())
            {
                dataGraph.addNode("", stackFilename); // Add node if it doesn't exist
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

        // Construct the path for the output file dynamically
        std::filesystem::path outputPath = writePath / (dequeuedFilename + ".txt");
        std::ofstream outFile(outputPath, std::ios_base::app);
        if (!outFile)
        {
            std::cerr << "Failed to write to file: " << outputPath << std::endl;
            continue;
        }

        // Write the dequeued data to the file
        outFile << data << std::endl;

        // Log the dequeuing operation with specific data
        if (dataGraph.nodes.find(dequeuedFilename) == dataGraph.nodes.end())
        {
            dataGraph.addNode("", dequeuedFilename); // Add node if it doesn't exist
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

        // Construct the path for the output file dynamically
        std::filesystem::path outputPath = writePath / (poppedFilename + ".txt");
        std::ofstream outFile(outputPath, std::ios_base::app);
        if (!outFile)
        {
            std::cerr << "Failed to write to file: " << outputPath << std::endl;
            continue;
        }

        // Write the popped data to the file
        outFile << data << std::endl;

        // Log the popping operation with specific data
        if (dataGraph.nodes.find(poppedFilename) == dataGraph.nodes.end())
        {
            dataGraph.addNode("", poppedFilename); // Add node if it doesn't exist
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
        directoryTree->build(); // Build the directory tree
        directoryTree->print(); // Print the directory tree
    }
    else
    {
        std::cerr << "Directory Tree is not initialized.\n";
    }
}
