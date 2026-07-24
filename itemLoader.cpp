#include "itemLoader.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> loadItems(const std::string& fileName) {
    std::vector<std::string> sequences;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file \"" << fileName << "\"\n";
        return sequences;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (!line.empty()) {
            sequences.push_back(line);
        }
    }

    return sequences;
}