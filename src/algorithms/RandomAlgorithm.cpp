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

Solution* RandomAlgorithm::run(Solution* initialSolution)
{
    Solution* bestSolution = nullptr;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() < maxRuntime) {
        Solution* currentSolution = new Solution(
            getRandomPermutation(initialSolution->getSize()),
            initialSolution->getSize(),
            *initialSolution->getDistanceMatrix());

        if (bestSolution == nullptr) {
            bestSolution = currentSolution;
        } else if (currentSolution < bestSolution) {
            delete bestSolution;
            bestSolution = currentSolution;
        } else {
            delete currentSolution;
        }
    }

    return bestSolution;
}
