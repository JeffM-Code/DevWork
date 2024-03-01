#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <vector>
#include <string>

class BubbleSort
{
public:
    void sort(std::vector<std::string> &values) const;

private:
    static int extractNumber(const std::string &s);
};

#endif // BUBBLESORT_H
