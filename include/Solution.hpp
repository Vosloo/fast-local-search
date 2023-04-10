#pragma once

#include "Node.hpp"
#include "DistanceMatrix.hpp"


class Solution
{
private:
    int* currentNodes;
    DistanceMatrix* distanceMatrix;
    int size;
    float score;
public:
    Solution(int* nodes, int size, DistanceMatrix& distanceMatrix);
    Solution(Solution& solution);
    ~Solution();
    DistanceMatrix* getDistanceMatrix();
    int* getCurrentNodes();
    void calculateScore();
    void setScore(float score);
    float getScore();
    int getNode(int index);
    int getSize();
    bool operator<(const Solution& solution) const;
    bool operator>(const Solution& solution) const;
    bool operator==(const Solution& solution) const;
};