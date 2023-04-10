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
    int* random_permutation;
    bool foundBetterSolution;

    while (true) {
        foundBetterSolution = false;
        random_permutation = getRandomPermutation(this->neigbourhoodSize);
        for (int i = 0; i < initialSolution->getSize(); i++) {
            EdgeDelta delta(
                this->neigbourhood[random_permutation[i]][0],
                this->neigbourhood[random_permutation[i]][1],
                currentSolution);
            noEvaluations++;

            if (delta.getDelta() > 0) {
                delta.apply();
                noSteps++;
                foundBetterSolution = true;
                break;
            }
        }

        delete[] random_permutation;

        if (!foundBetterSolution) {
            break;
        }
    }

    return currentSolution;
}