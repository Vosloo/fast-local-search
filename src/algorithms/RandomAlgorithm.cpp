#include <iostream>

#include "algorithms/RandomAlgorithm.hpp"
#include "Solution.hpp"
#include "utils.hpp"


Solution RandomAlgorithm::run(Solution &initialSolution)
{
    return getRandomPermutation(initialSolution);
}
