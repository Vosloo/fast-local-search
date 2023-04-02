#include <random>
#include <set>

#include "Node.hpp"
#include "Solution.hpp"

int getRandom(int upperLimit)
{
    return rand() % upperLimit;
}

int* getRandomPermutation(int size)
{
    int* replaceInds = new int[size];
    for (int i = 0; i < size; i++) {
        replaceInds[i] = i;
    }

    int replaceFromInd = 0;
    int replaceToInd = 0;
    int temp = 0;
    for (replaceFromInd = 0; replaceFromInd < size - 2; replaceFromInd++) {
        replaceToInd = replaceFromInd + getRandom(size - replaceFromInd);
        if (replaceFromInd == replaceToInd) {
            continue;
        }
        std::swap(replaceInds[replaceFromInd], replaceInds[replaceToInd]);
    }

    return replaceInds;
}

void getTwoRandomIndicies(int n, int* result)
{
    result[0] = getRandom(n);
    result[1] = getRandom(n - 1);
    if (result[0] == result[1]) {
        result[1] = n - 1;
    }
}
