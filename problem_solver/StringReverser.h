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
        string solve(string problem) override {
            reverse(problem.begin(), problem.end());
            return problem;
        }

    };
}


#endif //SERVER_SIDE_PROJECT_STRINGREVERSER_H
