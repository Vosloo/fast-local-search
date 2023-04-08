#pragma once

#include "Score.hpp"

class CsvWriter {
private:
    char delimiter = ',';

public:
    void writeScore(Score* score, std::string filename);
};
