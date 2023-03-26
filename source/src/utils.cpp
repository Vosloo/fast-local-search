#include <random>

#include "Node.hpp"
#include "Solution.hpp"


int getRandom(int upperLimit) {
    return rand() % upperLimit;
}

Solution getRandomPermutation(Solution& solution)
{
    Node** nodes = solution.getCurrentNodes();

    // Copy nodes
    Node** newNodes = new Node*[solution.getSize()];

    size_t replaceFromInd = 0;
    size_t replaceToInd = 0;
    for (replaceFromInd = 0; replaceFromInd < solution.getSize() - 2; replaceFromInd++) {
        replaceToInd = replaceFromInd + getRandom(solution.getSize() - replaceFromInd);
        // TODO: Fix
    }

    return Solution(newNodes, solution.getSize(), *solution.getDistanceMatrix());
}

