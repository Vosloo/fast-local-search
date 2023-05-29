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
#include "algorithms/TabuSearchAlgorithm.hpp"
#include "algorithms/SimulatedAnnealingAlgorithm.hpp"
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
    int& noRuns,
    bool saveNodes = false)
{

    Solution* solution;
    Solution* currentInitial = new Solution(*initialSolution);

    int* randomPermutation = new int[initialSolution->getSize()];
    for (int i = 0; i < initialSolution->getSize(); i++) {
        randomPermutation[i] = i;
    }

    int* rawScores = new int[noRuns];
    int** nodes = nullptr;
    if (saveNodes) {
        nodes = new int*[noRuns];
    }
    int* noEvaluations = new int[noRuns] { 0 };
    int* noSteps = new int[noRuns] { 0 };
    float* initialSolutionScores = new float[noRuns];

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int i = 0; i < noRuns; i++) {
        std::cout << "\rRun " << i + 1 << "/" << noRuns << std::flush;
        solution = algorithm.run(currentInitial, noEvaluations[i], noSteps[i]);
        rawScores[i] = solution->getScore();
        initialSolutionScores[i] = currentInitial->getScore();

        if (saveNodes) {
            nodes[i] = solution->getCopyCurrentNodes();
        }

        delete currentInitial;
        delete solution;
        if (i != noRuns - 1) {
            getRandomPermutation(randomPermutation, initialSolution->getSize());
            currentInitial = new Solution(
                randomPermutation,
                initialSolution->getSize(),
                *initialSolution->getDistanceMatrix());
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    int64_t runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    std::cout << std::endl;

    delete[] randomPermutation;

    return new Score(
        instance,
        algorithm,
        initialSolution,
        noRuns,
        rawScores,
        nodes,
        noEvaluations,
        noSteps,
        initialSolutionScores,
        runTime);
}

int runAlgorithms(
    Instance& instance,
    AbstractAlgorithm* algorithms[],
    Solution* initialSolution,
    int& noRuns,
    bool saveNodes,
    int noAlgorithms,
    CsvWriter& csvWriter,
    std::string outputFilename)
{
    int greedyRunTime = -1;
    for (int i = 0; i < noAlgorithms; i++) {
        AbstractAlgorithm* algorithm = algorithms[i];
        std::cout << "Running " << algorithm->getAlgorithmName() << " ..." << std::endl;

        Score* score = runAlgoritmh(instance, *algorithm, initialSolution, noRuns, saveNodes);
        if (algorithm->getAlgorithmName() == "GreedyAlgorithm") {
            greedyRunTime = score->getRunningTime();
        }

        printRunningTime(score);
        printScore(score);

        csvWriter.writeScore(score, outputFilename);

        delete algorithm;
        delete score;
    }

    return greedyRunTime;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: ./tsp <no_runs> [optional_output_filename]" << std::endl;
        return 1;
    }

    std::string outputFilename = "results.csv";
    if (argc == 3) {
        outputFilename = argv[2];
    }

    srand(time(NULL));

    FileReader fileReader;
    CsvWriter csvWriter;

    std::filesystem::path instancesDir = std::filesystem::current_path() / "../data" / "instances";

    int noRuns = std::stoi(argv[1]);
    std::cout << "No. runs: " << noRuns << std::endl;
    for (const auto& instancePath : std::filesystem::directory_iterator(instancesDir)) {
        if (instancePath.path().stem() == "pcb442") {
        // if (instancePath.path().stem() != "ch130") {
            continue; // Too big for steepest, for now don't run it
        }

        std::cout << "-----------------\n"
                  << "Running instance: " << instancePath.path().stem() << " (";

        Instance instance = fileReader.loadTspInstance(instancePath.path().stem());
        std::cout << instance.getSize() << " nodes)"
                  << "\n-----------------\n"
                  << std::endl;
        DistanceMatrix distanceMatrix(&instance);

        int* randomPermutation = new int[instance.getSize()];
        for (int i = 0; i < instance.getSize(); i++) {
            randomPermutation[i] = i;
        }

        getRandomPermutation(randomPermutation, instance.getSize());
        Solution* initialSolution = new Solution(
            randomPermutation,
            instance.getSize(),
            distanceMatrix);

        AbstractAlgorithm* firstAlgorithms[] = {
            new TabuSearchAlgorithm(initialSolution->getSize()),
            // new SteepestAlgorithm(initialSolution->getSize()),
            // new SimulatedAnnealingAlgorithm(initialSolution->getSize(), 0.95),
            // new GreedyAlgorithm(initialSolution->getSize()),
            // new HeuristicAlgorithm(),
        };

        int greedyRunTime = runAlgorithms(instance, firstAlgorithms, initialSolution, noRuns, true, 1, csvWriter, outputFilename);
        std::cout << "Greedy running time: " << greedyRunTime << " and " << (float)greedyRunTime / noRuns << " per run" << std::endl;

        // AbstractAlgorithm* secondAlgorithms[] = {
        //     new RandomAlgorithm((float)greedyRunTime / noRuns),
        //     new RandomWalkAlgorithm((float)greedyRunTime / noRuns)
        // };

        // runAlgorithms(instance, secondAlgorithms, initialSolution, noRuns, true, 2, csvWriter, outputFilename);

        delete initialSolution;
        delete[] randomPermutation;
    }

    return 0;
}
