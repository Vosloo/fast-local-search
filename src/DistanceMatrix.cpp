#include "DistanceMatrix.hpp"
#include "Instance.hpp"

#include <cmath>
#include <iostream>
#include <limits>

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

float DistanceMatrix::getDistance(Node& node1, Node& node2)
{
    return this->distances[node1.getId()][node2.getId()];
};

Node* DistanceMatrix::getClosestNode(Node& node)
{
    Node* closestNode = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    for (int i = 0; i < this->instance->getSize(); i++) {
        float distance = this->getDistance(node, *this->instance->getNodes()[i]);
        if (distance < minDistance) {
            minDistance = distance;
            closestNode = this->instance->getNodes()[i];
        }
    }

    return closestNode;
};

float DistanceMatrix::calculateDistance(Node& node1, Node& node2)
{
    return std::sqrt(std::pow(node1.getX() - node2.getX(), 2) + std::pow(node1.getY() - node2.getY(), 2));
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
                distanceMatrix[i][j] = this->calculateDistance(*nodes[i], *nodes[j]);
            }
        }
    }

    this->distances = distanceMatrix;
};
