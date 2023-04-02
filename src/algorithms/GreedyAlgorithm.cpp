#include "algorithms/GreedyAlgorithm.hpp"

#include "Solution.hpp"

Solution* GreedyAlgorithm::run(Solution* initialSolution)
{
    Solution* currentSolution = initialSolution;
    
    //wygenerować możliwe ruchy - gdzie delta większa od 0
    //shuffle ruchów 
    //sprawdzić ruchy do pierwszego najbliższego jeśli istnieją

    int neighborhood = getNeighborhood(currentSolution);








    return currentSolution;
}

int getNeighborhood(currentSolution)
{


    return
}

int 

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