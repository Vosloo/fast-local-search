#include <chrono>

#include "DistanceMatrix.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "algorithms/RandomWalkAlgorithm.hpp"
#include "delta/NodeDelta.hpp"
#include "utils.hpp"

RandomWalkAlgorithm::RandomWalkAlgorithm(float maxRuntime)
{
    this->maxRuntime = maxRuntime;
    setAlgorithmName("RandomWalkAlgorithm");
}

Solution* RandomWalkAlgorithm::run(Solution* initialSolution)
{
    Solution* bestSolution = new Solution(*initialSolution);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    int indices[2];
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() < maxRuntime) {
        getTwoRandomIndicies(bestSolution->getSize(), indices);

        NodeDelta nodeDelta(indices[0], indices[1], bestSolution);

        if (nodeDelta.getDelta() > 0) {
            nodeDelta.apply();
        }
    }

    return bestSolution;
};