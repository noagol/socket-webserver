//
// Created by EB on 10/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_EXPIREMENT_H
#define SERVER_SIDE_PROJECT_EXPIREMENT_H

#include <fstream>
#include <SearchableMatrix.h>
#include "MatrixGenerator.h"
#include "Position.h"
#include "SearcherSolver.h"
#include "BestFirstSearch.h"
#include "BFS.h"
#include "DFS.h"
#include "AStar.h"

#define EPOCHS 10

using namespace problem_solver;

class Expirement {
    vector<Matrix> matrices;
public:
    Expirement() {
        int i;
        int size;

        for (i = 0; i < EPOCHS; i++) {
            size = 10 + i * 4;
            MatrixGenerator mg = MatrixGenerator(size, size);
            matrices.push_back(mg.generate());
        }
    }

    void run() {
        typename vector<Matrix>::iterator it;
        for (it = matrices.begin(); it != matrices.end(); it++) {
            SearchableMatrix searchableMatrix = SearchableMatrix(&(*it).getMatrix());
            runAlgorithm(searchableMatrix, new BestFirstSearch<Position<int>>());
            runAlgorithm(searchableMatrix, new DFS<Position<int>>());
            runAlgorithm(searchableMatrix, new BFS<Position<int>>());
            runAlgorithm(searchableMatrix, new AStar<Position<int>>());
        }
    }

    void run1() {
        typename vector<Matrix>::iterator it;
        for (it = matrices.begin(); it != matrices.end(); it++) {
            SearchableMatrix searchableMatrix = SearchableMatrix(&(*it).getMatrix());
            runAlgorithm(searchableMatrix, new BestFirstSearch<Position<int>>());
        }

        cout << endl;

        for (it = matrices.begin(); it != matrices.end(); it++) {
            SearchableMatrix searchableMatrix = SearchableMatrix(&(*it).getMatrix());
            runAlgorithm(searchableMatrix, new DFS<Position<int>>());
        }

        cout << endl;

        for (it = matrices.begin(); it != matrices.end(); it++) {
            SearchableMatrix searchableMatrix = SearchableMatrix(&(*it).getMatrix());
            runAlgorithm(searchableMatrix, new BFS<Position<int>>());
        }

        cout << endl;

        for (it = matrices.begin(); it != matrices.end(); it++) {
            SearchableMatrix searchableMatrix = SearchableMatrix(&(*it).getMatrix());
            runAlgorithm(searchableMatrix, new AStar<Position<int>>());
        }
        cout << endl;
    }

    void runAlgorithm(SearchableMatrix &matrix, Searcher<Position<int>> *searcher) {
        int i;
        SearchSolution<Position<int>> *solution;
        int totalVerticiesSum = 0, totalCostSum = 0;
        for (i = 0; i < EPOCHS; i++) {
            solution = searcher->search(&matrix);
            if (solution == nullptr || solution->getPath().empty()) {
                cout << -1 << "," << totalVerticiesSum / (i + 1) << endl;
                return;
            }
            totalVerticiesSum += searcher->getCount();
            totalCostSum += solution->getTotalCost();
        }

        cout << totalCostSum / EPOCHS << "," << totalVerticiesSum / EPOCHS << endl;
    }

    void writeMatricesToFile(string filename) {
        // Open file
        ofstream outfile;
        outfile.open(filename, ios::app);

        if (!outfile.is_open()) {
            throw runtime_error("Unable to open file");
        }

        outfile << matrices.size() << endl;

        typename vector<Matrix>::iterator it;
        for (it = matrices.begin(); it != matrices.end(); it++) {
            outfile << *it;
        }


        outfile.close();
    }
};

#endif //SERVER_SIDE_PROJECT_EXPIREMENT_H
