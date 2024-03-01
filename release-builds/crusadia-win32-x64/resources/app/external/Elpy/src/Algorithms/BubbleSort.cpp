#include "BubbleSort.h"
#include <algorithm>
#include <sstream>

void BubbleSort::sort(std::vector<std::string> &values) const
{
    bool swapped;
    int n = values.size();
    do
    {
        swapped = false;
        for (int i = 1; i < n; i++)
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
