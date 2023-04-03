#include "delta/NodeDelta.hpp"
#include "Solution.hpp"

NodeDelta::NodeDelta(int node1Ind, int node2Ind, Solution* solution)
{
    this->node1Ind = node1Ind;
    this->node2Ind = node2Ind;
    this->solution = solution;
    this->delta = calculateDelta();
}

int NodeDelta::getNode1()
{
    return node1Ind;
}

int NodeDelta::getNode2()
{
    return node2Ind;
}

float NodeDelta::getDelta()
{
    return delta;
}

float NodeDelta::calculateDelta()
{
    int node1PrevInd = node1Ind - 1;
    int node1NextInd = node1Ind + 1;

    int node2PrevInd = node2Ind - 1;
    int node2NextInd = node2Ind + 1;

    if (node1Ind == 0) {
        node1PrevInd = solution->getSize() - 1;
    }

    if (node1Ind == solution->getSize() - 1) {
        node1NextInd = 0;
    }

    if (node2Ind == 0) {
        node2PrevInd = solution->getSize() - 1;
    }

    if (node2Ind == solution->getSize() - 1) {
        node2NextInd = 0;
    }

    DistanceMatrix* distanceMatrix = solution->getDistanceMatrix();

    float oldDistance1 = distanceMatrix->getDistance(solution->getNode(node1PrevInd), solution->getNode(node1Ind)) + distanceMatrix->getDistance(solution->getNode(node1Ind), solution->getNode(node1NextInd));
    float oldDistance2 = distanceMatrix->getDistance(solution->getNode(node2PrevInd), solution->getNode(node2Ind)) + distanceMatrix->getDistance(solution->getNode(node2Ind), solution->getNode(node2NextInd));

    float newDistance1 = distanceMatrix->getDistance(solution->getNode(node2PrevInd), solution->getNode(node1Ind)) + distanceMatrix->getDistance(solution->getNode(node1Ind), solution->getNode(node2NextInd));
    float newDistance2 = distanceMatrix->getDistance(solution->getNode(node1PrevInd), solution->getNode(node2Ind)) + distanceMatrix->getDistance(solution->getNode(node2Ind), solution->getNode(node1NextInd));

    return (oldDistance1 + oldDistance2) - (newDistance1 + newDistance2); // The bigger the better
}

void NodeDelta::apply()
{
    int* currentNodes = new int[solution->getSize()];

    std::copy(
        solution->getCurrentNodes(),
        solution->getCurrentNodes() + solution->getSize(),
        currentNodes);
    std::swap(currentNodes[node1Ind], currentNodes[node2Ind]);

    solution = new Solution(currentNodes, solution->getSize(), *solution->getDistanceMatrix());
}

bool NodeDelta::operator>(const NodeDelta& nodeDelta) const
{
    return delta > nodeDelta.delta;
}

bool NodeDelta::operator<(const NodeDelta& nodeDelta) const
{
    return delta < nodeDelta.delta;
}

bool NodeDelta::operator==(const NodeDelta& nodeDelta) const
{
    return delta == nodeDelta.delta;
}
