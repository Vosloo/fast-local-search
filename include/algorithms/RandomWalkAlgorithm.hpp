#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class RandomWalkAlgorithm : public AbstractAlgorithm {
private:
    float maxRuntime;

public:
    Solution* run(Solution* initialSolution, int& noEvaluations, int& noSteps) override;
    RandomWalkAlgorithm(float maxRuntime);
};


