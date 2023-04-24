#include "algorithms/TabuSearchAlgorithm.hpp"
#include "Solution.hpp"
#include "delta/EdgeDelta.hpp"
#include "utils.hpp"
#include <set>
#include <tuple>
#include <vector>

TabuSearchAlgorithm::TabuSearchAlgorithm(int instanceSize)
    : candidateListSize(instanceSize / 10)
{
    this->instanceSize = instanceSize;
    this->tabuTenure = instanceSize / 4;
    this->maxIterWoImprov = 15;
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

bool TabuSearchAlgorithm::fulfillsAspiration()
{
    return true; // TODO
}

void TabuSearchAlgorithm::updateEliteCandidates(std::vector<EdgeDelta*> eliteCandidates, Solution* currentSolution)
{
    int worstDeltaInd = -1;
    float worstDelta = -1e6;
    for (int i = 0; i < this->neighborhoodSize; i++) {
        EdgeDelta* delta = new EdgeDelta(this->neigbourhood[i][0], this->neigbourhood[i][1], currentSolution);
        if (i < this->candidateListSize) {
            eliteCandidates[i] = delta;
            if (i < this->candidateListSize - 1) {
                continue;
            }
        } else {
            if (delta->getDelta() > worstDelta) {
                delete eliteCandidates[worstDeltaInd];
                eliteCandidates[worstDeltaInd] = delta;
            }
        }

        worstDelta = -1e6;
        for (int j = 0; j < std::min(i, this->candidateListSize); j++) {
            if (eliteCandidates[j]->getDelta() < worstDelta) {
                worstDelta = eliteCandidates[j]->getDelta();
                worstDeltaInd = j;
            }
        }
    }
}

Solution* TabuSearchAlgorithm::run(Solution* initialSolution, int& noEvaluations, int& noSteps)
{
    Solution* currentSolution = new Solution(*initialSolution);
    Solution* bestSolution = nullptr;

    EdgeDelta* bestDelta = nullptr;
    EdgeDelta* currentDelta;

    std::cout << noEvaluations << std::endl;
    std::cout << noSteps << std::endl;

    std::vector<EdgeDelta*> eliteCandidates(this->candidateListSize); // probably should use queue

    std::tuple<int, int> bestEdge;
    std::set<std::tuple<int, int>> tabuList;

    int iterWoImprov = 0;
    int currentCandidate = 0;
    while (iterWoImprov < this->maxIterWoImprov) {
        this->updateEliteCandidates(eliteCandidates, currentSolution);
        for (int i = 0; i < this->candidateListSize; i++) {
            // Pop the first element from the candidate list

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
        currentCandidate++;

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