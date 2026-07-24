#ifndef SIM_HPP
#define SIM_HPP

#include <string>

/**
 * @brief Performs pairwise similarity analysis on a set of gene sequences.
 *
 * Reads a file whose first line is the number of sequences N, followed by
 * N DNA strings.  Computes a length-optimised bottom-up LCS for every pair
 * (i, j) with i < j and classifies the similarity as:
 *
 *   H  – High      (length ratio > 0.9  &&  LCS ratio > 0.9)
 *   M  – Medium    (length ratio > 0.8  &&  LCS ratio > 0.8)
 *   L  – Low       (length ratio > 0.5  &&  LCS ratio > 0.5)
 *   D  – Dissimilar (everything else)
 *
 * Prints a clean N × N table (symmetric, diagonal marked with '-').
 *
 * @param filename Path to the sequence file (e.g. seqs.txt)
 */
void sim(const std::string& filename);

#endif // SIM_HPP