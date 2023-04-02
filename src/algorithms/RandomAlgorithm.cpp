#include <iostream>

#include "Solution.hpp"
#include "algorithms/RandomAlgorithm.hpp"
#include "utils.hpp"

Solution* RandomAlgorithm::run(Solution* initialSolution)
{
    Solution* bestSolution = initialSolution;

    int i = 0;
    while (i < 100) // Zmienić na avg z G albo S
    {
        Solution* currentSolution = new Solution(
            getRandomPermutation(bestSolution->getSize()),
            bestSolution->getSize(),
            *bestSolution->getDistanceMatrix()
        );

        if (currentSolution->getScore() < bestSolution->getScore()) {
            delete bestSolution;
            bestSolution = currentSolution;
        } else {
            delete currentSolution;
        }

        i++;
    }

    return bestSolution;
}
