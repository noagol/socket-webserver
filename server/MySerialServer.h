
#ifndef SERVER_SIDE_PROJECT_MYSERIALSERVER_H
#define SERVER_SIDE_PROJECT_MYSERIALSERVER_H

#include "iostream"
#include "BaseServer.h"
#include "../helpers/StringHelpers.h"
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <thread>
#include <string.h>
#include "../client/MyTestClientHandler.h"
#include "../problem_solver/StringReverser.h"

using namespace client_side;
using namespace std;

namespace server_side {
    class MySerialServer : public BaseServer {
        static bool shouldStop;
    public:
        MySerialServer() ;

        void run(int port, ClientHandler *clientHandler) override;

        void stop() override;

        static void runServer(int port, ClientHandler *clientHandler) ;
    };
}


#endif //SERVER_SIDE_PROJECT_MYSERIALSERVER_H
