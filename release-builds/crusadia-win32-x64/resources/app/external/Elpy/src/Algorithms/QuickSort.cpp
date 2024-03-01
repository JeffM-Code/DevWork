#include "QuickSort.h"
#include <algorithm>
#include <sstream>

#include "QuickSort.h"
#include <algorithm>
#include <sstream>

void QuickSort::sort(std::vector<std::string> &values) const
{
    if (!values.empty())
    {
        quickSort(values, 0, values.size() - 1);
    }
}

void QuickSort::quickSort(std::vector<std::string> &values, size_t low, size_t high) const
{
    if (low < high)
    {
        size_t pi = partition(values, low, high);

        if (pi > 0)
        {
            quickSort(values, low, pi - 1);
        }
        quickSort(values, pi + 1, high);
    }
}

size_t QuickSort::partition(std::vector<std::string> &values, size_t low, size_t high) const
{
    int pivot = extractNumber(values[high]);
    size_t i = low - 1;

    for (size_t j = low; j <= high - 1; j++)
    {
        if (extractNumber(values[j]) < pivot)
        {
            i++;
            std::swap(values[i], values[j]);
        }
    }
    std::swap(values[i + 1], values[high]);
    return i + 1;
}

int QuickSort::extractNumber(const std::string &s)
{
    std::istringstream iss(s);
    double number;
    if (iss >> number)
    {
        return static_cast<int>(number);
    }
    return 0;
}
