#include "algorithms/SteepestAlgorithm.hpp"
#include "Solution.hpp"
#include "delta/EdgeDelta.hpp"
#include "utils.hpp"

SteepestAlgorithm::SteepestAlgorithm(int instanceSize)
{
    this->instanceSize = instanceSize;
    this->neighborhoodSize = (instanceSize - 1) * (instanceSize - 2) / 2 - 1;
    this->neigbourhood = getNeighborhood(this->instanceSize);
    setAlgorithmName("SteepestAlgorithm");
}

SteepestAlgorithm::~SteepestAlgorithm()
{
    for (int i = 0; i < this->neighborhoodSize; i++) {
        delete[] this->neigbourhood[i];
    }
    delete[] this->neigbourhood;
}

Solution* SteepestAlgorithm::run(Solution* initialSolution, int& noEvaluations, int& noSteps)
{
    Solution* currentSolution = new Solution(*initialSolution);
    EdgeDelta* bestDelta;
    bool foundBetterSolution;

    while (true) {
        bestDelta = nullptr;
        for (int i = 0; i < this->neighborhoodSize; i++) {
            EdgeDelta* delta = new EdgeDelta(
                this->neigbourhood[i][0],
                this->neigbourhood[i][1],
                currentSolution);
            noEvaluations++;

            if (delta->getDelta() > 0 && (bestDelta == nullptr || *delta > *bestDelta)) {
                delete bestDelta;
                bestDelta = delta;
            } else {
                delete delta;
            }
        }

        if (bestDelta == nullptr) {
            break;
        }
        noSteps++;
        bestDelta->apply();
        delete bestDelta;
    }

    return currentSolution;
}