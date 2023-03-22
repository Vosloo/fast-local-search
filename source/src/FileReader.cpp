#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "FileReader.hpp"

void FileReader::splitString(std::string& str, std::vector<std::string>& split, char delimiter)
{
    if (split.size() > 0) {
        split.clear();
    }

    int start = 0;
    int end = str.find(delimiter);
    while (end != -1) {
        split.push_back(str.substr(start, end - start));
        start = end + 1; // +1 to get rid of the delimiter
        end = str.find(delimiter, start);
    }
    split.push_back(str.substr(start, end - start));
}

std::vector<Node> FileReader::loadTspInstance(std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::vector<Node> nodes;
    int numberOfNodes = -1;
    bool coordsSection = false;

    std::string line;
    std::vector<std::string> split;
    while (std::getline(file, line)) {
        this->splitString(line, split);

        if (split[0] == "EOF") {
            break;
        }
        if (!coordsSection) {
            if (split[0] == "DIMENSION:") {
                numberOfNodes = std::stoi(split[1]);
            } else if (split[0] == "NODE_COORD_SECTION") {
                coordsSection = true;
            }
        } else {
            nodes.push_back(Node(
                std::stoi(split[0]),
                std::stoi(split[1]),
                std::stoi(split[2])));
        }
    }

    file.close();

    if (numberOfNodes == -1) {
        throw std::runtime_error("Could not find number of nodes in file");
    }

    return nodes;
}