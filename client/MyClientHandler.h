//
// Created by EB on 08/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_MYCLIENTHANDLER_H
#define SERVER_SIDE_PROJECT_MYCLIENTHANDLER_H

#include "BaseClientHandler.h"
#include "../problem_solver/Solver.h"
#include "../cache/FileCacheManager.h"
#include <sys/socket.h>
#include <SearchableMatrix.h>
#include "../helpers/StringHelpers.h"
#include "../problem_solver/SearchSolution.h"


using namespace problem_solver;
using namespace std;

namespace client_side {
    class MyClientHandler : public BaseClientHandler {
        Solver<Searchable<Position<int>>, SearchSolution<Position<int>>> *solver;
        FileCacheManager<SearchSolution<Position<int>>> cacheManager;
    public:
        MyClientHandler(Solver<Searchable<Position<int>>, SearchSolution<Position<int>>> *s) : solver(s), cacheManager(
                "matrix_client_handler.txt") {}

        void handleClient(int inputSocket, ostream &output) override {
            string problem;
            string position;
            SearchSolution<Position<int>> *solution;
            string *cached;
            Position<int> initial;
            Position<int> goal;

            vector<vector<int>> matrix;
            vector<string> spl;
            typename vector<string>::iterator it;
            vector<int> row;

            // To check socket status
            int error = 0;
            socklen_t len = sizeof(error);


            // Load matrix
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
                        break;
                    }
                }
                row = vector<int>();

                matrix.push_back(row);
                spl = split(&problem, ',');
                for (it = spl.begin(); it != spl.end(); it++) {
                    matrix.at(matrix.size() - 1).push_back(stoi(*it));
                }

                problem = readValuesToBuffer(inputSocket);
            } while (problem != "end");

            // Get initial and goal position
            initial = readPosition(inputSocket);
            goal = readPosition(inputSocket);

            // Create the matrix object
            SearchableMatrix *searchableMatrix = new SearchableMatrix(&matrix, initial, goal);

            // Save as string
            ostringstream os;
            os << *searchableMatrix;
            problem = os.str();

            // Search in cache
            solution = cacheManager.find(problem);
            if (solution == nullptr) {
                // Not found on cache
                // Solve
                solution = solver->solve(searchableMatrix);
                // Add to cache
                cacheManager.add(problem, solution);
            }


            if (solution != nullptr) {
                vector<State<Position<int>> *> path = solution->getPath();
                State<Position<int>> *lastPosition = path.at(0);
                string answer;

                typename vector<State<Position<int>> *>::iterator it1;
                for (it1 = path.begin() + 1; it1 != path.end(); it1++) {
                    if (lastPosition->getState().getX() < (*it1)->getState().getX()) {
                        answer += "Right,";
                    } else if (lastPosition->getState().getX() > (*it1)->getState().getX()) {
                        answer += "Left,";
                    } else if (lastPosition->getState().getY() < (*it1)->getState().getY()) {
                        answer += "Down,";
                    } else {
                        answer += "Up,";
                    }
                    lastPosition = *it1;
                }


                if (getsockopt(inputSocket, SOL_SOCKET, SO_ERROR, &error, &len) == 0) {
                    write(inputSocket, answer.c_str(), answer.size() - 1); // TODO: Handle directions
                }

            } else {
                if (getsockopt(inputSocket, SOL_SOCKET, SO_ERROR, &error, &len) == 0) {
                    write(inputSocket, "-1", 1); // TODO: Handle directions
                }
            }


            delete (searchableMatrix);

            close(inputSocket);
        }

        Position<int> readPosition(int inputSocket) {
            // To check socket status
            int error = 0;
            socklen_t len = sizeof(error);

            // Get postion
            string position;
            vector<string> spl;

            if (getsockopt(inputSocket, SOL_SOCKET, SO_ERROR, &error, &len) == 0) {
                position = readValuesToBuffer(inputSocket);
                spl = split(&position, ',');
                return Position<int>(stoi(spl.at(0)), stoi(spl.at(1)));
            } else {
                throw invalid_argument("Socket connection was interrupted");
            }
        }

        ~MyClientHandler() {
            delete (solver);
        }

    };
}

#endif //SERVER_SIDE_PROJECT_MYCLIENTHANDLER_H
