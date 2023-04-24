#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class SimulatedAnnealingAlgorithm : public AbstractAlgorithm {
private:
    int instanceSize;
    int neighborhoodSize;
    float temperature_cooling;
    int** neigbourhood;
public:
    SimulatedAnnealingAlgorithm(int instanceSize, float temperature_cooling);
    ~SimulatedAnnealingAlgorithm();
    Solution* run(Solution* initialSolution, int& noEvaluations, int& noSteps) override;
};
