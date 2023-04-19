#include "Score.hpp"
#include <cmath>

#include "Instance.hpp"

Score::Score(
    Instance& instance,
    AbstractAlgorithm& algorithm,
    Solution* initialSolution,
    int& noRuns,
    int* rawScores,
    int** nodes,
    int* noEvaluations,
    int* noSteps,
    float* initialSolutionScores,
    int runningTime)
    : instance(instance)
    , algorithm(algorithm)
    , initialSolution(initialSolution)
    , noRuns(noRuns)
    , rawScores(rawScores)
    , nodes(nodes)
    , noEvaluations(noEvaluations)
    , noSteps(noSteps)
    , initialSolutionScores(initialSolutionScores)
    , runningTime(runningTime)
{
    this->calculateScores();
}

Score::~Score()
{
    delete[] this->rawScores;
    delete[] this->noEvaluations;
    delete[] this->noSteps;
    delete[] this->initialSolutionScores;
    if (this->nodes != nullptr) {
        for (int i = 0; i < this->noRuns; i++) {
            delete[] this->nodes[i];
        }
        delete[] this->nodes;
    }
}

std::string Score::getInstanceName()
{
    return this->instance.getName();
}

std::string Score::getAlgorithmName()
{
    return this->algorithm.getAlgorithmName();
}

int Score::getNodesCount()
{
    return this->instance.getSize();
}

int Score::getNoRuns()
{
    return this->noRuns;
}

int* Score::getRawScores()
{
    return this->rawScores;
}

int** Score::getNodes()
{
    return this->nodes;
}

int* Score::getNoEvaluations()
{
    return this->noEvaluations;
}

int* Score::getNoSteps()
{
    return this->noSteps;
}

float* Score::getInitialSolutionScores()
{
    return this->initialSolutionScores;
}

int Score::getRunningTime()
{
    return this->runningTime;
}

int Score::getMinScore()
{
    return this->minScore;
}

float Score::getAvgScore()
{
    return this->avgScore;
}

int Score::getMaxScore()
{
    return this->maxScore;
}

float Score::getStdDev()
{
    return this->stdDev;
}

int Score::getInitialScore()
{
    return this->initialSolution->getScore();
}

void Score::calculateScores()
{
    int sum = 0;
    this->minScore = this->rawScores[0];
    this->maxScore = this->rawScores[0];
    for (int i = 0; i < this->noRuns; i++) {
        sum += this->rawScores[i];
        if (this->rawScores[i] < this->minScore) {
            this->minScore = this->rawScores[i];
        }
        if (this->rawScores[i] > this->maxScore) {
            this->maxScore = this->rawScores[i];
        }
    }

    this->avgScore = (float)sum / this->noRuns;

    float sumOfSquares = 0;
    for (int i = 0; i < this->noRuns; i++) {
        sumOfSquares += (this->rawScores[i] - this->avgScore) * (this->rawScores[i] - this->avgScore);
    }
    this->stdDev = sqrt(sumOfSquares / this->noRuns);
}
