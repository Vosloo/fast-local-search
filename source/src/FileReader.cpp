#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "FileReader.hpp"
#include "Instance.hpp"

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

Instance FileReader::loadTspInstance(std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    Node** nodes;
    int numberOfNodes = -1;
    bool coordsSection = false;
    int curInd = 0;

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
                nodes = new Node*[numberOfNodes];
            } else if (split[0] == "NODE_COORD_SECTION") {
                coordsSection = true;
            }
        } else {
            nodes[curInd] = new Node(std::stoi(split[0]), std::stoi(split[1]), std::stoi(split[2]));
            curInd++;
        }
    }

    file.close();

    if (numberOfNodes == -1) {
        throw std::runtime_error("Could not find number of nodes in file");
    }

    return Instance(nodes, numberOfNodes);
}