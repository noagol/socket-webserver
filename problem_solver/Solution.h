//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SOLUTION_H
#define SERVER_SIDE_PROJECT_SOLUTION_H

#include <list>
#include "State.h"
#include "string"
#include "ostream"
#include "vector"

using namespace std;

namespace problem_solver {
    template<class T>
    class Solution {
        vector<State<T>> path;
        int totalCost;
    public:
        virtual vector<State<T>> getPath() = 0;

        virtual int getTotalCost() = 0;

        friend ostream &operator<<(ostream &os, Solution &solution) {
            vector<State<T>> solPath = solution.getPath();
            typename vector<State<T>>::iterator it;
            for (it = solPath.begin(); it != solPath.end(); it++) {
                os << (*it).getCost() << "|";
            }
            os << endl;

            return os;
        }

        virtual ~Solution() {

        }
    };
}

#endif //SERVER_SIDE_PROJECT_SOLUTION_H
