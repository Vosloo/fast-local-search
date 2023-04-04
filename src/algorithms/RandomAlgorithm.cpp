#include <iostream>

#include "Solution.hpp"
#include "algorithms/RandomAlgorithm.hpp"
#include "utils.hpp"

Solution* RandomAlgorithm::run(Solution* initialSolution)
{
    Solution* bestSolution = nullptr;

    int i = 0;
    while (i < 100) // Zmienić na avg z G albo S
    {
        Solution* currentSolution = new Solution(
            getRandomPermutation(initialSolution->getSize()),
            initialSolution->getSize(),
            *initialSolution->getDistanceMatrix()
        );

        if (bestSolution == nullptr) {
            bestSolution = currentSolution;
        } else if (currentSolution->getScore() < bestSolution->getScore()) {
            delete bestSolution;
            bestSolution = currentSolution;
        } else {
            delete currentSolution;
        }

        i++;
    }

    return bestSolution;
}
