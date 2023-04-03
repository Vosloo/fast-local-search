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

    Solution* solution2 = new Solution(
        getRandomPermutation(instance.getSize()),
        instance.getSize(),
        distanceMatrix
    );

    // int* solutionNodes2 = solution2->getCurrentNodes();

    // int index1 = 0;
    // int index2 = 25;

    // std::cout << "Manual distance for " << index1 << " and " << index2 << ":" << std::endl;
    // float old1 = distanceMatrix.getDistance(solution2->getNode(index1 - 1), solution2->getNode(index1)) + distanceMatrix.getDistance(solution2->getNode(index1), solution2->getNode(index1 + 1));
    // float old2 = distanceMatrix.getDistance(solution2->getNode(index2 - 1), solution2->getNode(index2)) + distanceMatrix.getDistance(solution2->getNode(index2), solution2->getNode(index2 + 1));

    // float new1 = distanceMatrix.getDistance(solution2->getNode(index2 - 1), solution2->getNode(index1)) + distanceMatrix.getDistance(solution2->getNode(index1), solution2->getNode(index2 + 1));
    // float new2 = distanceMatrix.getDistance(solution2->getNode(index1 - 1), solution2->getNode(index2)) + distanceMatrix.getDistance(solution2->getNode(index2), solution2->getNode(index1 + 1));

    // std::cout << old1 + old2 << " -> " << new1 + new2 << " (" << old1 + old2 - new1 - new2 << ")" << std::endl;

    // NodeDelta nodeDelta(index1, index2, solution2);
    // std::cout << "Distance between " << index1 << " and " << index2 << ": " << nodeDelta.getDelta() << std::endl;
    // NodeDelta nodeDelta2(index1 + 1, index2, solution2);
    // std::cout << "Distance between " << index1 + 1 << " and " << index2 << ": " << nodeDelta2.getDelta() << std::endl;

    // std::cout << "Is nodeDelta > nodeDelta2? " << (nodeDelta > nodeDelta2) << std::endl;
    // std::cout << "Is nodeDelta2 > nodeDelta? " << (nodeDelta2 > nodeDelta) << std::endl;
    // std::cout << "Is nodeDelta == nodeDelta2? " << (nodeDelta == nodeDelta2) << std::endl;

    // return 0;

    print_stats(*solution1);

    // RandomAlgorithm randomAlgorithm;
    RandomWalkAlgorithm randomAlgorithm;
    // HeuristicAlgorithm randomAlgorithm;
    // Solution* solution2 = randomAlgorithm.run(solution1);

    print_stats(*solution2);

    delete solution1;
    delete solution2;

    return 0;
}
