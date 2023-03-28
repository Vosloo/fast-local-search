#include "DistanceMatrix.hpp"
#include "Node.hpp"
#include "Solution.hpp"
#include "utils.hpp"
#include "algorithms/RandomWalkAlgorithm.hpp"


Solution RandomWalkAlgorithm::run(Solution& initialSolution)
{
    Solution bestSolution = initialSolution;
    int size = initialSolution.getSize();
    Node* tempNode;
    int indicies[2];
    int i = 0;


    while (i < 100) // Zmienić na avg z G albo S
    {
        Solution currentSolution = Solution(bestSolution);

        getTwoRandomIndicies(size, indicies);

        Node** currentNodes = currentSolution.getCurrentNodes();

        tempNode = currentNodes[indicies[0]];
        currentNodes[indicies[0]] = currentNodes[indicies[1]];
        currentNodes[indicies[1]] = tempNode;

        if (currentSolution.getScore() < bestSolution.getScore()) {
            bestSolution = currentSolution;
        }
        i++;
    }
    
    return bestSolution;
};