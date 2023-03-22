#include <iostream>
#include "FileReader.hpp"
#include "Node.hpp"
#include "DistanceMatrix.hpp"

int main(int, char**) {
    std::string filename = "/home/marek/Projects/C++/Biol_evo/project_1/data/kroA100.tsp";
    FileReader fileReader;

    std::vector<Node> nodes = fileReader.loadTspInstance(filename);
    std::cout << "Number of nodes: " << nodes.size() << std::endl;
    for (Node node : nodes) {
        std::cout << "Node: " << node.getX() << " " << node.getY() << std::endl;
    }

    DistanceMatrix distanceMatrix(nodes);
    std::cout << "Distance between nodes 1 and 2: " << distanceMatrix.getDistance(nodes[0], nodes[1]) << std::endl;

    return 0;
}