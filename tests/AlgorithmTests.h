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

        testAlgorithms(&matrix1);

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

        testAlgorithms(&matrix2);

        vector<vector<int>> matrix3 = {
                {1, 5,  5},
                {3, 10, 5},
                {1, 3,  1}
        };

        testAlgorithms(&matrix3);

        vector<vector<int>> matrix4 = {
                {1, 5, 5},
                {5, 1, 5},
                {5, 1, 1}
        };

        testAlgorithms(&matrix4);

    }

    static void testAlgorithms(vector<vector<int>> *matrix) {
        SearchableMatrix problem = SearchableMatrix(matrix);
        cout << problem << endl << endl;

        cout << "===========Best First Search:" << endl;
        testAlgorithm1(&problem, new BestFirstSearch<Position<int>>());
        cout << "===========A Star:" << endl;
        testAlgorithm1(&problem, new AStar<Position<int>>());
        cout << "===========BFS:" << endl;
        testAlgorithm1(&problem, new BFS<Position<int>>());
        cout << "===========DFS:" << endl;
        testAlgorithm1(&problem, new DFS<Position<int>>());
        cout << endl;
    }

    static void testAlgorithm1(SearchableMatrix *problem, Searcher<Position<int>> *alg) {
        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(alg);

        Solution<Position<int>> *sol = s.solve(problem);

        std::cout << "Solution: " << *sol << std::endl;
        std::cout << "Total cost: " << sol->getTotalCost() << std::endl;
        std::cout << "Vertices count: " << alg->getCount() << std::endl;

        delete (sol);
    }

    static void bestFirstSearch1(vector<vector<int>> *matrix) {
        SearchableMatrix problem = SearchableMatrix(matrix);
        Searcher<Position<int>> *searcher = new BestFirstSearch<Position<int>>();
        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(searcher);

        Solution<Position<int>> *sol = s.solve(&problem);

        std::cout << *sol << std::endl;
        std::cout << sol->getTotalCost() << std::endl;
        std::cout << searcher->getCount() << std::endl;

        delete (sol);
    }

    static void BFS1(vector<vector<int>> *matrix) {
        SearchableMatrix problem = SearchableMatrix(matrix);
        Searcher<Position<int>> *searcher = new BFS<Position<int>>();

        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(searcher);

        int counter = 0;
        Solution<Position<int>> *sol = s.solve(&problem);


        std::cout << *sol << std::endl;
        std::cout << sol->getTotalCost() << std::endl;
        std::cout << searcher->getCount() << std::endl;

        delete (sol);
    }

    static void DFS1(vector<vector<int>> *matrix) {
        SearchableMatrix problem = SearchableMatrix(matrix);
        Searcher<Position<int>> *searcher = new DFS<Position<int>>();

        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(searcher);

        Solution<Position<int>> *sol = s.solve(&problem);

        std::cout << *sol << std::endl;
        std::cout << sol->getTotalCost() << std::endl;
        std::cout << searcher->getCount() << std::endl;

        delete (sol);
    }

    static void AStar1(vector<vector<int>> *matrix) {
        SearchableMatrix problem = SearchableMatrix(matrix);
        Searcher<Position<int>> *searcher = new AStar<Position<int>>();

        SearcherSolver<Position<int>>
                s = SearcherSolver<Position<int >>(searcher);

        Solution<Position<int>> *sol = s.solve(&problem);

        std::cout << *sol << std::endl;
        std::cout << sol->getTotalCost() << std::endl;
        std::cout << searcher->getCount() << std::endl;

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
