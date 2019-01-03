//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H
#define SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H

#include "BaseClientHandler.h"
#include "../problem_solver/Solver.h"

using namespace problem_solver;

namespace client_side {
    class MyTestClientHandler : public BaseClientHandler {
        Solver *solver;
    public:
        MyTestClientHandler(Solver *s) : solver(s) {}

        void handleClient(istream input, ostream output) override {

        }

        ~MyTestClientHandler() {
            delete (solver);
        }
    };
}

#endif //SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H
