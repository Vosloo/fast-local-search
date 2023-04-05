#include <iostream>
#include <random>
#include <set>

#include "DistanceMatrix.hpp"
#include "FileReader.hpp"
#include "Instance.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "algorithms/GreedyAlgorithm.hpp"
#include "algorithms/HeuristicAlgorithm.hpp"
#include "algorithms/RandomAlgorithm.hpp"
#include "algorithms/RandomWalkAlgorithm.hpp"
#include "algorithms/SteepestAlgorithm.hpp"
#include "delta/NodeDelta.hpp"
#include "utils.hpp"

void print_stats(Solution& solution)
{
    std::cout << "---------------------" << std::endl;
    std::cout << "Score: " << solution.getScore() << std::endl;
    for (int i = 0; i < solution.getSize(); i++) {
        std::cout << solution.getCurrentNodes()[i];
        if (i != solution.getSize() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n---------------------" << std::endl;
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    std::string filename = "kroD100.tsp";
    FileReader fileReader;

    Instance instance = fileReader.loadTspInstance(filename);
    std::cout << "Number of nodes: " << instance.getSize() << std::endl;

    DistanceMatrix distanceMatrix(&instance);

    Solution* solution1 = new Solution(getRandomPermutation(instance.getSize()), instance.getSize(), distanceMatrix);

    print_stats(*solution1);

    // RandomAlgorithm algorithm;
    // RandomWalkAlgorithm algorithm;
    // HeuristicAlgorithm algorithm;
    // GreedyAlgorithm algorithm(solution1->getSize());
    SteepestAlgorithm algorithm(solution1->getSize());

    Solution* solution2 = algorithm.run(solution1);

    print_stats(*solution2);

    delete solution1;
    delete solution2;

    return 0;
}
