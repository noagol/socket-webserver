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
        virtual void handleClient(int inputSocket, ostream& output) = 0;

        string readValuesToBuffer(int socket) {
            char buffer[BUFFER_SIZE];
            bzero(buffer, BUFFER_SIZE);
            int i = 0;
            ssize_t n = 0;
            char last = '\0';
            while (i < BUFFER_SIZE && last != '\n' && n >= 0) {
                n = read(socket, buffer + i, 1);
                last = buffer[i];
                i++;
            }

            if (n < 0  && i > 1) {
                throw runtime_error("Error reading from socket");
            }

            return strip(string(buffer));
        }
    };
}

#endif //SERVER_SIDE_PROJECT_CLIENTHANDLER_H
