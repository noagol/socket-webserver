

#ifndef SERVER_SIDE_PROJECT_BASESERVER_H
#define SERVER_SIDE_PROJECT_BASESERVER_H

#include "Server.h"
#include <thread>

namespace server_side {
    class BaseServer : public Server {
    public:
        BaseServer() {}

        void open(int port, ClientHandler *clientHandler) override;

        /**
         * Runs a server
         * @param port the port of the server
         * @param clientHandler client handler
         */
        virtual void run(int port, ClientHandler *clientHandler) = 0;
    };
}

#endif //SERVER_SIDE_PROJECT_BASESERVER_H
