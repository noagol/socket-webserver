//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_CLIENTHANDLER_H
#define SERVER_SIDE_PROJECT_CLIENTHANDLER_H

#include <istream>

using namespace std;

namespace client_side {
    class ClientHandler {
    public:
        virtual void handleClient(istream input, ostream output) = 0;

    };
}

#endif //SERVER_SIDE_PROJECT_CLIENTHANDLER_H
