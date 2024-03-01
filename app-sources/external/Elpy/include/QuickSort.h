#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <string>

class QuickSort
{
public:
    void sort(std::vector<std::string> &values) const;

private:
    void quickSort(std::vector<std::string> &values, size_t low, size_t high) const;
    size_t partition(std::vector<std::string> &values, size_t low, size_t high) const;
    static int extractNumber(const std::string &s);
};

#endif // QUICKSORT_H
