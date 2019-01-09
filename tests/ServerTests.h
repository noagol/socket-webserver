//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SERVERTESTS_H
#define SERVER_SIDE_PROJECT_SERVERTESTS_H


#include "../server/MyParallelServer.h"
#include "../client/MyClientHandler.h"
#include "../server/MySerialServer.h"
#include "../algorithm/AStar.h"
#include "../problem_solver/SearcherSolver.h"

using namespace problem_solver;
using namespace server_side;

class ServerTests {
public:
    static void simpleServer1() {

        MyTestClientHandler *clientHandler = new MyTestClientHandler(new StringReverser());

        MySerialServer *server = new MySerialServer();
        server->open(12346, clientHandler);
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 60000));

        server->stop();

        delete (server);
        delete (clientHandler);
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 200000000000000000));
    }

    static void parallelServer1() {
        MyTestClientHandler *clientHandler = new MyTestClientHandler(new StringReverser());

        MyParallelServer *server = new MyParallelServer();
        server->open(12346, clientHandler);
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 60000));

        server->stop();

        delete (server);
        delete (clientHandler);
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 200000000000000000));
    }


    static void parallelServer2() {
        MyClientHandler *clientHandler = new MyClientHandler(new SearcherSolver<Position<int>>(new AStar<Position<int>>()));

        MyParallelServer *server = new MyParallelServer();
        server->open(12346, clientHandler);
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 60000));

        server->stop();

        delete (server);
        delete (clientHandler);
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 200000000000000000));
    }
};

#endif //SERVER_SIDE_PROJECT_SERVERTESTS_H
