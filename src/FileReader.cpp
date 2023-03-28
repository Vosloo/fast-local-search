#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

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
    std::filesystem::path path = std::filesystem::current_path() / "../data" / filename;
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open TSP instance: " + path.string());
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
            // Index is 1-based, so we subtract 1
            nodes[curInd] = new Node(std::stoi(split[0]) - 1, std::stoi(split[1]), std::stoi(split[2]));
            curInd++;
        }
    }

    file.close();

    if (numberOfNodes == -1) {
        throw std::runtime_error("Could not find number of nodes in file");
    }

    return Instance(nodes, numberOfNodes);
}