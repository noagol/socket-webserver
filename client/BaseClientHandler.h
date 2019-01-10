//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BASECLIENTHANDLER_H
#define SERVER_SIDE_PROJECT_BASECLIENTHANDLER_H

#include "ClientHandler.h"

namespace client_side {
    class BaseClientHandler : public ClientHandler {
    public:
        BaseClientHandler();

        string readValuesToBuffer(int socket);
    };
}

#endif //SERVER_SIDE_PROJECT_BASECLIENTHANDLER_H
