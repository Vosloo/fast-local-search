#include <iostream>

#include "DistanceMatrix.hpp"
#include "FileReader.hpp"
#include "Instance.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "utils.hpp"


int main(int, char**)
{
    std::string filename = "/home/marek/Projects/C++/Biol_evo/project_1/data/kroA100.tsp";
    FileReader fileReader;

    Instance instance = fileReader.loadTspInstance(filename);
    std::cout << "Number of nodes: " << instance.getSize() << std::endl;
    Node** nodes = instance.getNodes();
    for (int i = 0; i < instance.getSize(); i++) {
        std::cout << "Node " << i << ": " << nodes[i]->getX() << ", " << nodes[i]->getY() << std::endl;
    }

    DistanceMatrix distanceMatrix(&instance);
    std::cout << "Distance between nodes 0 and 1: " << distanceMatrix.getDistance(*nodes[0], *nodes[1]) << std::endl;
    std::cout << "Distance between nodes 1 and 1: " << distanceMatrix.getDistance(*nodes[1], *nodes[1]) << std::endl;

    Solution solution1 = Solution(nodes, instance.getSize(), distanceMatrix);
    std::cout << "Score of solution1: " << solution1.getScore() << std::endl;
    for (int i = 0; i < solution1.getSize(); i++) {
        std::cout << nodes[i]->getId();
        if (i != solution1.getSize() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    Solution solution2 = getRandomPermutation(solution1);
    std::cout << "Score of solution2: " << solution2.getScore() << std::endl;
    for (int i = 0; i < solution2.getSize(); i++) {
        std::cout << nodes[i]->getId();
        if (i != solution1.getSize() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    
    std::cout << "Score of solution1: " << solution1.getScore() << std::endl;
    for (int i = 0; i < solution1.getSize(); i++) {
        std::cout << nodes[i]->getId();
        if (i != solution1.getSize() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    return 0;
}