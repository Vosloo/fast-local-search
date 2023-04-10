#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class GreedyAlgorithm : public AbstractAlgorithm {
private:
    int instanceSize;
    int neigbourhoodSize;
    int** neigbourhood;
public:
    GreedyAlgorithm(int instanceSize);
    ~GreedyAlgorithm();
    Solution* run(Solution* initialSolution, int& noEvaluations, int& noSteps) override;
};
