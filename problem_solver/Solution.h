//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SOLUTION_H
#define SERVER_SIDE_PROJECT_SOLUTION_H

#include <list>
#include "State.h"

using namespace std;

namespace problem_solver {
    template<class T>
    class Solution {
        list<State<T>> path;
        int totalCost;
    public:
        virtual list<State<T>> getPath() = 0;

        virtual int getTotalCost() = 0;
    };
}

#endif //SERVER_SIDE_PROJECT_SOLUTION_H
