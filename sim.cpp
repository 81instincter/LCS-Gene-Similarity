#include "sim.hpp"
#include "itemLoader.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

/**
 * Space-optimised bottom-up LCS length only.
 * Uses a single rolling array of size n+1 instead of a full (m+1)×(n+1) table.
 * Time: O(m·n)   Space: O(min(m,n)) after a possible swap.
 */
int lcsLength(const std::string& s1, const std::string& s2) {
    // Ensure we allocate the smaller dimension for the DP array
    const std::string* a = &s1;
    const std::string* b = &s2;
    if (a->size() < b->size()) {
        std::swap(a, b);
    }
    const int m = static_cast<int>(a->size());
    const int n = static_cast<int>(b->size());

    std::vector<int> dp(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
        int prev = 0;               // dp[i-1][j-1]
        for (int j = 1; j <= n; ++j) {
            const int temp = dp[j]; // dp[i-1][j]
            if ((*a)[i - 1] == (*b)[j - 1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = std::max(dp[j], dp[j - 1]);
            }
            prev = temp;
        }
    }
    return dp[n];
}

void sim(const std::string& filename) {
    const std::vector<std::string> fileLines = loadItems(filename);

    if (fileLines.empty()) {
        std::cerr << "Error: empty or unreadable input file.\n";
        return;
    }

    int numSequences = 0;
    try {
        numSequences = std::stoi(fileLines[0]);
    } catch (...) {
        std::cerr << "Error: first line must be an integer (sequence count).\n";
        return;
    }

    if (numSequences <= 0 || static_cast<size_t>(numSequences) > fileLines.size() - 1) {
        std::cerr << "Error: invalid sequence count.\n";
        return;
    }

    std::vector<std::string> sequences;
    sequences.reserve(numSequences);
    for (int i = 1; i <= numSequences; ++i) {
        sequences.push_back(fileLines[i]);
    }

    // Upper-triangle computation only; we will mirror for a symmetric display
    std::vector<std::vector<char>> table(numSequences, std::vector<char>(numSequences, '-'));

    for (int r = 0; r < numSequences; ++r) {
        for (int c = r + 1; c < numSequences; ++c) {
            const std::string& s1 = sequences[r];
            const std::string& s2 = sequences[c];

            const int len1 = static_cast<int>(s1.size());
            const int len2 = static_cast<int>(s2.size());
            const int lcsLen = lcsLength(s1, s2);

            const double ratioLen = static_cast<double>(std::min(len1, len2)) /
                                    static_cast<double>(std::max(len1, len2));
            const double ratioLCS = static_cast<double>(lcsLen) /
                                    static_cast<double>(std::min(len1, len2));

            char label = 'D';
            if (ratioLen > 0.9 && ratioLCS > 0.9) {
                label = 'H';
            } else if (ratioLen > 0.8 && ratioLCS > 0.8) {
                label = 'M';
            } else if (ratioLen > 0.5 && ratioLCS > 0.5) {
                label = 'L';
            }

            table[r][c] = label;
            table[c][r] = label;   // symmetry
        }
    }

    // Pretty-print the similarity matrix
    std::cout << "Gene Sequence Similarity Matrix\n";
    std::cout << "(H = High, M = Medium, L = Low, D = Dissimilar, - = self)\n\n";

    // Column headers
    std::cout << "    ";
    for (int j = 0; j < numSequences; ++j) {
        std::cout << std::setw(3) << (j + 1);
    }
    std::cout << '\n';

    // Rows
    for (int i = 0; i < numSequences; ++i) {
        std::cout << std::setw(2) << (i + 1) << "  ";
        for (int j = 0; j < numSequences; ++j) {
            std::cout << std::setw(3) << table[i][j];
        }
        std::cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <sequences.txt>\n";
        return 1;
    }

    sim(argv[1]);
    return 0;
}