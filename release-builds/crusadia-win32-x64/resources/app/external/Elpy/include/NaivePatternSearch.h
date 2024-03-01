#ifndef NAIVEPATTERNSEARCH_H
#define NAIVEPATTERNSEARCH_H

#include <string>

class NaivePatternSearch
{
public:
    // Returns true if the exact pattern is found in the text
    bool search(const std::string &text, const std::string &pattern) const;
};

#endif // NAIVEPATTERNSEARCH_H
