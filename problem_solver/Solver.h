//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SOLVER_H
#define SERVER_SIDE_PROJECT_SOLVER_H

#include "Solution.h"
#include "Searchable.h"

namespace problem_solver {
    template<class P, class S>
    class Solver {
    public:
        virtual S *solve(P *problem) = 0;

        virtual ~Solver() {}
    };
}
#endif //SERVER_SIDE_PROJECT_SOLVER_H
