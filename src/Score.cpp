#include "Score.hpp"
#include <cmath>

#include "Instance.hpp"

Score::Score(
    Instance& instance,
    AbstractAlgorithm& algorithm,
    Solution* initialSolution,
    int& noRuns,
    int* scores,
    int runningTime)
    : instance(instance)
    , algorithm(algorithm)
    , initialSolution(initialSolution)
    , noRuns(noRuns)
    , scores(scores)
    , runningTime(runningTime)
{
    this->calculateScores();
}

Score::~Score()
{
    delete[] this->scores;
}

std::string Score::getInstanceName()
{
    return this->instance.getName();
}

std::string Score::getAlgorithmName()
{
    return this->algorithm.getAlgorithmName();
}

int Score::getNoRuns()
{
    return this->noRuns;
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
    this->minScore = this->scores[0];
    this->maxScore = this->scores[0];
    for (int i = 0; i < this->noRuns; i++) {
        sum += this->scores[i];
        if (this->scores[i] < this->minScore) {
            this->minScore = this->scores[i];
        }
        if (this->scores[i] > this->maxScore) {
            this->maxScore = this->scores[i];
        }
    }

    this->avgScore = (float)sum / this->noRuns;

    float sumOfSquares = 0;
    for (int i = 0; i < this->noRuns; i++) {
        sumOfSquares += (this->scores[i] - this->avgScore) * (this->scores[i] - this->avgScore);
    }
    this->stdDev = sqrt(sumOfSquares / this->noRuns);
}
