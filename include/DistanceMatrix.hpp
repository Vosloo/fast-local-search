#pragma once

#include <iostream>
#include <set>

#include "Node.hpp"
#include "Instance.hpp"

class DistanceMatrix
{
private:
    Instance* instance;
    float** distances;
    void calculateDistances();
    float calculateDistance(int node1, int node2);

public:
    DistanceMatrix(Instance* instance);
    ~DistanceMatrix();
    float getDistance(int node1, int node2);
    int getClosestNode(int node, std::set <int> visited);
    Instance* getInstance();
};
