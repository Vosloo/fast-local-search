#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class SimulatedAnnealingAlgorithm : public AbstractAlgorithm {
private:
    int instanceSize;
    int neighborhoodSize;
    float initialTemperature;
    float temperatureCooling;
    int** neigbourhood;
public:
    SimulatedAnnealingAlgorithm(int instanceSize, float initialTemperature, float temperatureCooling);
    ~SimulatedAnnealingAlgorithm();
    Solution* run(Solution* initialSolution, int& noEvaluations, int& noSteps) override;
};
