#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class SteepestAlgorithm : public AbstractAlgorithm {
private:
    int instanceSize;
    int neighborhoodSize;
    int** neigbourhood;
public:
    SteepestAlgorithm(int instanceSize);
    ~SteepestAlgorithm();
    Solution* run(Solution* initialSolution) override;
};
