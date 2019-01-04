//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SERVER_H
#define SERVER_SIDE_PROJECT_SERVER_H

#include "../client/ClientHandler.h"

using namespace client_side;

namespace server_side {
    class Server {
        virtual void open(int port, ClientHandler *clientHandler) = 0;

        virtual void stop() = 0;
    };
}

#endif //SERVER_SIDE_PROJECT_SERVER_H
