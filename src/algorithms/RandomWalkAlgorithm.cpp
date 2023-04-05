#include "algorithms/RandomWalkAlgorithm.hpp"
#include "DistanceMatrix.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "delta/NodeDelta.hpp"
#include "utils.hpp"

Solution* RandomWalkAlgorithm::run(Solution* initialSolution)
{
    Solution* bestSolution = new Solution(*initialSolution);

    int i = 0;
    int indices[2];
    while (i < 100) {
        // Replace two random nodes
        getTwoRandomIndicies(bestSolution->getSize(), indices);

        NodeDelta nodeDelta(indices[0], indices[1], bestSolution);

        if (nodeDelta.getDelta() > 0) {
            nodeDelta.apply();
        }

        i++;
    }

    return bestSolution;
};