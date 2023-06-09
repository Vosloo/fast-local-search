#include "Solution.hpp"
#include "DistanceMatrix.hpp"
#include "Node.hpp"

Solution::Solution(int* nodes, int size, DistanceMatrix& distanceMatrix, bool freeOnDelete)
{
    this->size = size;
    this->currentNodes = nodes;
    this->distanceMatrix = &distanceMatrix;
    this->freeOnDelete = freeOnDelete;
    this->calculateScore();
}

Solution::Solution(Solution& solution)
{
    this->size = solution.getSize();
    this->currentNodes = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        this->currentNodes[i] = solution.getCurrentNodes()[i];
    }
    this->freeOnDelete = true;
    this->distanceMatrix = solution.getDistanceMatrix();
    this->score = solution.getScore();
}

Solution::~Solution()
{
    if (this->freeOnDelete) {
        delete[] this->currentNodes;
    }
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

int* Solution::getCopyCurrentNodes()
{
    int* copy = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        copy[i] = this->currentNodes[i];
    }
    return copy;
}

DistanceMatrix* Solution::getDistanceMatrix()
{
    return this->distanceMatrix;
}

bool Solution::operator<(const Solution& solution) const
{
    return this->score < solution.score;
}

bool Solution::operator>(const Solution& solution) const
{
    return this->score > solution.score;
}

bool Solution::operator==(const Solution& solution) const
{
    return this->score == solution.score;
}
