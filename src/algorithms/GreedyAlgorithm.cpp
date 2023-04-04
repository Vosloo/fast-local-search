#include "algorithms/GreedyAlgorithm.hpp"
#include "delta/EdgeDelta.hpp"

#include "Solution.hpp"
#include "utils.hpp"

GreedyAlgorithm::GreedyAlgorithm(int instanceSize)
{
    this->instanceSize = instanceSize;
    this->neigbourhoodSize = (instanceSize - 1) * (instanceSize - 2) / 2 - 1;
    this->neigbourhood = getNeighborhood(this->instanceSize);
}

GreedyAlgorithm::~GreedyAlgorithm()
{
    for (int i = 0; i < this->neigbourhoodSize; i++) {
        delete[] this->neigbourhood[i];
    }
    delete[] this->neigbourhood;
}

Solution* GreedyAlgorithm::run(Solution* initialSolution)
{
    Solution* currentSolution = new Solution(*initialSolution);

    int* random_permutation = getRandomPermutation(this->neigbourhoodSize);
    for (int i = 0; i < initialSolution->getSize(); i++) {
        EdgeDelta delta(
            this->neigbourhood[random_permutation[i]][0],
            this->neigbourhood[random_permutation[i]][1],
            currentSolution);

        if (delta.getDelta() > 0) {
            std::cout << "Iteration: " << i << std::endl;
            std::cout << "Found better solution with delta: " << delta.getDelta() << std::endl;
            delta.apply();
            break;
        }
    }

    return currentSolution;
}