#pragma once

#include <iostream>

#include "Solution.hpp"

class AbstractAlgorithm {
private:
    std::string algorithmName;
protected:
    void setAlgorithmName(std::string algorithmName) {
        this->algorithmName = algorithmName;
    }
public:
    virtual Solution* run(Solution* initialSolution) = 0;
    virtual ~AbstractAlgorithm() = default;
    std::string getAlgorithmName() {
        return algorithmName;
    }
};
