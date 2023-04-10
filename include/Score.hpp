#pragma once

#include <iostream>

#include "Instance.hpp"
#include "Solution.hpp"
#include "algorithms/AbstractAlgorithm.hpp"

class Score {
private:
    Instance& instance;
    AbstractAlgorithm& algorithm;
    Solution* initialSolution;
    int& noRuns;
    int* rawScores;
    int* noEvaluations;
    int* noSteps;
    float* initialSolutionScores;
    int runningTime; // in ms
    int minScore;
    float avgScore;
    int maxScore;
    float stdDev;
    void calculateScores();

public:
    Score(
        Instance& instance,
        AbstractAlgorithm& algorithm,
        Solution* initialSolution,
        int& noRuns,
        int* rawScores,
        int* noEvaluations,
        int* noSteps,
        float* initialSolutionScores,
        int runningTime);
    ~Score();
    std::string getInstanceName();
    std::string getAlgorithmName();
    int getNoRuns();
    int* getRawScores();
    int* getNoEvaluations();
    int* getNoSteps();
    float* getInitialSolutionScores();
    int getRunningTime();
    int getMinScore();
    float getAvgScore();
    int getMaxScore();
    float getStdDev();
    int getInitialScore();
};
