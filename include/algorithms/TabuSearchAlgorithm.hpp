#pragma once

#include "AbstractAlgorithm.hpp"
#include "Solution.hpp"
#include "delta/EdgeDelta.hpp"
#include <vector>

class TabuSearchAlgorithm : public AbstractAlgorithm {
private:
    int instanceSize;
    int neighborhoodSize;
    int candidateListSize;
    int** neigbourhood;
    int tabuTenure;
    int maxIterWoImprov;
    void updateTabuList(std::set<std::tuple<int, int>>& tabuList, std::tuple<int, int>& edge);
    bool isTabu(std::set<std::tuple<int, int>>& tabuList, std::tuple<int, int>& edge);
    bool fulfillsAspiration();
    void updateEliteCandidates(std::vector<EdgeDelta*> eliteCandidates, Solution* currentSolution);

public:
    TabuSearchAlgorithm(int instanceSize);
    ~TabuSearchAlgorithm();
    Solution* run(Solution* initialSolution, int& noEvaluations, int& noSteps) override;
};
