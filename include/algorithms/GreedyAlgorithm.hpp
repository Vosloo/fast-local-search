#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class GreedyAlgorithm : public AbstractAlgorithm {
private:
    int instanceSize;
    int* neigbourhood;
public:
    GreedyAlgorithm(int instanceSize);
    ~GreedyAlgorithm() override;
    Solution* run(Solution* initialSolution) override;
    int getNeighborhood(int n);
};
