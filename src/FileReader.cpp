#include <filesystem>
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
    std::filesystem::path path = std::filesystem::current_path() / "../data" / "instances" / filename;
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open TSP instance: " + path.string());
    }

    Node** nodes;
    int numberOfNodes = -1;
    bool coordsSection = false;
    int curInd = 0;

    int dimNum = -1;
    std::string dimension = "DIMENSION";

    std::string line;
    std::vector<std::string> split;
    while (std::getline(file, line)) {
        this->splitString(line, split);

        if (dimNum == -1) {
            if (split.size() == 2) {
                dimNum = 1;
                dimension += ":";
            } else if (split.size() == 3) {
                dimNum = 2;
            } else {
                throw std::runtime_error("Should not happen - more than 3 splits in line");
            }
        }

        if (split[0] == "EOF") {
            break;
        }
        if (!coordsSection) {
            if (split[0] == dimension) {
                numberOfNodes = std::stoi(split[dimNum]);
                nodes = new Node*[numberOfNodes];
            } else if (split[0] == "NODE_COORD_SECTION") {
                coordsSection = true;
            }
        } else {
            // Index is 1-based, so we subtract 1
            nodes[curInd] = new Node(std::stoi(split[0]) - 1, std::stod(split[1]), std::stod(split[2]));
            curInd++;
        }
    }

    file.close();

    if (numberOfNodes == -1) {
        throw std::runtime_error("Could not find number of nodes in file");
    }

    return Instance(nodes, numberOfNodes);
}