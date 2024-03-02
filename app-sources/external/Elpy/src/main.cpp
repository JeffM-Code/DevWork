#include "DataStructureManager.h"
#include "AlgorithmManager.h"
#include "Graph.h"
#include "DirectoryTree.h"

#include <iostream>
#include <string>
#include <exception>

int main()
{
    try
    {
        std::cout << "*.*.*..*.*.** ELPY *.*.*..*.*.**\n"
                  << std::endl;

        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        

        /*
        Data structures
        */
        DataStructureManager dataStructureManager(std::filesystem::current_path().string());

        dataStructureManager.loadData();
        dataStructureManager.processQueueData();
        dataStructureManager.processStackData();

        /*
        Algorithms
        */
        AlgorithmManager algorithmManager;

        // std::string pattern;
        // std::cout << "Enter search pattern: ";
        // std::getline(std::cin, pattern); // Use getline to include whitespaces

        // algorithmManager.performPatternSearch(pattern);
        // algorithmManager.performLinearSearch();
        algorithmManager.performBubbleSort();
        algorithmManager.performMergeSort();
        algorithmManager.performQuickSort();

        /*
        **Summary**

        */
        std::cout << "\n\n*************************************************************************************************\n\n";
        std::cout << "--SUMMARY--\n\n";
        std::cout << "Data:\n";
        dataStructureManager.printDirectoryTree();
        std::cout << "\n\n";
        std::cout << "Processing:\n";
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
