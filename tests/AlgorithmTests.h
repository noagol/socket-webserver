//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_ALGORITHMTESTS_H
#define SERVER_SIDE_PROJECT_ALGORITHMTESTS_H

#include <Position.h>
#include <Solver.h>
#include <SearchableMatrix.h>
#include <SearcherSolver.h>
#include <BestFirstSearch.h>

using namespace problem_solver;

class AlgorithmTests {
public:
    static void bestFirstSearch1() {
        vector <vector<int>> matrix = {{1, 20, 5, 4},
                                       {4, 20, 5, 4},
                                       {1, 5,  6, 4},
                                       {1, 20, 9, 4}};

        SearchableMatrix problem = SearchableMatrix(matrix);
        SearcherSolver <Position<int>>
                s = SearcherSolver<Position<int >>(new BestFirstSearch<Position<int>>());

        Solution <Position<int>> *sol = s.solve(&problem);

        std::cout << *sol << std::endl;

        delete (sol);
    }
};

#endif //SERVER_SIDE_PROJECT_ALGORITHMTESTS_H
