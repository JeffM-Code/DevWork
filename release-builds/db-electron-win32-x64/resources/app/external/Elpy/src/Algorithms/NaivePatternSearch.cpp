#include "NaivePatternSearch.h"

bool NaivePatternSearch::search(const std::string &text, const std::string &pattern) const
{
    size_t M = pattern.length();
    size_t N = text.length();

    if (M > N)
    {
        return false;
    }

    for (size_t i = 0; i <= N - M; i++)
    {
        size_t j;
        for (j = 0; j < M; j++)
        {
            if (text[i + j] != pattern[j])
            {
                break;
            }
        }
        if (j == M)
        {
            return true;
        }
    }
    return false;
}
