//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H
#define SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H

#include "BaseClientHandler.h"
#include "../problem_solver/Solver.h"
#include "../cache/FileCacheManager.h"
#include <sys/socket.h>

using namespace problem_solver;
using namespace std;

namespace client_side {
    class MyTestClientHandler : public BaseClientHandler {
        Solver<string, string> *solver;
        FileCacheManager<string> cacheManager;
    public:
        MyTestClientHandler(Solver<string, string> *s);

        void handleClient(int inputSocket) override;

        ~MyTestClientHandler();
    };
}

#endif //SERVER_SIDE_PROJECT_MYTESTCLIENTHANDLER_H
