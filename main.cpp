#include <iostream>
#include "helpers/StringHelpers.h"
#include "server/MyParallelServer.h"
#include "client/MyClientHandler.h"
#include "problem_solver/SearcherSolver.h"
#include "algorithm/AStar.h"


using namespace server_side;

int main(int argc, char **argv) {
    // Validate
    if (argc != 2) {
        throw invalid_argument(format("Invalid number of arguments to "
                                      "main given. Expected 1 given %d", argc - 1));
    }

    MyClientHandler *clientHandler = new MyClientHandler(
            new SearcherSolver<Position<int>>(new AStar<Position<int>>()));

    MyParallelServer *server = new MyParallelServer();
    server->open(atoi(argv[1]), clientHandler);

    // Wait for all threads to finish
    MyParallelServer::joinMainThreads();

    cout << "Terminating the server" << endl;
    // Stop running threads
    server->stop();

    delete (server);
    delete (clientHandler);

    cout << "Server successfully terminated" << endl;

//    Set<Position<int>, State<Position<int>>*> s;
//
//    Position<int> a = Position<int>(5, 5);
//    Position<int> b = Position<int>(6, 5);
//    Position<int> c = Position<int>(5, 5);
//    Position<int> d = Position<int>(4, 5);
//    Position<int> e = Position<int>(3, 3);
//    Position<int> f = Position<int>(3, 3);
//
//    State<Position<int>> *state = new State<Position<int>>(a, 10, nullptr);
//
//    s.insert(a, state);
//    s.insert(b, state);
//    s.insert(c, state);
//    s.insert(a, state);
//    s.insert(b, state);
//    s.insert(c, state);
//
//    s.insert(d, state);
//    s.insert(e, state);
//    s.insert(f, state);


//    AlgorithmTests::test();


//    AlgorithmTests::loadTest1();

//    ServerTests::simpleServer1();
//    ServerTests::parallelServer1();
//    ServerTests::parallelServer2();

//    Expirement e = Expirement();
//    e.writeMatricesToFile("graphs.txt");
//    e.run();
    return 0;
}