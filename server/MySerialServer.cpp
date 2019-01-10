#include "MySerialServer.h"

namespace server_side {

    MySerialServer::MySerialServer() : BaseServer() {}

    /**
     * Runs a server
     * @param port the port of the server
     * @param timesPerSecond how many time to read in a second
     * @param bindTable the bind table
     * @param symbolTable the symbol table
     */
    void MySerialServer::runServer(int port, ClientHandler *clientHandler) {
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

        // Set timeout
        struct timeval tv;
        tv.tv_sec = 150;  /* 150 Secs Timeout */
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
            newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

            if (newsockfd == -1) {
                // No one accepted
                continue;
            }


            // Client handler
            try {
                clientHandler->handleClient(newsockfd, cout);
            } catch (exception &ex) {
                cout << ex.what() << endl;
            }


            // Close the socket
            if (newsockfd) {
                close(newsockfd);
            }

            this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 200));
        }


        close(sockfd);
    }

}

bool server_side::MySerialServer::shouldStop = false;

/**
 * Run a client in a new thread
 * @param port
 * @param clientHandler
 */
void server_side::MySerialServer::run(int port, ClientHandler *clientHandler) {
    // Run the server in new thread
    thread serverThread(runServer, port, clientHandler);
    serverThread.detach();
}

/**
 * stop sever
 */
void server_side::MySerialServer::stop() {
    shouldStop = true;
}