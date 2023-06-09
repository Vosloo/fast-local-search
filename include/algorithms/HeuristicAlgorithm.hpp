#pragma once

#include "set"

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class HeuristicAlgorithm : public AbstractAlgorithm {
public:
    Solution* run(Solution* initialSolution, int& noEvaluations, int& noSteps) override;
    HeuristicAlgorithm();
};
