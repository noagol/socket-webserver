#include "BaseServer.h"

/**
 * Open a new sever
 * @param port - port number
 * @param clientHandler - handel client request
 */
void server_side::BaseServer::open(int port, ClientHandler *clientHandler) {
    // validate
    if (1 > port || port > 65535) {
        throw invalid_argument(format("Port value out of range: %d", port));
    }

    // Run the server
    run(port, clientHandler);
}



