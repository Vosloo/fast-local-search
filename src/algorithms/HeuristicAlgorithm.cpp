#include <set>

#include "DistanceMatrix.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "utils.hpp"
#include "algorithms/HeuristicAlgorithm.hpp"


Solution* HeuristicAlgorithm::run(Solution* initialSolution)
{
    int current_node = getRandom(initialSolution->getSize());
    std::set <int> visited = {current_node};

    int* heuristic_solution = new int[initialSolution->getSize()];
    heuristic_solution[0] = current_node;

    int closest_node = -1;
    for (int i = 1; i < initialSolution->getSize(); i++)
    {
        closest_node = initialSolution->getDistanceMatrix()->getClosestNode(current_node, visited);
        
        heuristic_solution[i] = closest_node;
        visited.insert(closest_node);
        
        current_node = closest_node;
    }

    Solution* solution = new Solution(heuristic_solution, initialSolution->getSize(), *initialSolution->getDistanceMatrix());

    return solution;
};
