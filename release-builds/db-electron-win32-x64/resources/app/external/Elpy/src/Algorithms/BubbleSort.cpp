#include "BubbleSort.h"
#include <algorithm>
#include <sstream>

void BubbleSort::sort(std::vector<std::string> &values) const
{
    bool swapped;
    size_t n = values.size();  // Changed type of n to size_t
    do
    {
        swapped = false;
        for (size_t i = 1; i < n; i++)  // Also change the loop variable to size_t
        {
            if (extractNumber(values[i - 1]) > extractNumber(values[i]))
            {
                std::swap(values[i - 1], values[i]);
                swapped = true;
            }
        }
        n--;
    } while (swapped);
}

int BubbleSort::extractNumber(const std::string &s)
{
    std::istringstream iss(s);
    int number;
    iss >> number;
    return number;
}
