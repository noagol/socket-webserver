//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_STRINGREVERSER_H
#define SERVER_SIDE_PROJECT_STRINGREVERSER_H

#include <string>
#include <algorithm>
#include "Solver.h"

using namespace std;

namespace problem_solver {
    class StringReverser : public Solver<string, string> {
    public:
        string *solve(string *problem) override {
            string *solution = new string();
            *solution = *problem;
            reverse(solution->begin(), solution->end());
            return solution;
        }

    };
}


#endif //SERVER_SIDE_PROJECT_STRINGREVERSER_H
