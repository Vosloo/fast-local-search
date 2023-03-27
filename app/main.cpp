#include <iostream>
#include <random>

#include "DistanceMatrix.hpp"
#include "FileReader.hpp"
#include "Instance.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "utils.hpp"


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
    std::cout << "\nScore of solution1: " << solution1.getScore() << std::endl;
    for (int i = 0; i < solution1.getSize(); i++) {
        std::cout << solution1.getCurrentNodes()[i]->getId();
        if (i != solution1.getSize() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    Solution solution2 = getRandomPermutation(solution1);
    std::cout << "\nScore of solution2: " << solution2.getScore() << std::endl;
    for (int i = 0; i < solution2.getSize(); i++) {
        std::cout << solution2.getCurrentNodes()[i]->getId();
        if (i != solution2.getSize() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    
    return 0;
}