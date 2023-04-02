#include <iostream>
#include <random>
#include <set>

#include "DistanceMatrix.hpp"
#include "FileReader.hpp"
#include "Instance.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "algorithms/RandomAlgorithm.hpp"
#include "algorithms/RandomWalkAlgorithm.hpp"
#include "algorithms/HeuristicAlgorithm.hpp"
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

    std::string filename = "kroA100.tsp";
    FileReader fileReader;

    Instance instance = fileReader.loadTspInstance(filename);
    std::cout << "Number of nodes: " << instance.getSize() << std::endl;

    DistanceMatrix distanceMatrix(&instance);

    int* solutionNodes = new int[instance.getSize()];
    for (int i = 0; i < instance.getSize(); i++) {
        solutionNodes[i] = i;
    }

    Solution* solution1 = new Solution(solutionNodes, instance.getSize(), distanceMatrix);

    std::cout << "Manual distance for 12 and 25: " << std::endl;
    int old1 = distanceMatrix.getDistance(11, 12) + distanceMatrix.getDistance(12, 13);
    int old2 = distanceMatrix.getDistance(24, 25) + distanceMatrix.getDistance(25, 26);

    int new1 = distanceMatrix.getDistance(24, 12) + distanceMatrix.getDistance(12, 26);
    int new2 = distanceMatrix.getDistance(11, 25) + distanceMatrix.getDistance(25, 13);

    std::cout << old1 + old2 << " -> " << new1 + new2 << " (" << old1 + old2 - new1 - new2 << ")" << std::endl;

    NodeDelta nodeDelta(25, 12, &distanceMatrix);
    std::cout << "Distance between 25 and 12: " << nodeDelta.getDelta() << std::endl;
    return 0;

    print_stats(*solution1);

    // RandomAlgorithm randomAlgorithm;
    // RandomWalkAlgorithm randomAlgorithm;
    HeuristicAlgorithm randomAlgorithm;
    Solution* solution2 = randomAlgorithm.run(solution1);

    print_stats(*solution2);

    delete solution2;

    return 0;
}
