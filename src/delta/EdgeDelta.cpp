#include "delta/EdgeDelta.hpp"
#include "Solution.hpp"
#include <iostream>

EdgeDelta::EdgeDelta(int node1ExternalInd, int node2InternalInd, Solution* solution)
{
    this->node1ExternalInd = node1ExternalInd;
    this->node2InternalInd = node2InternalInd;
    this->solution = solution;
    this->delta = calculateDelta();
}

EdgeDelta::EdgeDelta(std::tuple<int, int>& edge, Solution* solution)
{
    this->node1ExternalInd = std::get<0>(edge);
    this->node2InternalInd = std::get<1>(edge);
    this->solution = solution;
    this->delta = calculateDelta();
}

float EdgeDelta::calculateDelta()
{
    int node1InternalInd = node1ExternalInd + 1;
    int node2ExternalInd = node2InternalInd + 1;

    DistanceMatrix* distanceMatrix = solution->getDistanceMatrix();

    float oldDistance1 = distanceMatrix->getDistance(solution->getNode(node1ExternalInd), solution->getNode(node1InternalInd));
    float oldDistance2 = distanceMatrix->getDistance(solution->getNode(node2InternalInd), solution->getNode(node2ExternalInd));

    float newDistance1 = distanceMatrix->getDistance(solution->getNode(node1ExternalInd), solution->getNode(node2InternalInd));
    float newDistance2 = distanceMatrix->getDistance(solution->getNode(node1InternalInd), solution->getNode(node2ExternalInd));

    return (oldDistance1 + oldDistance2) - (newDistance1 + newDistance2); // The bigger the better
}

std::tuple<int, int> EdgeDelta::getEdge()
{
    return std::make_tuple(node1ExternalInd, node2InternalInd);
}

int EdgeDelta::getNode1ExternalInd()
{
    return node1ExternalInd;
}

int EdgeDelta::getNode2InternalInd()
{
    return node2InternalInd;
}

float EdgeDelta::getDelta()
{
    return delta;
}

void EdgeDelta::apply()
{
    int* nodes = solution->getCurrentNodes();

    int node1InternalInd = node1ExternalInd + 1;
    int middlePoint = node1ExternalInd + (node2InternalInd - node1ExternalInd) / 2 + 1;

    for (int i = node1InternalInd; i < middlePoint; i++) {
        std::swap(nodes[i], nodes[node2InternalInd - (i - node1InternalInd)]);
    }

    solution->setScore(solution->getScore() - delta);
}

void EdgeDelta::update(Solution* solution)
{
    this->solution = solution;
    this->delta = calculateDelta();
}

bool EdgeDelta::operator>(const EdgeDelta& edgeDelta) const
{
    return delta > edgeDelta.delta;
}

bool EdgeDelta::operator<(const EdgeDelta& edgeDelta) const
{
    return delta < edgeDelta.delta;
}

bool EdgeDelta::operator==(const EdgeDelta& edgeDelta) const
{
    return delta == edgeDelta.delta;
}
