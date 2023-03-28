#pragma once

#include <iostream>

#include "Node.hpp"
#include "Instance.hpp"

class DistanceMatrix
{
private:
    Instance* instance;
    float** distances;
    void calculateDistances();
    float calculateDistance(Node& node1, Node& node2);

public:
    DistanceMatrix(Instance* instance);
    ~DistanceMatrix();
    float getDistance(Node& node1, Node& node2);
    Node* getClosestNode(Node& node);
};
