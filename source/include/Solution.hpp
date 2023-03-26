#pragma once

#include "Node.hpp"
#include "DistanceMatrix.hpp"


class Solution
{
private:
    Node** currentNodes;
    DistanceMatrix* distanceMatrix;
    int size;
    float score;
    void calculateScore();
public:
    Solution(Node** nodes, int size, DistanceMatrix& distanceMatrix);
    Node** getCurrentNodes();
    DistanceMatrix* getDistanceMatrix();
    float getScore();
    int getSize();
};