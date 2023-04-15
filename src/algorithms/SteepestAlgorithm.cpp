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
    EdgeDelta* currentDelta;

    while (true) {
        bestDelta = nullptr;
        for (int i = 0; i < this->neighborhoodSize; i++) {
            currentDelta = new EdgeDelta(
                this->neigbourhood[i][0],
                this->neigbourhood[i][1],
                currentSolution);
            noEvaluations++;

            if (currentDelta->getDelta() > 0 && (bestDelta == nullptr || *currentDelta > *bestDelta)) {
                delete bestDelta;
                bestDelta = currentDelta;
            } else {
                delete currentDelta;
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