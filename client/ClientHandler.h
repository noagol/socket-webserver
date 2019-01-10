//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_CLIENTHANDLER_H
#define SERVER_SIDE_PROJECT_CLIENTHANDLER_H

#define BUFFER_SIZE 4096
#include <istream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "../helpers/StringHelpers.h"

using namespace std;

namespace client_side {
    class ClientHandler {
    public:
        virtual void handleClient(int inputSocket) = 0;
    };
}

#endif //SERVER_SIDE_PROJECT_CLIENTHANDLER_H
