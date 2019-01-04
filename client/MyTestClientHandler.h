//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H
#define SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H

#include "BaseClientHandler.h"
#include "../problem_solver/Solver.h"


using namespace problem_solver;
using namespace std;

namespace client_side {
    class MyTestClientHandler : public BaseClientHandler {
        Solver<string, string> *solver;
    public:
        MyTestClientHandler(Solver<string, string> *s) : solver(s) {}

        void handleClient(int inputSocket, ostream &output) override {
            string input;

            input = readValuesToBuffer(inputSocket);
            do {
                if (input.empty()) {
                    continue;
                }

                // Change string inplace
                solver->solve(&input);

                // Print output
                output << input << endl;

                // Write back to socket
                write(inputSocket, input.c_str(), input.size());

                // Read one more line
                input = readValuesToBuffer(inputSocket);
            } while (input != "end");

            close(inputSocket);
        }


        ~MyTestClientHandler() {
            delete (solver);
        }

    };
}

#endif //SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H
