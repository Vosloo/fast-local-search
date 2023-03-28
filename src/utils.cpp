#include <random>

#include "Node.hpp"
#include "Solution.hpp"

int getRandom(int upperLimit)
{
    return rand() % upperLimit;
}

Solution getRandomPermutation(Solution& solution)
{
    int* replaceInds = new int[solution.getSize()];
    for (int i = 0; i < solution.getSize(); i++) {
        replaceInds[i] = i;
    }

    Node** newNodes = new Node*[solution.getSize()];

    size_t replaceFromInd = 0;
    size_t replaceToInd = 0;
    int temp = 0;
    for (replaceFromInd = 0; replaceFromInd < solution.getSize() - 2; replaceFromInd++) {
        replaceToInd = replaceFromInd + getRandom(solution.getSize() - replaceFromInd);
        temp = replaceInds[replaceFromInd];
        replaceInds[replaceFromInd] = replaceInds[replaceToInd];
        replaceInds[replaceToInd] = temp;
    }

    Node** oldNodes = solution.getCurrentNodes();
    for (int i = 0; i < solution.getSize(); i++) {
        newNodes[i] = oldNodes[replaceInds[i]];
    }

    delete[] replaceInds;

    return Solution(newNodes, solution.getSize(), *solution.getDistanceMatrix());
}
