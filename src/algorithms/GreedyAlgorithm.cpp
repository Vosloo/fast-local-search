#include "algorithms/GreedyAlgorithm.hpp"

#include "Solution.hpp"

GreedyAlgorithm::GreedyAlgorithm(int instanceSize)
{
    this->instanceSize = instanceSize;
    this->neigbourhood = getNeighborhood(this->instanceSize);
}

GreedyAlgorithm::~GreedyAlgorithm()
{
    for (int i = 0; i < this->instanceSize * (this->instanceSize - 2) / 2; i++) {
        delete[] this->neigbourhood[i];
    }
    delete[] this->neigbourhood;
}

Solution* GreedyAlgorithm::run(Solution* initialSolution)
{
    Solution* currentSolution = initialSolution;

    // wygenerować możliwe ruchy - gdzie delta większa od 0
    // shuffle ruchów
    // sprawdzić ruchy do pierwszego najbliższego jeśli istnieją

    int neighborhood = getNeighborhood(currentSolution);
    shuffle(neighborhood)
    for 

    return currentSolution;
}

// [(i_1, j_1), (i_2, j_2), ..., (i_n, j_n)]


int getNeighborhood(int n)
{
    // (n - 2)
    int** neighborhood = new int*[n * (n - 2) / 2];
    int currentInd = 0;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 2; j < n; j++) {
            neighborhood[currentInd] = new int[2];
            neighborhood[currentInd][0] = i;
            neighborhood[currentInd][1] = j;
            currentInd++;
        }
        // delta = distanceMatrix[solution[i]][solution[i+1]] + distanceMatrix[solution[j]][solution[j+1]]
        // delta -= distanceMatrix[solution[i]][solution[j]] + distanceMatrix[solution[i+1]][solution[j+1]]
    }

    return neighborhood;
}
    /*
    def get_possible_edge_swaps(pairs, distance_matrix):
        length = len(pairs)
        infra = []
        for i, pair1 in enumerate(pairs):
            for j, pair2 in enumerate(pairs):
                if (i != j) and ((i + 1) % length != j) and ((i - 1) % length != j):
                    delta = calculate_delta_infra(pair1, pair2, distance_matrix)
                    if delta > 0:
                        infra.append(["infra", pair1, pair2, delta])
        return infra

    def list2pairs(solution):
        res = [(solution[i], solution[i + 1]) for i in range(len(solution) - 1)]
        res.append((solution[-1], solution[0]))
        return res
    */

    // 1 2 3 4 5 6 7 8
    // 1 -> 2 with 5 -> 6
    // 1 5 4 3 2 6 7 8

    // 1 2 3 4 5 6 7 8
    // 5 -> 6 with 1 -> 2
    // 6 2 3 4 5 1 8 7