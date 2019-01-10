//
// Created by EB on 10/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_MATRIX_H
#define SERVER_SIDE_PROJECT_MATRIX_H

#include <vector>
#include <ostream>
#include <iostream>

using namespace std;

class Matrix {
    vector<vector<int>> matrix;
public:
    Matrix(vector<vector<int>> *m) : matrix(*m) {}

    vector<vector<int>> &getMatrix() {
        return matrix;
    }

    friend ostream &operator<<(ostream &os, Matrix &m) {
        // Print size of the matrix
        os << m.matrix.at(0).size() << endl;
        // Print initial and goal state
        os << "0,0" << endl;
        os << m.matrix.at(0).size() - 1 << "," << m.matrix.size() - 1 << endl;

        // Print the matrix
        typename vector<vector<int>>::iterator it1;
        typename vector<int>::iterator it2;

        // Write rows
        for (it1 = m.matrix.begin(); it1 != m.matrix.end(); it1++) {
            for (it2 = (*it1).begin(); it2 != ((*it1).end() - 1); it2++) {
                os << *it2 << ",";
            }
            os << *it2 << endl;
        }

        return os;
    }
};


#endif //SERVER_SIDE_PROJECT_MATRIX_H
