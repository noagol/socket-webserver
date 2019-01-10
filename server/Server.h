
#ifndef SERVER_SIDE_PROJECT_SERVER_H
#define SERVER_SIDE_PROJECT_SERVER_H

#include "../client/ClientHandler.h"

using namespace client_side;

namespace server_side {
    /**
     * Server interface
     */
    class Server {
        /**
        * Open a new sever
        * @param port - port number
        * @param clientHandler - handel client request
        */
        virtual void open(int port, ClientHandler *clientHandler) = 0;

        /**
         * stop server
         */
        virtual void stop() = 0;
    };
}

#endif //SERVER_SIDE_PROJECT_SERVER_H
