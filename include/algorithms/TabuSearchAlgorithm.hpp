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
    void updateTabuList(std::tuple<int, int>* tabuList, std::tuple<int, int>& edge, int& tabuIndex);
    void moveTabuAtNewest(std::tuple<int, int>* tabuList, int& tabuIndex, int& toMoveInd);
    bool isTabu(std::tuple<int, int>* tabuList, std::tuple<int, int>& edge);
    bool fulfillsAspiration(EdgeDelta* delta);
    void updateEliteCandidates(std::vector<EdgeDelta*>&eliteCandidates, Solution* currentSolution, int& noEvaluations);

public:
    TabuSearchAlgorithm(int instanceSize);
    ~TabuSearchAlgorithm();
    Solution* run(Solution* initialSolution, int& noEvaluations, int& noSteps) override;
};
