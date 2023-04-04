#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class SteepestAlgorithm : public AbstractAlgorithm {
private:
    int instanceSize;
    int* neigbourhood;
public:
    SteepestAlgorithm(int instanceSize);
    ~SteepestAlgorithm() override;
    Solution* run(Solution* initialSolution) override;
    int getNeighborhood(int n);
};
