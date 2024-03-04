#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <string>

class MergeSort
{
public:
    void sort(std::vector<std::string> &values) const;

private:
    void mergeSort(std::vector<std::string> &values, size_t left, size_t right) const;

    void merge(std::vector<std::string> &values, size_t left, size_t middle, size_t right) const;

    static int extractNumber(const std::string &s);
};

#endif
