#include "algorithms/GreedyAlgorithm.hpp"
#include "delta/EdgeDelta.hpp"

#include "Solution.hpp"
#include "utils.hpp"

GreedyAlgorithm::GreedyAlgorithm(int instanceSize)
{
    this->instanceSize = instanceSize;
    this->neigbourhoodSize = (instanceSize - 1) * (instanceSize - 2) / 2 - 1;
    this->neigbourhood = getNeighborhood(this->instanceSize);
    setAlgorithmName("GreedyAlgorithm");
}

GreedyAlgorithm::~GreedyAlgorithm()
{
    for (int i = 0; i < this->neigbourhoodSize; i++) {
        delete[] this->neigbourhood[i];
    }
    delete[] this->neigbourhood;
}

Solution* GreedyAlgorithm::run(Solution* initialSolution, int& noEvaluations, int& noSteps)
{
    Solution* currentSolution = new Solution(*initialSolution);

    int* randomPermutation = new int[this->neigbourhoodSize];
    for (int i = 0; i < this->neigbourhoodSize; i++) {
        randomPermutation[i] = i;
    }

    bool foundBetterSolution;
    while (true) {
        foundBetterSolution = false;
        getRandomPermutation(randomPermutation, this->neigbourhoodSize);
        for (int i = 0; i < this->neigbourhoodSize; i++) {
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
            }
        }

        if (!foundBetterSolution) {
            break;
        }
    }

    delete[] randomPermutation;

    return currentSolution;
}