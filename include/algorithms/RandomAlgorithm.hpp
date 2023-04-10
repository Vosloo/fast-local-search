#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class RandomAlgorithm : public AbstractAlgorithm {
private:
    float maxRuntime;

public:
    Solution* run(Solution* initialSolution, int& noEvaluations, int& noSteps) override;
    RandomAlgorithm(float maxRuntime);
};
