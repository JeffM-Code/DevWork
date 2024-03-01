#include "NaivePatternSearch.h"

bool NaivePatternSearch::search(const std::string& text, const std::string& pattern) const {
    size_t M = pattern.length();
    size_t N = text.length();

    // Check if the pattern can fit within the text
    if (M > N) {
        return false;
    }

    for (size_t i = 0; i <= N - M; i++) {
        size_t j;
        for (j = 0; j < M; j++) {
            // If mismatch is found, break out of this loop
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        // If the loop completed, we found a match
        if (j == M) {
            return true; // Pattern found
        }
    }
    return false; // Pattern not found
}
