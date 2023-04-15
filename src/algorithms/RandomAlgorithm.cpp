#include <chrono>
#include <iostream>

#include "Solution.hpp"
#include "algorithms/RandomAlgorithm.hpp"
#include "utils.hpp"

RandomAlgorithm::RandomAlgorithm(float maxRuntime)
{
    this->maxRuntime = maxRuntime;
    setAlgorithmName("RandomAlgorithm");
}

Solution* RandomAlgorithm::run(Solution* initialSolution, int& noEvaluations, int& noSteps)
{
    Solution* bestSolution = new Solution(*initialSolution);
    Solution* currentSolution;
    
    int* randomPermutation = new int[initialSolution->getSize()];
    for (int i = 0; i < initialSolution->getSize(); i++) {
        randomPermutation[i] = i;
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() < maxRuntime) {
        getRandomPermutation(randomPermutation, initialSolution->getSize());
        currentSolution = new Solution(
            randomPermutation,
            initialSolution->getSize(),
            *initialSolution->getDistanceMatrix());
        noEvaluations++;

        if (*currentSolution < *bestSolution) {
            delete bestSolution;
            noSteps++;
            bestSolution = currentSolution;
        } else {
            delete currentSolution;
        }
    }

    delete[] randomPermutation;

    return bestSolution;
}
