#include "delta/EdgeDelta.hpp"
#include "Solution.hpp"

EdgeDelta::EdgeDelta(int node1ExternalInd, int node2InternalInd, Solution* solution)
{
    this->node1ExternalInd = node1ExternalInd;
    this->node2InternalInd = node2InternalInd;
    this->solution = solution;
    this->delta = calculateDelta();
}

float EdgeDelta::calculateDelta()
{
    // 1 2 3 4 5 6 7 8
    // (2, 3) with (6, 7)
    // (ext1, int1) with (int2, ext2)
    //
    // 1 2 6 5 4 3 7 8
    // (2, 6) with (3, 7)
    // (ext1, int2) with (int1, ext2)

    int node1InternalInd = node1ExternalInd + 1;
    int node2ExternalInd = node2InternalInd + 1;

    DistanceMatrix* distanceMatrix = solution->getDistanceMatrix();

    float oldDistance1 = distanceMatrix->getDistance(solution->getNode(node1ExternalInd), solution->getNode(node1InternalInd));
    float oldDistance2 = distanceMatrix->getDistance(solution->getNode(node2InternalInd), solution->getNode(node2ExternalInd));

    float newDistance1 = distanceMatrix->getDistance(solution->getNode(node1ExternalInd), solution->getNode(node2InternalInd));
    float newDistance2 = distanceMatrix->getDistance(solution->getNode(node1InternalInd), solution->getNode(node2ExternalInd));

    return (oldDistance1 + oldDistance2) - (newDistance1 + newDistance2); // The bigger the better
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
    // Tricky case
    // 1 2 3 4 5 6 7
    // (2, 3) with (7, 1)
    // 
    // 1 2 7 6 5 4 3
    // ------
    // 
    // Normal case
    // 0 1 2 3 4 5 6
    // (1, 2) with (4, 5)
    // 
    // 0 1 4 3 2 5 6

    // 0 1 2 3 4 5 6
    // (1, 2) with (5, 6)
    //
    // 0 1 5 4 3 2 6

    int node1InternalInd = node1ExternalInd + 1;
    int node2ExternalInd = node2InternalInd + 1;

    if (node2ExternalInd == solution->getSize()) {
        // Case when second edge loops back to the first node
    } else {
        int* currentNodes = solution->getCurrentNodes();

        int midPoint;
        if ((node2ExternalInd - node1InternalInd) % 2 == 0) {
            midPoint = node1InternalInd + (node2ExternalInd - node1InternalInd) / 2;
        } else {
            midPoint = node1InternalInd + (node2ExternalInd - node1InternalInd) / 2 + 1;
        }

        for (int i = node1InternalInd; i < midPoint; i++) {
            std::swap(currentNodes[i], currentNodes[node2InternalInd - (i - node1InternalInd)]);
        }
        // TODO: Fix this
    }
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
