#include "algorithms/TabuSearchAlgorithm.hpp"
#include "Solution.hpp"
#include "delta/EdgeDelta.hpp"
#include "utils.hpp"
#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>

TabuSearchAlgorithm::TabuSearchAlgorithm(int instanceSize)
    : candidateListSize(instanceSize * 0.20)
{
    this->instanceSize = instanceSize;
    this->tabuTenure = instanceSize / 4;
    this->maxIterWoImprov = 8;
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

void TabuSearchAlgorithm::generateEliteCandidates(std::vector<EdgeDelta*>& eliteCandidates, Solution* currentSolution, int& noEvaluations)
{
    for (int i = 0; i < (int)eliteCandidates.size(); i++) {
        delete eliteCandidates[i];
    }
    eliteCandidates.clear();

    // Generate all candidates
    EdgeDelta** deltas = new EdgeDelta*[this->neighborhoodSize];
    for (int i = 0; i < this->neighborhoodSize; i++) {
        deltas[i] = new EdgeDelta(
            this->neigbourhood[i][0],
            this->neigbourhood[i][1],
            currentSolution);
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

void TabuSearchAlgorithm::updateEliteCandidates(std::vector<EdgeDelta*>& eliteCandidates, Solution* currentSolution, int& noEvaluations)
{
    for (int i = 0; i < (int)eliteCandidates.size(); i++) {
        eliteCandidates[i]->update(currentSolution);
        noEvaluations++;
    }

    std::sort(eliteCandidates.begin(), eliteCandidates.end(), [](EdgeDelta* a, EdgeDelta* b) {
        return *a > *b;
    });
}

Solution* TabuSearchAlgorithm::run(Solution* initialSolution, int& noEvaluations, int& noSteps)
{
    Solution* currentSolution = new Solution(*initialSolution);
    Solution* bestSolution = new Solution(*currentSolution);
    EdgeDelta* bestCandidate = nullptr;
    EdgeDelta* currentDelta;

    std::vector<EdgeDelta*> eliteCandidates;
    eliteCandidates.reserve(this->candidateListSize);

    std::tuple<int, int>* tabuList = new std::tuple<int, int>[this->tabuTenure];
    std::tuple<int, int> edge;

    int iterWoImprov = 0;
    int currentTabuInd = 0;
    int usedEliteCandidates = 0;
    bool tabuFull = false;
    bool tabuFound = false;
    while (iterWoImprov < this->maxIterWoImprov) {
        // Use only 20% of elite candidates then generate new ones
        if (eliteCandidates.size() == 0 
            || usedEliteCandidates >= this->candidateListSize * 0.08 
            || eliteCandidates[0]->getDelta() < -180
        ) {
            generateEliteCandidates(eliteCandidates, currentSolution, noEvaluations);
            usedEliteCandidates = 0;
        } else {
            updateEliteCandidates(eliteCandidates, currentSolution, noEvaluations);
            usedEliteCandidates++;
        }

        for (int i = 0; i < (int)eliteCandidates.size(); i++) {
            currentDelta = eliteCandidates[i];
            edge = currentDelta->getEdge();

            if (isTabu(tabuList, edge) && !fulfillsAspiration(currentDelta)) {
                tabuFound = true;
                continue;
            }

            if (bestCandidate == nullptr || *currentDelta > *bestCandidate) {
                tabuFound = false;
                bestCandidate = new EdgeDelta(*currentDelta);
                delete currentDelta;
                eliteCandidates.erase(eliteCandidates.begin() + i);
                break; // Elite candidates are sorted so as soon as we find a better one we can stop
            }
        }

        if (bestCandidate == nullptr) {
            // No candidate found, we select the oldest tabu edge
            int candidateIdx = -1;
            if (tabuFound) {
                // Choose by the oldest tabu - aspiration by default
                if (tabuFull) {
                    if (currentTabuInd < this->tabuTenure - 1) {
                        candidateIdx = currentTabuInd + 1;
                    } else {
                        candidateIdx = 0;
                    }
                } else {
                    candidateIdx = 0;
                }
                bestCandidate = new EdgeDelta(tabuList[candidateIdx], currentSolution);
            }
        }

        bestCandidate->apply();
        if (bestCandidate != nullptr) {
            delete bestCandidate;
            bestCandidate = nullptr;
        }

        if (*currentSolution < *bestSolution) {
            delete bestSolution;
            bestSolution = new Solution(*currentSolution);
            iterWoImprov = 0;
            noSteps++;
        } else {
            iterWoImprov++;
        }

        updateTabuList(tabuList, edge, currentTabuInd);
        currentTabuInd = (currentTabuInd + 1) % this->tabuTenure;
        currentDelta = nullptr;

        tabuFound = false;
        if (!tabuFull && currentTabuInd == 0) {
            tabuFull = true;
        }
    }

    delete[] tabuList;
    delete currentSolution;

    for (auto& candidate : eliteCandidates) {
        delete candidate;
    }

    return bestSolution;
}