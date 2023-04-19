#pragma once

#include "Score.hpp"

class CsvWriter {
private:
    char delimiter = ';';
    char nodesSeparator = ',';
    std::string nodesToString(Score* score, int* nodes);

public:
    void writeScore(Score* score, std::string filename);
};
