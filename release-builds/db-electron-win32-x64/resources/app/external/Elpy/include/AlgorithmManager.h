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
    AlgorithmManager(const std::string &basePath);
    void performPatternSearch(const std::string &pattern) const;
    void performLinearSearch() const;
    void performBubbleSort() const;
    void performMergeSort() const;
    void performQuickSort() const;
};

#endif
