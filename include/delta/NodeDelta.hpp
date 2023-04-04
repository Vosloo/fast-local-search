#pragma once

#include "Solution.hpp"

class NodeDelta {
private:
    int node1Ind;
    int node2Ind;
    Solution* solution;
    float delta;
    float calculateDelta();

public:
    NodeDelta(int node1Ind, int node2Ind, Solution* solution);
    int getNode1();
    int getNode2();
    float getDelta();
    void apply();
    bool operator>(const NodeDelta& nodeDelta) const;
    bool operator<(const NodeDelta& nodeDelta) const;
    bool operator==(const NodeDelta& nodeDelta) const;
};
