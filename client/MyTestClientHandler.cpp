#include "MyTestClientHandler.h"

namespace client_side {
    /**
     * Solves a string problem
     * @param s solver on the heap
     */
    MyTestClientHandler::MyTestClientHandler(Solver<string, string> *s) : solver(s),
                                                                          cacheManager("test_client_handler.txt") {}

    /**
     * Solve a string problem
     * @param inputSocket input
     */
    void MyTestClientHandler::handleClient(int inputSocket) {
        string problem;
        string *solution;

        // To check socket status
        int error = 0;
        socklen_t len = sizeof(error);

        // Receive first problem
        if (getsockopt(inputSocket, SOL_SOCKET, SO_ERROR, &error, &len) == 0) {
            problem = readValuesToBuffer(inputSocket);
        }
        do {
            if (problem.empty()) {
                if (getsockopt(inputSocket, SOL_SOCKET, SO_ERROR, &error, &len) == 0) {
                    write(inputSocket, "-", 1);
                    problem = readValuesToBuffer(inputSocket);
                    continue;
                } else {
                    close(inputSocket);
                    return;
                }
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
            cout << problem << "|" << *solution << endl;

            // Write back to socket
            write(inputSocket, solution->c_str(), solution->size());

            // Read one more line
            if (getsockopt(inputSocket, SOL_SOCKET, SO_ERROR, &error, &len) == 0) {
                problem = readValuesToBuffer(inputSocket);
            } else {
                break;
            }
        } while (problem != "end");

        // Close input socket
        close(inputSocket);
    }

    /**
     * Free solver allocated memory
     */
    MyTestClientHandler::~MyTestClientHandler() {
        delete (solver);
    }

}