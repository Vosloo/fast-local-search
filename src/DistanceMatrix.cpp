#include "DistanceMatrix.hpp"
#include "Instance.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <set>

DistanceMatrix::DistanceMatrix(Instance* instance)
{
    this->instance = instance;
    this->calculateDistances();
};

DistanceMatrix::~DistanceMatrix()
{
    for (int i = 0; i < this->instance->getSize(); i++) {
        delete[] this->distances[i];
    }
    delete[] this->distances;
};

float DistanceMatrix::getDistance(int node1, int node2)
{
    return this->distances[node1][node2];
};

int DistanceMatrix::getClosestNode(int node, std::set <int> visited)
{
    int closestNode = -1;
    float minDistance = std::numeric_limits<float>::max();
    for (int i = 0; i < this->instance->getSize(); i++) {
        float distance = this->getDistance(node, i);
        if ((distance < minDistance) && (visited.find(i) == visited.end())){
            minDistance = distance;
            closestNode = i;
        }
    }

    return closestNode;
};

Instance* DistanceMatrix::getInstance()
{
    return this->instance;
};

float DistanceMatrix::calculateDistance(int node1, int node2)
{
    Node* node1Ptr = this->instance->getNodes()[node1];
    Node* node2Ptr = this->instance->getNodes()[node2];
    return std::sqrt(std::pow(node1Ptr->getX() - node2Ptr->getX(), 2) + std::pow(node1Ptr->getY() - node2Ptr->getY(), 2));
};

void DistanceMatrix::calculateDistances()
{
    float** distanceMatrix = new float*[this->instance->getSize()];
    Node** nodes = this->instance->getNodes();
    for (int i = 0; i < this->instance->getSize(); i++) {
        distanceMatrix[i] = new float[this->instance->getSize()];
        for (int j = 0; j < this->instance->getSize(); j++) {
            if (i == j) {
                distanceMatrix[i][j] = std::numeric_limits<float>::max();
            } else {
                distanceMatrix[i][j] = this->calculateDistance(i, j);
            }
        }
    }

    this->distances = distanceMatrix;
};
