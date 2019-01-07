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
#include "../algorithm/BFS.h"
#include "../algorithm/DFS.h"
#include "../algorithm/AStar.h"


using namespace problem_solver;

class AlgorithmTests {
public:
    static void test() {
        vector<vector<int>> matrix1 = {{1, 20, 5, 4},
                                       {4, 20, 5, 4},
                                       {1, 5,  6, 4},
                                       {1, 20, 9, 4}};

//        bestFirstSearch1(matrix1);
//        BFS1(matrix1);
        DFS1(matrix1);
//        AStar1(matrix1);

        cout << endl;

        vector<vector<int>> matrix2 = {
                {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
                {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
                {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
                {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
                {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}
        };

//        bestFirstSearch1(matrix2);
//        BFS1(matrix2);
//        DFS1(matrix2);
//        AStar1(matrix2);

        vector<vector<int>> matrix3 = {
                {1, 1, 1},
                {1, 1, 1},
                {1, 1, 1}
        };

//        AStar1(matrix3);

        cout << endl;


    }

    static void bestFirstSearch1(vector<vector<int>> matrix) {
        SearchableMatrix problem = SearchableMatrix(matrix);
        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(new BestFirstSearch<Position<int>>());

        Solution<Position<int>> *sol = s.solve(&problem);

        std::cout << *sol << std::endl;
        std::cout << sol->getTotalCost() << std::endl;

        delete (sol);
    }

    static void BFS1(vector<vector<int>> matrix) {
        SearchableMatrix problem = SearchableMatrix(matrix);
        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(new BFS<Position<int>>());

        Solution<Position<int>> *sol = s.solve(&problem);

        std::cout << *sol << std::endl;
        std::cout << sol->getTotalCost() << std::endl;
        delete (sol);
    }

    static void DFS1(vector<vector<int>> matrix) {
        SearchableMatrix problem = SearchableMatrix(matrix);
        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(new DFS<Position<int>>());

        Solution<Position<int>> *sol = s.solve(&problem);

        std::cout << *sol << std::endl;
        std::cout << sol->getTotalCost() << std::endl;
        delete (sol);
    }

    static void AStar1(vector<vector<int>> matrix) {
        SearchableMatrix problem = SearchableMatrix(matrix);
        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(new AStar<Position<int>>());

        Solution<Position<int>> *sol = s.solve(&problem);

        std::cout << *sol << std::endl;
        std::cout << sol->getTotalCost() << std::endl;
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
