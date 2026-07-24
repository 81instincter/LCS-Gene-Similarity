#ifndef ITEM_LOADER_HPP
#define ITEM_LOADER_HPP

#include <string>
#include <vector>

/**
 * @brief Loads lines from a text file into a vector of strings.
 *
 * Used by the similarity analysis tool to read gene sequence data.
 * The first line is expected to be an integer count; subsequent lines
 * are the DNA sequences themselves.
 *
 * @param fileName Path to the input file
 * @return Vector containing every line of the file (empty on failure)
 */
std::vector<std::string> loadItems(const std::string& fileName);

#endif // ITEM_LOADER_HPP