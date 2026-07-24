#ifndef LCS_HPP
#define LCS_HPP

#include <string>

/**
 * @brief Computes the Longest Common Subsequence (LCS) of two strings.
 *
 * Uses classic bottom-up dynamic programming with a (m+1) × (n+1) table
 * to reconstruct one valid LCS string (not merely its length).
 *
 * Time:  O(m * n)
 * Space: O(m * n)
 *
 * @param string1 First input sequence
 * @param string2 Second input sequence
 * @return One longest common subsequence (empty string if none exists)
 */
std::string lcs(const std::string& string1, const std::string& string2);

#endif // LCS_HPP