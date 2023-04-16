#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"

class TabuSearchAlgorithm : public AbstractAlgorithm {
private:
    int instanceSize;
    int neighborhoodSize;
    int** neigbourhood;
    int tabuTenure;
    int maxIterWoImprov;
    void updateTabuList(std::set<std::tuple<int, int>>& tabuList, std::tuple<int, int>& edge);
    bool isTabu(std::set<std::tuple<int, int>>& tabuList, std::tuple<int, int>& edge);
public:
    TabuSearchAlgorithm(int instanceSize);
    ~TabuSearchAlgorithm();
    Solution* run(Solution* initialSolution, int& noEvaluations, int& noSteps) override;
};
