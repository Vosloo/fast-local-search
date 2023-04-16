#pragma once

#include "Solution.hpp"
#include <tuple>

class EdgeDelta {
private:
    int node1ExternalInd;
    int node2InternalInd;
    Solution* solution;
    float delta;
    float calculateDelta();

public:
    EdgeDelta(int node1ExternalInd, int node2InternalInd, Solution* solution);
    EdgeDelta(std::tuple<int, int>& edge, Solution* solution);
    int getNode1ExternalInd();
    int getNode2InternalInd();
    float getDelta();
    void apply();
    bool operator>(const EdgeDelta& edgeDelta) const;
    bool operator<(const EdgeDelta& edgeDelta) const;
    bool operator==(const EdgeDelta& edgeDelta) const;
};
