#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "FileReader.hpp"
#include "Instance.hpp"
#include "utils.hpp"

void FileReader::splitString(std::string& str, std::vector<std::string>& split, char delimiter)
{
    if (split.size() > 0) {
        split.clear();
    }

    int start = 0;
    int end = str.find(delimiter);
    while (end != -1) {
        std::string s = str.substr(start, end - start);
        if (s.size() > 0) {
            split.push_back(s);
        }
        start = end + 1;
        end = str.find(delimiter, start);
    }
    split.push_back(str.substr(start, end - start));
}

Instance FileReader::loadTspInstance(std::string filename)
{
    std::filesystem::path path = std::filesystem::current_path() / "../data" / "instances" / (filename + ".tsp");
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open TSP instance: " + path.string());
    }

    Node** nodes;
    int numberOfNodes = -1;
    bool coordsSection = false;
    int curInd = 0;

    std::string dimension = "DIMENSION";
    std::regex dimNumRegex("[0-9]+");
    std::smatch match;

    std::string line;
    std::vector<std::string> split;
    while (std::getline(file, line)) {
        this->splitString(line, split);

        if (split[0] == "EOF") {
            break;
        }
        if (!coordsSection) {
            if (split[0].rfind(dimension, 0) == 0) {
                std::regex_search(line, match, dimNumRegex);
                if (match.size() == 0) {
                    throw std::runtime_error("Could not find number of nodes in file!");
                }

                numberOfNodes = std::stoi(match[0]);
                nodes = new Node*[numberOfNodes];
            } else if (split[0] == "NODE_COORD_SECTION") {
                if (numberOfNodes == -1) {
                    throw std::runtime_error("Could not find number of nodes in file!");
                }
                coordsSection = true;
            }
        } else {
            int x = std::stoi(split[0]) - 1;
            double y = std::stod(split[1]);
            double z = std::stod(split[2]);
            // Index is 1-based, so we subtract 1
            nodes[curInd] = new Node(x, y, z);
            curInd++;
        }
    }

    file.close();

    if (numberOfNodes == -1) {
        throw std::runtime_error("Could not find number of nodes in file");
    }

    std::string name = filename.substr(0, filename.find_last_of('.'));

    return Instance(nodes, numberOfNodes, name);
}