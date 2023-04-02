#pragma once

#include "DistanceMatrix.hpp"

class NodeDelta {
private:
    int node1;
    int node2;
    DistanceMatrix* distanceMatrix;
    float delta;
    float calculateDelta();

public:
    NodeDelta(int node1, int node2, DistanceMatrix* distanceMatrix);
    int getNode1();
    int getNode2();
    float getDelta();
};
