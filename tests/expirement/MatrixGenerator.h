//
// Created by EB on 10/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_MATRIXGENERATOR_H
#define SERVER_SIDE_PROJECT_MATRIXGENERATOR_H

#include <vector>
#include <random>
#include "Matrix.h"

using namespace std;

class MatrixGenerator {
    int n;
    int m;
public:
    MatrixGenerator(int rowNum, int columnNum) : n(rowNum), m(columnNum) {}

    Matrix generate(int rangeStart = -1, int rangeEnd = 30) {
        vector<vector<int>> matrix;
        int i, j;

        for (i = 0; i < n; i++) {
            vector<int> v;
            for (j = 0; j < m; j++) {
                v.push_back(randomInt(rangeStart, rangeEnd));
            }
            matrix.push_back(v);
        }

        return (Matrix) &matrix;
    }

    int randomInt(int rangeStart, int rangeEnd) {
        // obtain a random number from hardware
        std::random_device rd;
        // seed the generator
        std::mt19937 eng(rd());
        // define the range
        std::uniform_int_distribution<> distr(rangeStart, rangeEnd);

        return distr(eng);
    }
};


#endif //SERVER_SIDE_PROJECT_MATRIXGENERATOR_H
