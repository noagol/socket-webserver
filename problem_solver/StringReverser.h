
#ifndef SERVER_SIDE_PROJECT_STRINGREVERSER_H
#define SERVER_SIDE_PROJECT_STRINGREVERSER_H

#include <string>
#include <algorithm>
#include "Solver.h"

using namespace std;

namespace problem_solver {
    class StringReverser : public Solver<string, string> {
    public:
        string *solve(string *problem) override ;
    };
}


#endif //SERVER_SIDE_PROJECT_STRINGREVERSER_H
