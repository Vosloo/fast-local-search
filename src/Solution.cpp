#include "Solution.hpp"
#include "DistanceMatrix.hpp"
#include "Node.hpp"

Solution::Solution(int* nodes, int size, DistanceMatrix& distanceMatrix)
{
    this->size = size;
    this->currentNodes = nodes;
    this->distanceMatrix = &distanceMatrix;
    this->calculateScore();
}

Solution::Solution(Solution& solution)
{
    this->size = solution.getSize();
    this->currentNodes = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        this->currentNodes[i] = solution.getCurrentNodes()[i];
    }
    this->distanceMatrix = solution.getDistanceMatrix();
    this->score = solution.getScore();
}

Solution::~Solution()
{
    std::cout << "Deleting solution" << std::endl;
    delete[] this->currentNodes;
}

void Solution::calculateScore()
{
    this->score = 0.0f;
    for (int i = 0; i < size - 1; i++) {
        this->score += this->distanceMatrix->getDistance(currentNodes[i], currentNodes[i + 1]);
    }
    this->score += this->distanceMatrix->getDistance(currentNodes[size - 1], currentNodes[0]);
}

void Solution::setScore(float score)
{
    this->score = score;
}

float Solution::getScore()
{
    return this->score;
}

int Solution::getNode(int index)
{
    if (index == -1) {
        return this->currentNodes[this->size - 1];
    } else if (index == this->size) {
        return this->currentNodes[0];
    } else if (-1 < index && index < this->size) {
        return this->currentNodes[index];
    } else {
        throw std::invalid_argument("Index out of bounds");
    }
}

int Solution::getSize()
{
    return this->size;
}

int* Solution::getCurrentNodes()
{
    return this->currentNodes;
}

DistanceMatrix* Solution::getDistanceMatrix()
{
    return this->distanceMatrix;
}
