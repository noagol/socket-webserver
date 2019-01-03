#include <iostream>

#include "problem_solver/SearcherSolver.h"
#include "algorithm/BestFirstSearch.h"
#include "helpers/Position.h"
#include "problem_solver/SearchableMatrix.h"

using namespace problem_solver;


int main() {
    vector<vector<int>> matrix = {{1, 20, 5, 4},
                                  {4, 20, 5, 4},
                                  {1, 5,  6, 4},
                                  {1, 20, 9, 4}};
    SearchableMatrix problem = SearchableMatrix(matrix);
    SearcherSolver<Position<int>>
            s = SearcherSolver<Position<int>>(new BestFirstSearch<Position<int>>());

    Solution<Position<int>> *sol = s.solve(&problem);

    std::cout << sol << std::endl;


    return 0;
}