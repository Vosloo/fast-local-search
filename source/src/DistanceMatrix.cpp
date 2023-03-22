#include "DistanceMatrix.hpp"

#include <cmath>
#include <iostream>
#include <vector>

DistanceMatrix::DistanceMatrix(std::vector<Node>& nodes)
{
    this->nodes = nodes;
    this->calculateDistances();
};

float DistanceMatrix::getDistance(Node& node1, Node& node2)
{
    return sqrt(pow(node1.getX() - node2.getX(), 2) + pow(node1.getY() - node2.getY(), 2));
};

void DistanceMatrix::calculateDistances()
{
    for (int i = 0; i < this->nodes.size(); i++)
    {
        std::vector<float> row;
        for (int j = 0; j < this->nodes.size(); j++)
        {
            row.push_back(this->getDistance(this->nodes[i], this->nodes[j]));
        }
        this->distances.push_back(row);
    }
};
