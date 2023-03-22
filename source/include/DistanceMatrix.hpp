#pragma once

#include <vector>
#include <iostream>

#include "Node.hpp"

class DistanceMatrix
{
private:
    std::vector<Node> nodes;
    std::vector<std::vector<float>> distances;
    void calculateDistances();

public:
    DistanceMatrix(std::vector<Node> &nodes);
    float getDistance(Node &node1, Node &node2);
};
