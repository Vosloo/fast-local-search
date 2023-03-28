#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"


class RandomAlgorithm : public AbstractAlgorithm {
public:
    Solution run(Solution &initialSolution) override;
};
