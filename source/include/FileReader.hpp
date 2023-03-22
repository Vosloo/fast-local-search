#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Node.hpp"

class FileReader
{
private:
    void splitString(std::string &str, std::vector<std::string> &split, char delimiter = ' ');
public:
    std::vector<Node> loadTspInstance(std::string &filename);
};
