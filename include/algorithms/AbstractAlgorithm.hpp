#pragma once

#include "Solution.hpp"


class AbstractAlgorithm {
public:
    virtual Solution run(Solution &initialSolution) = 0;
    ~AbstractAlgorithm() = default;
};
