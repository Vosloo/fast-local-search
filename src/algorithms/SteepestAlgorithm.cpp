#include "algorithms/SteepestAlgorithm.hpp"

#include "Solution.hpp"

SteepestAlgorithm::SteepestAlgorithm(int instanceSize)
{
    this->instanceSize = instanceSize;
    this->neigbourhood = getNeighborhood(this->instanceSize);
}

GreedyAlgorithm::~SteepestAlgorithm()
{
    for (int i = 0; i < this->instanceSize * (this->instanceSize - 2) / 2; i++) {
        delete[] this->neigbourhood[i];
    }
    delete[] this->neigbourhood;
}

Solution* SteepestAlgorithm::run(Solution* initialSolution)
{
    Solution* currentSolution = initialSolution;

    // wygenerować możliwe ruchy - gdzie delta większa od 0
    // shuffle ruchów
    // sprawdzić ruchy do pierwszego najbliższego jeśli istnieją

    int neighborhood = getNeighborhood(currentSolution);
    shuffle(neighborhood)
    for 

    return currentSolution;
}