#include "lcs.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string lcs(const std::string& string1, const std::string& string2) {
    const int m = static_cast<int>(string1.size());
    const int n = static_cast<int>(string2.size());

    // DP table: LCS_table[i][j] = length of LCS of prefixes string1[0..i) and string2[0..j)
    std::vector<std::vector<int>> LCS_table(m + 1, std::vector<int>(n + 1, 0));

    // Fill the table bottom-up
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (string1[i - 1] == string2[j - 1]) {
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            } else {
                LCS_table[i][j] = std::max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
            }
        }
    }

    // Reconstruct one LCS by tracing back from the bottom-right corner
    int index = LCS_table[m][n];
    std::string result(index, '\0');

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (string1[i - 1] == string2[j - 1]) {
            result[--index] = string1[i - 1];
            --i;
            --j;
        } else if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <sequence1> <sequence2>\n";
        return 1;
    }

    const std::string seq1 = argv[1];
    const std::string seq2 = argv[2];

    const std::string result = lcs(seq1, seq2);
    std::cout << "LCS: " << result.size() << " " << result << '\n';

    return 0;
}