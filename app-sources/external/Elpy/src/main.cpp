#include "DataStructureManager.h"
#include "AlgorithmManager.h"

#include <filesystem>
#include <iostream>
#include <string>

int main()
{
    try
    {
        std::cout << "*.*.*..*.*.** ELPY *.*.*..*.*.**\n\n";

        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Current working directory: " << currentPath << std::endl;

        std::filesystem::path basePath = currentPath;
        while (!basePath.filename().string().empty())
        {
            if (basePath.filename() == "app")
            {
                break;
            }
            basePath = basePath.parent_path();
        }

        if (basePath.filename().string().empty())
        {
            std::cerr << "Failed to find the app-sources directory." << std::endl;
            return EXIT_FAILURE;
        }

        std::string basePathStr = basePath.string();
        std::cout << "Calculated base path: " << basePathStr << std::endl;

        DataStructureManager dataStructureManager(basePathStr);
        dataStructureManager.loadData();
        dataStructureManager.processQueueData();
        dataStructureManager.processStackData();

        AlgorithmManager algorithmManager(basePathStr);
        algorithmManager.performBubbleSort();
        algorithmManager.performMergeSort();
        algorithmManager.performQuickSort();

        std::cout << "\n\n*************************************************************************************************\n\n";
        std::cout << "--SUMMARY--\n\n";
        std::cout << "Data:\n";
        dataStructureManager.printDirectoryTree();
        std::cout << "\n\nProcessing:\n";
        dataStructureManager.dataGraph.printGraph();
        std::cout << "\n*************************************************************************************************\n\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
