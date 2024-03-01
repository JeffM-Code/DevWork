#include "QuickSort.h"
#include <algorithm>
#include <sstream>

#include "QuickSort.h"
#include <algorithm>
#include <sstream>

void QuickSort::sort(std::vector<std::string> &values) const {
    if (!values.empty()) {
        quickSort(values, 0, values.size() - 1);
    }
}

void QuickSort::quickSort(std::vector<std::string> &values, size_t low, size_t high) const {
    if (low < high) {
        size_t pi = partition(values, low, high);

        // Check to prevent underflow when 'pi' is 0.
        // This avoids subtracting 1 from 'pi' when 'pi' is 0, which would underflow since 'size_t' is unsigned.
        if (pi > 0) {
            quickSort(values, low, pi - 1); // Safely call quickSort for the left part if 'pi' is not the first element.
        }
        quickSort(values, pi + 1, high); // Recursively sort the right part.
    }
}

size_t QuickSort::partition(std::vector<std::string> &values, size_t low, size_t high) const {
    int pivot = extractNumber(values[high]);
    size_t i = low - 1;

    for (size_t j = low; j <= high - 1; j++) {
        if (extractNumber(values[j]) < pivot) {
            i++;
            std::swap(values[i], values[j]);
        }
    }
    std::swap(values[i + 1], values[high]);
    return i + 1;
}

// Method extractNumber remains unchanged


// Corrected definition of extractNumber to match the header declaration
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
