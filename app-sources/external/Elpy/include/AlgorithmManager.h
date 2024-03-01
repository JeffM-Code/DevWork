#ifndef ALGORITHMMANAGER_H
#define ALGORITHMMANAGER_H

#include <string>
#include <filesystem>

class AlgorithmManager
{
private:
    std::filesystem::path searchPath;

public:
    AlgorithmManager();
    void performPatternSearch(const std::string &pattern) const; // For performing naive pattern search
    void performLinearSearch() const;                            // For performing linear search for values over 5
    void performBubbleSort() const;                              // New method for performing bubble sort on file contents
    void performMergeSort() const;
    void performQuickSort() const;
};

#endif // ALGORITHMMANAGER_H
