

#ifndef SERVER_SIDE_PROJECT_MYPARALLELSERVER_H
#define SERVER_SIDE_PROJECT_MYPARALLELSERVER_H

#include "iostream"
#include "BaseServer.h"
#include "../helpers/StringHelpers.h"
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "../client/MyTestClientHandler.h"
#include "../problem_solver/StringReverser.h"

using namespace client_side;
using namespace std;

namespace server_side {
    class MyParallelServer : public BaseServer {
        static bool shouldStop;
        static vector<thread *> threads;
        static vector<thread *> mainThreads;
    public:
        MyParallelServer();

        void run(int port, ClientHandler *clientHandler) override;

        void stop() override;

        static void joinClientThreads();

        static void joinMainThreads();

        static void runThread(int clientSocket, ClientHandler *clientHandler);

        static void runServer(int port, ClientHandler *clientHandler);
    };
}


#endif //SERVER_SIDE_PROJECT_MYPARALLELSERVER_H
