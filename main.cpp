#include <iostream>
#include "problem_solver/Solver.h"
#include "problem_solver/StringReverser.h"
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
    SearcherSolver<SearchableMatrix, Position<int>> s =
            SearcherSolver<SearchableMatrix, Position<int>>(new BestFirstSearch(problem));

    std::cout << solver.solve("nkkjlj") << std::endl;


    return 0;
}