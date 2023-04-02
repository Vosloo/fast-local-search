#include "delta/NodeDelta.hpp"

NodeDelta::NodeDelta(int node1, int node2, DistanceMatrix* distanceMatrix)
{
    this->node1 = node1;
    this->node2 = node2;
    this->distanceMatrix = distanceMatrix;
    this->delta = calculateDelta();
}

int NodeDelta::getNode1()
{
    return node1;
}

int NodeDelta::getNode2()
{
    return node2;
}

float NodeDelta::getDelta()
{
    return delta;
}

float NodeDelta::calculateDelta()
{
    int node1PreviousIndex = node1 - 1;
    int node1NextIndex = node1 + 1;

    int node2PreviousIndex = node2 - 1;
    int node2NextIndex = node2 + 1;

    if (node1 == 0) {
        node1PreviousIndex = distanceMatrix->getInstance()->getSize() - 1;
    }

    if (node1 == distanceMatrix->getInstance()->getSize() - 1) {
        node1NextIndex = 0;
    }

    if (node2 == 0) {
        node2PreviousIndex = distanceMatrix->getInstance()->getSize() - 1;
    }

    if (node2 == distanceMatrix->getInstance()->getSize() - 1) {
        node2NextIndex = 0;
    }

    float oldDistance1 = distanceMatrix->getDistance(node1PreviousIndex, node1) + distanceMatrix->getDistance(node1, node1NextIndex);
    float oldDistance2 = distanceMatrix->getDistance(node2PreviousIndex, node2) + distanceMatrix->getDistance(node2, node2NextIndex);

    float newDistance1 = distanceMatrix->getDistance(node2PreviousIndex, node1) + distanceMatrix->getDistance(node1, node2NextIndex);
    float newDistance2 = distanceMatrix->getDistance(node1PreviousIndex, node2) + distanceMatrix->getDistance(node2, node1NextIndex);

    return (oldDistance1 + oldDistance2) - (newDistance1 + newDistance2); // The more the better
}