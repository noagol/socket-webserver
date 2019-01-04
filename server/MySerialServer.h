//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_MYSERIALSERVER_H
#define SERVER_SIDE_PROJECT_MYSERIALSERVER_H

#include "iostream"
#include "BaseServer.h"
#include "../helpers/StringHelpers.h"
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <thread>
#include <string.h>
#include "../client/MyTestClientHandler.h"
#include "../problem_solver/StringReverser.h"

using namespace client_side;
using namespace std;

namespace server_side {
    class MySerialServer : public BaseServer {
        static bool shouldStop;
    public:
        MySerialServer() : BaseServer() {}


        void open(int port, ClientHandler *clientHandler) override {
            // validate
            if (1 > port || port > 65535) {
                throw invalid_argument(format("Port value out of range: %d", port));
            }

            // Run the server in new thread
            thread serverThread(runServer, port, clientHandler);
            serverThread.detach();
        }

        void stop() override {
            shouldStop = true;
        }

        /**
         * Runs a server
         * @param port the port of the server
         * @param timesPerSecond how many time to read in a second
         * @param bindTable the bind table
         * @param symbolTable the symbol table
         */
        static void runServer(int port, ClientHandler *clientHandler) {
            int sockfd, newsockfd, portno, clilen;
            char buffer[1024];
            struct sockaddr_in serv_addr, cli_addr;
            int n;

            // First call to socket() function
            sockfd = socket(AF_INET, SOCK_STREAM, 0);

            if (sockfd < 0) {
                perror("ERROR opening socket");
                exit(1);
            }

            // Set timeout // TODO: CHECK ACCEPT ENDS
            struct timeval tv;
            tv.tv_sec = 10;  /* 150 Secs Timeout */
            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *) &tv, sizeof(struct timeval));


            // Initialize socket structure
            bzero((char *) &serv_addr, sizeof(serv_addr));

            serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr = INADDR_ANY;
            serv_addr.sin_port = htons(port);

            // Now bind the host address using bind() call.
            if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
                perror("ERROR on binding");
                close(sockfd);
                exit(1);
            }

            /** Now start listening for the clients, here process will
            go in sleep mode and will wait for the incoming connection
            **/
            listen(sockfd, 5);
            clilen = sizeof(cli_addr);

            // Update variables
            while (!shouldStop) {
                // Accept actual connection from the client
                newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen); // TODO: ADD TIMEOUT

                if (newsockfd == -1) {
                    // No one accepted
                    continue;
                }


                // Client handler
                clientHandler->handleClient(newsockfd, cout);


                // Close the socket
                if (newsockfd) {
                    close(newsockfd);
                }

                this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 200));
            }


            close(sockfd);
        }

//        void readValuesToBuffer(char *buffer, int socket) {
//            bzero(buffer, 1024);
//            int i = 0;
//            ssize_t n = 0;
//            char last = '\0';
//            while (i < 1024 && last != '\n' && n >= 0) {
//                n = read(socket, buffer + i, 1);
//                last = buffer[i];
//                i++;
//            }
//
//            if (n < 0) {
//                throw runtime_error("Error reading from socket");
//            }
//        }
    };
}

bool server_side::MySerialServer::shouldStop = false;


#endif //SERVER_SIDE_PROJECT_MYSERIALSERVER_H
