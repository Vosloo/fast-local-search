#include <iostream>

#include "Solution.hpp"
#include "algorithms/RandomAlgorithm.hpp"
#include "utils.hpp"

Solution RandomAlgorithm::run(Solution& initialSolution)
{
    Solution bestSolution = initialSolution;

    int i = 0;
    while (i < 100) // Zmienić na avg z G albo S
    {
        Solution currentSolution = getRandomPermutation(bestSolution);
        if (currentSolution.getScore() < bestSolution.getScore()) {
            bestSolution = currentSolution;
        }
        i++;
    }
    
    return bestSolution;
}
