#include "algorithms/TabuSearchAlgorithm.hpp"
#include "Solution.hpp"
#include "delta/EdgeDelta.hpp"
#include "utils.hpp"
#include <algorithm>
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

void TabuSearchAlgorithm::updateTabuList(std::tuple<int, int>* tabuList, std::tuple<int, int>& edge, int& tabuIndex)
{
    tabuList[tabuIndex] = edge;
}

void TabuSearchAlgorithm::moveTabuAtNewest(std::tuple<int, int>* tabuList, int& tabuIndex, int& toMoveInd)
{
    std::tuple<int, int> tmp = tabuList[toMoveInd];
    tabuList[toMoveInd] = tabuList[tabuIndex];
    tabuList[tabuIndex] = tmp;
}

bool TabuSearchAlgorithm::isTabu(std::tuple<int, int>* tabuList, std::tuple<int, int>& edge)
{
    for (int i = 0; i < this->tabuTenure; i++) {
        if (tabuList[i] == edge) {
            return true;
        }
    }
    return false;
}

bool TabuSearchAlgorithm::fulfillsAspiration(EdgeDelta* delta)
{
    return delta->getDelta() > 0;
}

void TabuSearchAlgorithm::updateEliteCandidates(std::vector<EdgeDelta*>& eliteCandidates, Solution* currentSolution, int& noEvaluations)
{
    for (int i = 0; i < (int)eliteCandidates.size(); i++) {
        delete eliteCandidates[i];
    }
    eliteCandidates.clear();

    eliteCandidates.reserve(this->candidateListSize);

    // Generate all candidates
    EdgeDelta** deltas = new EdgeDelta*[this->neighborhoodSize];
    for (int i = 0; i < this->neighborhoodSize; i++) {
        deltas[i] = new EdgeDelta(this->neigbourhood[i][0], this->neigbourhood[i][1], currentSolution);
        noEvaluations++;
    }

    // Select k best candidates
    std::sort(deltas, deltas + this->neighborhoodSize, [](EdgeDelta* a, EdgeDelta* b) {
        return *a > *b;
    });
    for (int i = 0; i < this->neighborhoodSize; i++) {
        if (i < this->candidateListSize) {
            eliteCandidates.push_back(deltas[i]);
            continue;
        }
        delete deltas[i];
    }
    delete[] deltas;
}

Solution* TabuSearchAlgorithm::run(Solution* initialSolution, int& noEvaluations, int& noSteps)
{
    Solution* currentSolution = new Solution(*initialSolution);
    Solution* bestSolution = nullptr;

    EdgeDelta* currentDelta;

    std::vector<EdgeDelta*> eliteCandidates;

    std::tuple<int, int>* tabuList = new std::tuple<int, int>[this->tabuTenure];

    int iterWoImprov = 0;
    int candidateChosen = -1;
    int currentTabuInd = 0;
    bool tabuFound = false;
    bool tabuFull = false;
    while (iterWoImprov < this->maxIterWoImprov) {
        this->updateEliteCandidates(eliteCandidates, currentSolution, noEvaluations);

        for (int i = 0; i < (int)eliteCandidates.size(); i++) {
            std::tuple<int, int> edge = eliteCandidates[i]->getEdge();

            if (this->isTabu(tabuList, edge)) {
                tabuFound = true;
            }

            if (tabuFound && this->fulfillsAspiration(eliteCandidates[i])) {
                candidateChosen = i;
                break;
            } else if (tabuFound) {
                continue;
            }

            candidateChosen = i;
            tabuFound = false;
            break;
        }

        if (tabuFound) {
            // Choose by the oldest tabu - aspiration by default
            if (tabuFull) {
                if (currentTabuInd < this->tabuTenure - 1) {
                    candidateChosen = currentTabuInd + 1;
                } else {
                    candidateChosen = 0;
                }
            } else {
                candidateChosen = 0;
            }
            currentDelta = new EdgeDelta(tabuList[candidateChosen], currentSolution);
        } else {
            currentDelta = eliteCandidates[candidateChosen];
            eliteCandidates.erase(eliteCandidates.begin() + candidateChosen);
        }

        currentDelta->apply();

        if (bestSolution == nullptr || *currentSolution < *bestSolution) {
            if (bestSolution != nullptr) {
                delete bestSolution;
            }
            bestSolution = new Solution(*currentSolution);
            iterWoImprov = 0;
            noSteps++;
        } else {
            iterWoImprov++;
        }

        if (tabuFound) {
            this->moveTabuAtNewest(tabuList, currentTabuInd, candidateChosen);
        } else {
            std::tuple<int, int> edge = currentDelta->getEdge();
            this->updateTabuList(tabuList, edge, currentTabuInd);
        }
        currentTabuInd++;
        currentTabuInd %= this->tabuTenure;
        if (!tabuFull && currentTabuInd == 0) {
            tabuFull = true;
        }

        tabuFound = false;
        candidateChosen = -1;

        delete currentDelta;
    }

    for (int i = 0; i < (int)eliteCandidates.size(); i++) {
        delete eliteCandidates[i];
    }

    delete[] tabuList;
    delete currentSolution;
    return bestSolution;
}