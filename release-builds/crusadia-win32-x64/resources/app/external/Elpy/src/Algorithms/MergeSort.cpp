#include "MergeSort.h"
#include <sstream>
#include <vector>

// Update parameter types to size_t to avoid narrowing conversions
void MergeSort::sort(std::vector<std::string> &values) const
{
    if (!values.empty())
    {
        mergeSort(values, 0, values.size() - 1);
    }
}

void MergeSort::mergeSort(std::vector<std::string> &values, size_t left, size_t right) const
{
    if (left < right)
    {
        size_t middle = left + (right - left) / 2;
        mergeSort(values, left, middle);
        mergeSort(values, middle + 1, right);
        merge(values, left, middle, right);
    }
}

void MergeSort::merge(std::vector<std::string> &values, size_t left, size_t middle, size_t right) const
{
    size_t n1 = middle - left + 1;
    size_t n2 = right - middle;
    std::vector<std::string> L(n1), R(n2);

    for (size_t i = 0; i < n1; i++)
        L[i] = values[left + i];
    for (size_t j = 0; j < n2; j++)
        R[j] = values[middle + 1 + j];

    size_t i = 0, j = 0;
    size_t k = left;
    while (i < n1 && j < n2)
    {
        if (extractNumber(L[i]) <= extractNumber(R[j]))
        {
            values[k] = L[i++];
        }
        else
        {
            values[k] = R[j++];
        }
        k++;
    }

    while (i < n1)
    {
        values[k++] = L[i++];
    }

    while (j < n2)
    {
        values[k++] = R[j++];
    }
}

int MergeSort::extractNumber(const std::string &s)
{
    std::istringstream iss(s);
    double number;
    if (iss >> number)
    {
        return static_cast<int>(number);
    }
    return 0;
}
