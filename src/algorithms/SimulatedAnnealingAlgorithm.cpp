#include "algorithms/SimulatedAnnealingAlgorithm.hpp"
#include "Solution.hpp"
#include "delta/EdgeDelta.hpp"
#include "utils.hpp"
#include <random>
#include <cmath>

SimulatedAnnealingAlgorithm::SimulatedAnnealingAlgorithm(int instanceSize, float temperature_cooling)
{
    this->instanceSize = instanceSize;
    this->temperature_cooling = temperature_cooling;
    this->neighborhoodSize = (instanceSize - 1) * (instanceSize - 2) / 2 - 1;
    this->neigbourhood = getNeighborhood(this->instanceSize);
    setAlgorithmName("SimulatedAnnealing");
}

SimulatedAnnealingAlgorithm::~SimulatedAnnealingAlgorithm()
{
    for (int i = 0; i < this->neighborhoodSize; i++) {
        delete[] this->neigbourhood[i];
    }
    delete[] this->neigbourhood;
}

Solution* SimulatedAnnealingAlgorithm::run(Solution* initialSolution, int& noEvaluations, int& noSteps)
{
    Solution* currentSolution = new Solution(*initialSolution);
    float T = currentSolution->getScore() * 10;
    float T_alpha = this->temperature_cooling;

    int* randomPermutation = new int[this->neighborhoodSize];
    for (int i = 0; i < this->neighborhoodSize; i++) {
        randomPermutation[i] = i;
    }

    bool foundBetterSolution;
    while (true) {
        foundBetterSolution = false;
        getRandomPermutation(randomPermutation, this->neighborhoodSize);
        for (int i = 0; i < this->neighborhoodSize; i++) {
            EdgeDelta delta(
                this->neigbourhood[randomPermutation[i]][0],
                this->neigbourhood[randomPermutation[i]][1],
                currentSolution);
            noEvaluations++;

            if (delta.getDelta() > 0) {
                delta.apply();
                noSteps++;
                foundBetterSolution = true;
                break;
            } else if (exp(delta.getDelta()/T) > rand()){
                //TODO temperatura chuja
                delta.apply();
                noSteps++;
                foundBetterSolution = true;
                T *= T_alpha;
                break;
            }
        }


        if (!foundBetterSolution) {
            break;
        }
    }

    delete[] randomPermutation;

    return currentSolution;
}