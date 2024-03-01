#include "LinearSearch.h"

bool LinearSearch::search(const std::vector<int> &data) const
{
    for (int value : data)
    {
        if (value > 5)
        {
            return true;
        }
    }
    return false;
}
