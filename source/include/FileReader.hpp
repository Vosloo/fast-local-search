#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Instance.hpp"

class FileReader
{
private:
    void splitString(std::string &str, std::vector<std::string> &split, char delimiter = ' ');
public:
    Instance loadTspInstance(std::string &filename);
};
