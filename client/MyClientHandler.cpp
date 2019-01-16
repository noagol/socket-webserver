#include "MyClientHandler.h"

namespace client_side {
    /**
     * A client handler for matrix and fastest route problem
     * @param s solver object
     */
    MyClientHandler::MyClientHandler(Solver<Searchable<Position<int>>, SearchSolution<Position<int>>> *s) :
            solver(s), cacheManager("matrix_client_handler.txt") {}

    /**
     * Handle client request
     * @param inputSocket input socket of client
     * @param output output stream
     */
    void MyClientHandler::handleClient(int inputSocket) {
        string problem;
        string position;
        SearchSolution<Position<int>> *solution;
        Position<int> initial;
        Position<int> goal;

        vector<vector<int>> matrix;
        vector<string> spl;
        vector<string> lines;
        typename vector<string>::iterator it1, it2;
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
                    // Socket is dead
                    close(inputSocket);
                    return;
                }
            }

            // Add to lines vector
            lines.push_back(problem);

            // Read another line
            problem = readValuesToBuffer(inputSocket);
        } while (problem != "end");


        // Cast each row in the matrix
        for (it1 = lines.begin(); it1 != lines.end() - 2; it1++) {
            // Add row to matrix
            row = vector<int>();
            spl = split(&(*it1), ',');
            for (it2 = spl.begin(); it2 != spl.end(); it2++) {
                row.push_back(stoi(*it2));
            }
            matrix.push_back(row);
        }

        // Get initial and goal position
        initial = readPosition(*it1);
        goal = readPosition(*(it1+1));

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
            // There is a solution
            string answer = getPathMovements(solution);
            if (getsockopt(inputSocket, SOL_SOCKET, SO_ERROR, &error, &len) == 0) {
                write(inputSocket, answer.c_str(), answer.size() - 1);
            }
        } else {
            // No solution found
            if (getsockopt(inputSocket, SOL_SOCKET, SO_ERROR, &error, &len) == 0) {
                write(inputSocket, "-1", 1);
            }
        }

        // Free allocated memory
        delete (searchableMatrix);
        // Close the socket
        close(inputSocket);
    }

    /**
     * Returns movement directions from a solution
     * @param solution given solution
     * @return "Up Down Left Left" etc..
     */
    string MyClientHandler::getPathMovements(SearchSolution<Position<int>> *solution) {
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

        return answer;
    }

    /**
     * Read a position from socket
     * @param inputSocket input socket
     * @return position
     */
    Position<int> MyClientHandler::readPosition(string &position) {
        // Get postion
        vector<string> spl;

        spl = split(&position, ',');
        return {stoi(spl.at(1)), stoi(spl.at(0))};
    }

    /**
     * Free solver allocated memory
     */
    MyClientHandler::~MyClientHandler() {
        delete (solver);
    }
}