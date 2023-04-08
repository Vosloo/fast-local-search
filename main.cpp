#include <chrono>
#include <filesystem>
#include <iostream>
#include <random>

#include "CsvWriter.hpp"
#include "DistanceMatrix.hpp"
#include "FileReader.hpp"
#include "Instance.hpp"
#include "Node.hpp"
#include "Score.hpp"
#include "Solution.hpp"
#include "algorithms/GreedyAlgorithm.hpp"
#include "algorithms/HeuristicAlgorithm.hpp"
#include "algorithms/RandomAlgorithm.hpp"
#include "algorithms/RandomWalkAlgorithm.hpp"
#include "algorithms/SteepestAlgorithm.hpp"
#include "delta/NodeDelta.hpp"
#include "utils.hpp"

void printStats(Solution& solution)
{
    std::cout << "---------------------" << std::endl;
    std::cout << "Score: " << solution.getScore() << std::endl;
    for (int i = 0; i < solution.getSize(); i++) {
        std::cout << solution.getCurrentNodes()[i];
        if (i != solution.getSize() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n---------------------" << std::endl;
}

void printRunningTime(Score* score)
{
    std::cout << "Running time of " << score->getAlgorithmName() << ": " << score->getRunningTime() << " [ms]" << std::endl;
}

void printScore(Score* score)
{
    std::cout << score->getAlgorithmName()
              << " - min: " << score->getMinScore()
              << " / avg: " << score->getAvgScore()
              << " / max: " << score->getMaxScore() << "\n"
              << std::endl;
}

Score* runAlgoritmh(
    Instance& instance,
    AbstractAlgorithm& algorithm,
    Solution* initialSolution,
    int& noRuns)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    Solution* solution;
    Solution* currentInitial = new Solution(*initialSolution);
    int* rawScores = new int[noRuns];
    for (int i = 0; i < noRuns; i++) {
        solution = algorithm.run(currentInitial);
        rawScores[i] = solution->getScore();

        delete currentInitial;
        delete solution;
        if (i != noRuns - 1) {
            currentInitial = new Solution(getRandomPermutation(initialSolution->getSize()), initialSolution->getSize(), *initialSolution->getDistanceMatrix());
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    int64_t runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    return new Score(instance, algorithm, initialSolution, noRuns, rawScores, runTime);
}

int runAlgorithms(
    Instance& instance,
    AbstractAlgorithm* algorithms[],
    Solution* initialSolution,
    int& noRuns,
    int noAlgorithms,
    CsvWriter& csvWriter)
{
    int greedyRunTime = -1;
    for (int i = 0; i < noAlgorithms; i++) {
        AbstractAlgorithm* algorithm = algorithms[i];
        std::cout << "Running " << algorithm->getAlgorithmName() << " ..." << std::endl;

        Score* score = runAlgoritmh(instance, *algorithm, initialSolution, noRuns);
        if (algorithm->getAlgorithmName() == "GreedyAlgorithm") {
            greedyRunTime = score->getRunningTime();
        }

        printRunningTime(score);
        printScore(score);

        csvWriter.writeScore(score, "results.csv");

        delete algorithm;
        delete score;
    }

    return greedyRunTime;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Usage: ./tsp <no_runs>" << std::endl;
        return 1;
    }

    std::cout << argv[1] << std::endl;

    srand(time(NULL));

    FileReader fileReader;
    CsvWriter csvWriter;

    std::filesystem::path instancesDir = std::filesystem::current_path() / "../data" / "instances";

    int noRuns = std::stoi(argv[1]);
    std::cout << "No. runs: " << noRuns << std::endl;
    for (const auto& instancePath : std::filesystem::directory_iterator(instancesDir)) {
        if (instancePath.path().stem() == "pcb442") {
            continue; // Too big for steepest, for now don't run it
        }

        std::cout << "-----------------\n" << "Running instance: " << instancePath.path().stem() << "\n-----------------\n" << std::endl;

        Instance instance = fileReader.loadTspInstance(instancePath.path().stem());
        DistanceMatrix distanceMatrix(&instance);
        Solution* initialSolution = new Solution(getRandomPermutation(instance.getSize()), instance.getSize(), distanceMatrix);

        AbstractAlgorithm* firstAlgorithms[] = {
            new SteepestAlgorithm(initialSolution->getSize()),
            new GreedyAlgorithm(initialSolution->getSize()),
            new HeuristicAlgorithm(),
        };

        int greedyRunTime = runAlgorithms(instance, firstAlgorithms, initialSolution, noRuns, 3, csvWriter);
        std::cout << "Greedy running time: " << greedyRunTime << " and " << (float)greedyRunTime / noRuns << " per run" << std::endl;

        AbstractAlgorithm* secondAlgorithms[] = {
            new RandomAlgorithm((float)greedyRunTime / noRuns),
            new RandomWalkAlgorithm((float)greedyRunTime / noRuns)
        };

        runAlgorithms(instance, secondAlgorithms, initialSolution, noRuns, 2, csvWriter);

        delete initialSolution;
    }

    return 0;
}
