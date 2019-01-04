//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SERVERTESTS_H
#define SERVER_SIDE_PROJECT_SERVERTESTS_H


#include <MySerialServer.h>

using namespace server_side;

class ServerTests {
public:
    static void simpleServer1() {
        MySerialServer server = MySerialServer();
        server.open(12345);

        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 200000000000000000));
    }
};
#endif //SERVER_SIDE_PROJECT_SERVERTESTS_H
