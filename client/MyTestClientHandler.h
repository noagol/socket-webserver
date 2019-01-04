//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H
#define SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H

#include "BaseClientHandler.h"
#include "../problem_solver/Solver.h"
#include "../cache/FileCacheManager.h"


using namespace problem_solver;
using namespace std;

namespace client_side {
    class MyTestClientHandler : public BaseClientHandler {
        Solver<string, string> *solver;
        FileCacheManager<string> cacheManager;
    public:
        MyTestClientHandler(Solver<string, string> *s) : solver(s), cacheManager("test_client_handler.txt") {}

        void handleClient(int inputSocket, ostream &output) override {
            string problem;
            string *solution;
            string *cached;
            problem = readValuesToBuffer(inputSocket);
            do {
                if (problem.empty()) {
                    write(inputSocket, "-", 1);
                    problem = readValuesToBuffer(inputSocket);
                    continue;
                }

                // Search in cache
                solution = cacheManager.find(problem);
                if (solution == nullptr) {
                    // Not found on cache
                    // Solve
                    solution = solver->solve(&problem);
                    // Add to cache
                    cacheManager.add(problem, solution);
                }

                // Print output
                output << problem << "|" << *solution << endl;

                // Write back to socket
                write(inputSocket, solution->c_str(), solution->size());

                // Read one more line
                problem = readValuesToBuffer(inputSocket);
            } while (problem != "end");

            close(inputSocket);
        }


        ~MyTestClientHandler() {
            delete (solver);
        }

    };
}

#endif //SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H
