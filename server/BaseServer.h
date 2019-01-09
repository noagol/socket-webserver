//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BASESERVER_H
#define SERVER_SIDE_PROJECT_BASESERVER_H

#include "Server.h"
#include <thread>

namespace server_side {
    class BaseServer : public Server {
    public:
        BaseServer() {}

        void open(int port, ClientHandler *clientHandler) override {
            // validate
            if (1 > port || port > 65535) {
                throw invalid_argument(format("Port value out of range: %d", port));
            }

            // Run the server
            run(port, clientHandler);
        }

        /**
         * Runs a server
         * @param port the port of the server
         * @param clientHandler client handler
         */
        virtual void run(int port, ClientHandler *clientHandler) = 0;
    };
}

#endif //SERVER_SIDE_PROJECT_BASESERVER_H
