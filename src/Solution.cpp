#include "Solution.hpp"
#include "DistanceMatrix.hpp"
#include "Node.hpp"

Solution::Solution(Node** nodes, int size, DistanceMatrix& distanceMatrix)
{
    this->currentNodes = nodes;
    this->size = size;
    this->distanceMatrix = &distanceMatrix;
    this->calculateScore();
}

Solution::~Solution()
{
    delete[] this->currentNodes;
}

void Solution::calculateScore()
{
    this->score = 0.0f;
    currentNodes = getCurrentNodes();
    for (int i = 0; i < size - 1; i++) {
        this->score += distanceMatrix->getDistance(*currentNodes[i], *currentNodes[i + 1]);
    }
    this->score += distanceMatrix->getDistance(*currentNodes[0], *currentNodes[size - 1]);
}

float Solution::getScore()
{
    return this->score;
}

int Solution::getSize()
{
    return this->size;
}

Node** Solution::getCurrentNodes()
{
    return this->currentNodes;
}

DistanceMatrix* Solution::getDistanceMatrix()
{
    return this->distanceMatrix;
}
