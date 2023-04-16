#include "algorithms/TabuSearchAlgorithm.hpp"
#include "Solution.hpp"
#include "delta/EdgeDelta.hpp"
#include "utils.hpp"
#include <set>
#include <tuple>

TabuSearchAlgorithm::TabuSearchAlgorithm(int instanceSize)
{
    this->instanceSize = instanceSize;
    this->tabuTenure = instanceSize / 4;
    this->maxIterWoImprov = 100;
    this->neighborhoodSize = (instanceSize - 1) * (instanceSize - 2) / 2 - 1;
    this->neigbourhood = getNeighborhood(this->instanceSize);
    setAlgorithmName("TabuSearchAlgorithm");
}

TabuSearchAlgorithm::~TabuSearchAlgorithm()
{
    for (int i = 0; i < this->neighborhoodSize; i++) {
        delete[] this->neigbourhood[i];
    }
    delete[] this->neigbourhood;
}

void TabuSearchAlgorithm::updateTabuList(std::set<std::tuple<int, int>>& tabuList, std::tuple<int, int>& edge)
{
    if ((int)tabuList.size() >= this->tabuTenure) {
        tabuList.erase(tabuList.begin());
    }

    tabuList.insert(edge);
}

bool TabuSearchAlgorithm::isTabu(std::set<std::tuple<int, int>>& tabuList, std::tuple<int, int>& edge)
{
    return tabuList.find(edge) != tabuList.end();
}

Solution* TabuSearchAlgorithm::run(Solution* initialSolution, int& noEvaluations, int& noSteps)
{
    Solution* currentSolution = new Solution(*initialSolution);
    Solution* bestSolution = nullptr;
    
    EdgeDelta* bestDelta = nullptr;
    EdgeDelta* currentDelta;

    std::tuple<int, int> bestEdge;
    std::set<std::tuple<int, int>> tabuList;

    int iterWoImprov = 0;
    while (iterWoImprov < this->maxIterWoImprov) {
        for (int i = 0; i < this->neighborhoodSize; i++) {
            std::tuple<int, int> edge = std::make_tuple(this->neigbourhood[i][0], this->neigbourhood[i][1]);
            if (isTabu(tabuList, edge)) {
                continue;
            }

            currentDelta = new EdgeDelta(edge, currentSolution);
            if (bestDelta == nullptr || *currentDelta > *bestDelta) {
                delete bestDelta;
                bestDelta = currentDelta;
                bestEdge = edge;
            } else {
                delete currentDelta;
            }

            noEvaluations++;
        }

        bestDelta->apply();
        delete bestDelta;

        if (bestSolution == nullptr || *currentSolution < *bestSolution) {
            delete bestSolution;
            bestSolution = new Solution(*currentSolution);
            iterWoImprov = 0;
            noSteps++;        
        } else {
            iterWoImprov++;
        }

        updateTabuList(tabuList, bestEdge);

        bestDelta = nullptr;
    }

    delete currentSolution;
    return bestSolution;
}