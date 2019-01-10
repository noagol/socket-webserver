
#include "BaseClientHandler.h"

namespace client_side {
    /**
     * Base class for client handlers
     */
    BaseClientHandler::BaseClientHandler() {}

    /**
     * Read values until new line character
     * @param socket input socket
     * @return line read from socket
     */
    string BaseClientHandler::readValuesToBuffer(int socket) {
        // Buffer
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        int i = 0;
        ssize_t n = 0;
        char last = '\0';

        // Read until new line
        while (i < BUFFER_SIZE && last != '\n' && n >= 0) {
            n = read(socket, buffer + i, 1);
            last = buffer[i];
            i++;
        }

        // Unable to read from socket
        if (n < 0  && i > 1) {
            throw runtime_error("Error reading from socket");
        }

        // Return the striped buffer string
        return strip(string(buffer));
    }
}