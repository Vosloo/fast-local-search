#include "algorithms/GreedyAlgorithm.hpp"

#include "Solution.hpp"

Solution GreedyAlgorithm::run(Solution& initialSolution)
{
    Solution bestSolution = initialSolution;
    return bestSolution;
}

// 1 2 3 4 5 6 7 8
// 1 -> 2 with 5 -> 6
// 1 5 4 3 2 6 7 8

// 1 2 3 4 5 6 7 8
// 5 -> 6 with 1 -> 2
// 6 2 3 4 5 1 8 7