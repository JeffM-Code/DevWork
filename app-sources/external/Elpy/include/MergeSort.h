#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <string>

class MergeSort
{
public:
    // Public interface to sort a vector of strings.
    void sort(std::vector<std::string> &values) const;

private:
    // Helper function that implements the merge sort algorithm.
    void mergeSort(std::vector<std::string> &values, size_t left, size_t right) const;

    // Helper function to merge two sorted halves of the vector.
    void merge(std::vector<std::string> &values, size_t left, size_t middle, size_t right) const;

    // Utility function to extract the first numerical value from a string.
    static int extractNumber(const std::string &s);
};

#endif // MERGESORT_H
