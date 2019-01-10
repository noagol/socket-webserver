#include "MyParallelServer.h"


server_side::MyParallelServer::MyParallelServer() : BaseServer() {}

/**
* Runs a server in new thread
* @param port the port of the server
* @param clientHandler client handler
*/
void server_side::MyParallelServer::run(int port, ClientHandler *clientHandler) {
    // Run the server in new thread
    thread serverThread(runServer, port, clientHandler);
    serverThread.detach();
}

/**
 * stop server
 */
void server_side::MyParallelServer::stop() {
    shouldStop = true;
}

/**
 * Start a thread to handel clident
 * @param clientSocket
 * @param clientHandler
 */
void server_side::MyParallelServer::runThread(int clientSocket, ClientHandler *clientHandler) {
    // Run a thread to handle client
    clientHandler->handleClient(clientSocket);

    // Close the socket
    if (clientSocket) {
        close(clientSocket);
    }
}

/**
 * Runs a server
 * @param port the port of the server
 * @param clientHandler client handler
 */
void server_side::MyParallelServer::runServer(int port, ClientHandler *clientHandler) {
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
    listen(sockfd, 100);
    clilen = sizeof(cli_addr);

    thread clientThread;
    // Update variables
    while (!shouldStop) {
        // Accept actual connection from the client
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

        if (newsockfd == -1) {
            // No one accepted
            continue;
        }

        clientThread = thread(runThread, newsockfd, clientHandler);
        clientThread.detach();
    }

    close(sockfd);
}

bool server_side::MyParallelServer::shouldStop = false;

