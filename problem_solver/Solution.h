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
#include "../helpers/StringHelpers.h"

using namespace std;

namespace problem_solver {
    template<class T>
    class Solution {
    public:
        virtual vector<State<T>> getPath() = 0;

        virtual int getTotalCost() = 0;

        friend ostream &operator<<(ostream &os, Solution &solution);

        virtual ~Solution() {}
    };
}

#endif //SERVER_SIDE_PROJECT_SOLUTION_H
