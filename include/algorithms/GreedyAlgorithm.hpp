#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class GreedyAlgorithm : public AbstractAlgorithm {
public:
    Solution run(Solution& initialSolution) override;
};
