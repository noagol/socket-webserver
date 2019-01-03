//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_MYSERIALSERVER_H
#define SERVER_SIDE_PROJECT_MYSERIALSERVER_H

#include "BaseServer.h"

namespace server_side {
    class MySerialServer : public BaseServer {
        MySerialServer() : BaseServer() {}

        void open(int port) override {

        }

        void stop() override {

        }
    };
}

#endif //SERVER_SIDE_PROJECT_MYSERIALSERVER_H
