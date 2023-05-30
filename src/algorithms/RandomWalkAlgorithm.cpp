#include <chrono>

#include "DistanceMatrix.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "algorithms/RandomWalkAlgorithm.hpp"
#include "delta/NodeDelta.hpp"
#include "delta/EdgeDelta.hpp"  
#include "utils.hpp"

RandomWalkAlgorithm::RandomWalkAlgorithm(float maxRuntime)
{
    this->maxRuntime = maxRuntime;
    setAlgorithmName("RandomWalkAlgorithm");
}

Solution* RandomWalkAlgorithm::run(Solution* initialSolution, int& noEvaluations, int& noSteps)
{
    Solution* bestSolution = new Solution(*initialSolution);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int instanceSize = bestSolution->getSize();
    int** neigbourhood = getNeighborhood(instanceSize);

    int neigbourhoodSize = (instanceSize - 1) * (instanceSize - 2) / 2 - 1;
    noEvaluations += neigbourhoodSize;
    int* randomPermutation = new int[neigbourhoodSize];
    for (int i = 0; i < neigbourhoodSize; i++) {
        randomPermutation[i] = i;
    }
    getRandomPermutation(randomPermutation, neigbourhoodSize);

    int counter = 0;
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() < maxRuntime) {
        EdgeDelta edgeDelta(
            neigbourhood[randomPermutation[counter]][0],
            neigbourhood[randomPermutation[counter]][1],
            bestSolution);

        edgeDelta.apply();
        noSteps++;

        if (counter == neigbourhoodSize - 1) {
            getRandomPermutation(randomPermutation, neigbourhoodSize);
            counter = 0;
        } else {
            counter++;
        }
    }

    for (int i = 0; i < neigbourhoodSize; i++) {
        delete[] neigbourhood[i];
    }
    delete[] neigbourhood;
    delete[] randomPermutation;

    return bestSolution;
};