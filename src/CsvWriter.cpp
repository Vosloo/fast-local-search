#include "CsvWriter.hpp"

#include <filesystem>
#include <fstream>


// instanceName,algorithmName,noRuns,runningTime,minScore,avgScore,maxScore,stdDev,initialSolutionScore
// kroD100.tsp,RandomAlgorithm,1000,123,20,30,40,21.37,100
// kroD100.tsp,RandomWalkAlgorithm,1000,456,21,31,41,21.37,110
// ...

void CsvWriter::writeScore(Score* score, std::string filename)
{
    std::filesystem::path path = std::filesystem::current_path() / "../data" / filename;
    std::ofstream outfile(path, std::ios_base::app);

    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open CSV file: " + path.string());
    }

    if (outfile.tellp() == 0) {
        outfile << "instanceName" << delimiter << "algorithmName" << delimiter 
                << "noRuns" << delimiter << "runningTime" << delimiter 
                << "minScore" << delimiter << "avgScore" << delimiter 
                << "maxScore" << delimiter << "stdDev" << delimiter 
                << "initialSolutionScore" << "\n";
    }

    outfile << score->getInstanceName() << delimiter << score->getAlgorithmName() << delimiter 
            << score->getNoRuns() << delimiter << score->getRunningTime() << delimiter 
            << score->getMinScore() << delimiter << score->getAvgScore() << delimiter 
            << score->getMaxScore() << delimiter <<  score->getStdDev() << delimiter 
            << score->getInitialScore() << "\n";
    
    std::filesystem::path rawScoresPath = std::filesystem::current_path() / "../data" / (path.stem().string() + "_raw.csv");
    std::ofstream rawScoresFile(rawScoresPath, std::ios_base::app);

    if (!rawScoresFile.is_open()) {
        throw std::runtime_error("Could not open CSV file: " + rawScoresPath.string());
    }

    if (rawScoresFile.tellp() == 0) {
        rawScoresFile << "instanceName" << delimiter << "algorithmName" << delimiter 
                      << "noRun" << delimiter << "score" << delimiter
                      << "noEvaluations" << delimiter << "noSteps" << delimiter 
                      << "initialSolutionScore" << "\n";
    }

    for (int i = 0; i < score->getNoRuns(); i++) {
        rawScoresFile << score->getInstanceName() << delimiter << score->getAlgorithmName() << delimiter 
                      << i << delimiter << score->getRawScores()[i] << delimiter
                      << score->getNoEvaluations()[i] << delimiter << score->getNoSteps()[i] << delimiter 
                      << score->getInitialSolutionScores()[i] << "\n";
    }

    outfile.close();
}