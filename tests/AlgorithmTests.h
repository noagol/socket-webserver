//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_ALGORITHMTESTS_H
#define SERVER_SIDE_PROJECT_ALGORITHMTESTS_H

#include "../helpers/Position.h"
#include "../problem_solver/Solver.h"
#include "../problem_solver/SearchableMatrix.h"
#include "../problem_solver/SearcherSolver.h"
#include "../algorithm/BestFirstSearch.h"

using namespace problem_solver;

class AlgorithmTests {
public:
    static void bestFirstSearch1() {
        vector<vector<int>> matrix = {{1, 20, 5, 4},
                                      {4, 20, 5, 4},
                                      {1, 5,  6, 4},
                                      {1, 20, 9, 4}};

        SearchableMatrix problem = SearchableMatrix(matrix);
        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(new BestFirstSearch<Position<int>>());

        Solution<Position<int>> *sol = s.solve(&problem);

        std::cout << problem << std::endl;
        std::cout << *sol << std::endl;

        delete (sol);
    }

    static void loadTest1() {
        SearchableMatrix problem;
        SearchSolution<Position<int>> solution;

        istringstream p{"1,20,5,4|4,20,5,4|1,5,6,4|1,20,9,4"};
        istringstream s{"1/(0,0)|4/(1,0)|5/(0,2)|5/(2,1)|4/(2,3)|4/(3,3)"};

        p >> problem;
        s >> solution;


        std::cout << problem << std::endl;
        std::cout << solution << std::endl;

//            delete (sol);
    }
};

#endif //SERVER_SIDE_PROJECT_ALGORITHMTESTS_H
