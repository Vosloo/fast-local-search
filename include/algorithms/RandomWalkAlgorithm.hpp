#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class RandomWalkAlgorithm : public AbstractAlgorithm {
public:
    Solution run(Solution& initialSolution) override;
};


