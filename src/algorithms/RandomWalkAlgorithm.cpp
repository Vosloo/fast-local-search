#include "algorithms/RandomWalkAlgorithm.hpp"
#include "DistanceMatrix.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "utils.hpp"

Solution* RandomWalkAlgorithm::run(Solution* initialSolution)
{
    Solution* bestSolution = initialSolution;

    int i = 0;
    int indices[2];
    while (i < 100) {
        // Replace two random nodes
        getTwoRandomIndicies(bestSolution->getSize(), indices);

        int* currentNodes = new int[bestSolution->getSize()];

        std::copy(
            bestSolution->getCurrentNodes(),
            bestSolution->getCurrentNodes() + bestSolution->getSize(),
            currentNodes);
        std::swap(currentNodes[indices[0]], currentNodes[indices[1]]);

        Solution* currentSolution = new Solution(
            currentNodes,
            bestSolution->getSize(),
            *bestSolution->getDistanceMatrix());

        if (currentSolution->getScore() < bestSolution->getScore()) {
            delete bestSolution;
            bestSolution = currentSolution;
        } else {
            delete currentSolution;
        }

        i++;
    }

    return bestSolution;
};