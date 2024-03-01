#include "LinearSearch.h"

bool LinearSearch::search(const std::vector<int> &data) const
{
    for (int value : data)
    {
        if (value > 5)
        {
            return true; // Value over 5 found
        }
    }
    return false; // No value over 5 found
}
