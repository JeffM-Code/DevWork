#include "AlgorithmManager.h"
#include "NaivePatternSearch.h"
#include "LinearSearch.h"
#include "BubbleSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <sstream>

namespace fs = std::filesystem;

AlgorithmManager::AlgorithmManager()
{
    char *userPath = nullptr;
    size_t pathSize = 0;
    errno_t err;

    // Attempt to get USERPROFILE environment variable
    err = _dupenv_s(&userPath, &pathSize, "USERPROFILE");
    if (err || userPath == nullptr)
    {
        // If USERPROFILE is not found, try HOME
        err = _dupenv_s(&userPath, &pathSize, "HOME");
    }

    std::filesystem::path homePath;
    if (!err && userPath != nullptr)
    {
        homePath = userPath;
        free(userPath); // It's important to free the allocated memory by _dupenv_s
    }

    homePath = homePath / "Documents" / "release-builds" / "crusadia-win32-x64" / "resources" / "app";

    searchPath = homePath / "processed_data_streamlining";

    // Log the search path for verification
    std::cout << "Search directory set to: " << searchPath << "\n";
}

void AlgorithmManager::performPatternSearch(const std::string &pattern) const
{
    NaivePatternSearch searcher;
    for (const auto &entry : fs::directory_iterator(searchPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt")
        {
            std::ifstream file(entry.path());
            std::string line;
            int lineNum = 0;

            while (std::getline(file, line))
            {
                lineNum++; // Increment line number for each new line read
                if (searcher.search(line, pattern))
                {
                    // Make sure to report the entire pattern
                    std::cout << "Pattern \"" << pattern << "\" found in file: " << entry.path().filename()
                              << ", on line: " << lineNum << std::endl;
                }
            }
        }
    }
}

void AlgorithmManager::performLinearSearch() const
{
    LinearSearch searcher;
    for (const auto &entry : fs::directory_iterator(searchPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt")
        {
            std::ifstream file(entry.path());
            std::vector<int> numbers;
            std::string line;
            while (std::getline(file, line))
            {
                std::istringstream iss(line);
                int number;
                while (iss >> number)
                {
                    numbers.push_back(number);
                }
            }

            if (searcher.search(numbers))
            {
                std::cout << "Value over 5 found in: " << entry.path().filename() << std::endl;
            }
        }
    }
}

void AlgorithmManager::performBubbleSort() const
{
    BubbleSort sorter;
    std::filesystem::path outputPath = searchPath / "bubble_sorted_processed_data.txt";
    std::ofstream outputFile(outputPath, std::ios::out | std::ios::trunc); // Open for writing and truncate any existing data

    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open output file for bubble sort results." << std::endl;
        return;
    }

    for (const auto &entry : std::filesystem::directory_iterator(searchPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt")
        {
            std::ifstream file(entry.path());
            std::string line;
            std::vector<std::string> values;

            while (std::getline(file, line))
            {
                values.push_back(line);
            }

            // Sort the extracted values
            sorter.sort(values);

            // Write sorted values to the output file
            outputFile << entry.path().filename() << ":\n";
            for (const auto &value : values)
            {
                outputFile << value << ", ";
            }
            outputFile << "\n\n"; // Add a newline for separation between file entries
        }
    }

    // Confirm the successful creation of the bubble sort file
    std::cout << "\n\nBubble sort file successfully created at: " << outputPath << "\n\n\n";
}

void AlgorithmManager::performMergeSort() const
{
    MergeSort sorter;
    std::filesystem::path outputPath = searchPath / "merge_sorted_processed_data.txt"; // Specify the output file for merge-sorted data
    std::ofstream outputFile(outputPath, std::ios::out | std::ios::trunc);             // Open for writing and truncate any existing data

    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open output file for merge sort results." << std::endl;
        return;
    }

    for (const auto &entry : std::filesystem::directory_iterator(searchPath))
    {
        // Skip non-txt files and the bubble_sorted_processed_data.txt file
        if (entry.is_regular_file() && entry.path().extension() == ".txt" && entry.path().filename() != "bubble_sorted_processed_data.txt")
        {
            std::ifstream file(entry.path());
            std::string line;
            std::vector<std::string> values;

            // Read file contents, assuming values are separated by commas
            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                std::string value;
                while (std::getline(ss, value, ','))
                {
                    // Trim spaces before and after the comma
                    value.erase(0, value.find_first_not_of(" \t\n\r\f\v")); // Left trim
                    value.erase(value.find_last_not_of(" \t\n\r\f\v") + 1); // Right trim
                    if (!value.empty())
                    {
                        values.push_back(value);
                    }
                }
            }

            // Apply Merge Sort to the collected values
            sorter.sort(values);

            // Write sorted values to the output file, prefixed with the file title
            outputFile << entry.path().filename() << ":\n";
            for (const auto &value : values)
            {
                outputFile << value << ", ";
            }
            outputFile << "\n\n"; // Add a newline for separation between file entries
        }
    }

    std::cout << "Merge sort file successfully created at: " << outputPath << std::endl; // Confirm the successful creation of the merge sort file
}

void AlgorithmManager::performQuickSort() const
{
    QuickSort sorter;
    // Define the output file path for QuickSort results
    std::filesystem::path outputPath = searchPath / "quick_sorted_processed_data.txt";
    std::ofstream outputFile(outputPath);

    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open output file for quick sort results at: " << outputPath << std::endl;
        return;
    }
    else
    {
        std::cout << "QuickSort processing started. Output file at: " << outputPath << std::endl;
    }

    for (const auto &entry : std::filesystem::directory_iterator(searchPath))
    {
        // Skip the sorted files from BubbleSort and MergeSort
        if (entry.is_regular_file() && entry.path().extension() == ".txt" &&
            entry.path().filename() != "bubble_sorted_processed_data.txt" &&
            entry.path().filename() != "merge_sorted_processed_data.txt")
        {
            std::ifstream file(entry.path());
            if (!file.is_open())
            {
                std::cerr << "Failed to open input file: " << entry.path() << std::endl;
                continue;
            }

            std::vector<std::string> values;
            std::string line;

            // Read file contents
            while (std::getline(file, line))
            {
                // Optionally, trim and validate line before adding
                values.push_back(line);
            }

            file.close(); // Close the file after reading

            // Sort the values using QuickSort
            sorter.sort(values);

            // Write the sorted data to the output file, prefixed with the file's name
            outputFile << entry.path().filename() << ":\n";
            for (const auto &value : values)
            {
                outputFile << value << ", ";
            }
            outputFile << "\n\n"; // Ensure separation between entries
        }
    }

    outputFile.close(); // Close the output file

    std::cout << "QuickSort processing completed. Sorted data written to: " << outputPath << std::endl;
}
