#include <iostream>
#include <random>

#include "DistanceMatrix.hpp"
#include "FileReader.hpp"
#include "Instance.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "algorithms/RandomAlgorithm.hpp"
#include "utils.hpp"

void print_stats(Solution& solution)
{
    std::cout << "---------------------" << std::endl;
    std::cout << "Score: " << solution.getScore() << std::endl;
    for (int i = 0; i < solution.getSize(); i++) {
        std::cout << solution.getCurrentNodes()[i]->getId();
        if (i != solution.getSize() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n---------------------" << std::endl;
}

int main(int, char**)
{
    srand(time(NULL));

    std::string filename = "kroA100.tsp";
    FileReader fileReader;

    Instance instance = fileReader.loadTspInstance(filename);
    std::cout << "Number of nodes: " << instance.getSize() << std::endl;
    Node** nodes = instance.getNodes();
    for (int i = 0; i < instance.getSize(); i++) {
        std::cout << "Node " << nodes[i]->getId() << ": " << nodes[i]->getX() << ", " << nodes[i]->getY() << std::endl;
    }

    DistanceMatrix distanceMatrix(&instance);
    std::cout << "Distance between nodes 0 and 1: " << distanceMatrix.getDistance(*nodes[0], *nodes[1]) << std::endl;
    std::cout << "Distance between nodes 1 and 1: " << distanceMatrix.getDistance(*nodes[1], *nodes[1]) << std::endl;

    Node** solutionNodes = new Node*[instance.getSize()];
    for (int i = 0; i < instance.getSize(); i++) {
        solutionNodes[i] = nodes[i];
    }

    Solution solution1 = Solution(solutionNodes, instance.getSize(), distanceMatrix);

    print_stats(solution1);

    RandomAlgorithm randomAlgorithm;
    Solution solution2 = randomAlgorithm.run(solution1);

    print_stats(solution2);

    return 0;
}
