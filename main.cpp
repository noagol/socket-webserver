#include <iostream>
#include <MySerialServer.h>

#include "tests/AlgorithmTests.h"
#include "tests/ServerTests.h"

using namespace server_side;

int main() {
//    AlgorithmTests::bestFirstSearch1();
//    ServerTests::simpleServer1();

    State<Position<int>> state = State<Position<int>>(Position<int>(5, 5), 20, nullptr);

//    State<string> state = State<string>("abcd", 20, nullptr);

    cout << state << endl;
    return 0;
}