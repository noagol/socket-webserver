#include "MyParallelServer.h"


server_side::MyParallelServer::MyParallelServer() : BaseServer() {}

/**
* Runs a server in new thread
* @param port the port of the server
* @param clientHandler client handler
*/
void server_side::MyParallelServer::run(int port, ClientHandler *clientHandler) {
    // Run the server in new thread
    thread *serverThread = new thread(runServer, port, clientHandler);
    mainThreads.push_back(serverThread);
}

/**
 * Stop server
 */
void server_side::MyParallelServer::stop() {
    shouldStop = true;

    typename vector<thread *>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++) {
        if ((*it)->joinable()) {
            (*it)->join();
        }
        delete (*it);
    }

    for (it = mainThreads.begin(); it != mainThreads.end(); it++) {
        if ((*it)->joinable()) {
            (*it)->join();
        }
        delete (*it);
    }
}

/**
 * Join all threads
 */
void server_side::MyParallelServer::joinClientThreads() {
    typename vector<thread *>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++) {
        (*it)->join();
    }
}

/**
 * Join all threads
 */
void server_side::MyParallelServer::joinMainThreads() {
    typename vector<thread *>::iterator it;
    for (it = mainThreads.begin(); it != mainThreads.end(); it++) {
        (*it)->join();
    }
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
    int sockfd, newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;

    // First call to socket() function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

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
    listen(sockfd, SOMAXCONN);
    clilen = sizeof(cli_addr);

    thread *clientThread;

    // Accept first client
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (newsockfd != -1) {
        // No one accepted
        clientThread = new thread(runThread, newsockfd, clientHandler);
        MyParallelServer::threads.push_back(clientThread);
    }

    // Set timeout
    struct timeval tv;
    tv.tv_sec = 1;  /* 1 Secs Timeout */
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *) &tv, sizeof(struct timeval));

    // Update variables
    while (!shouldStop) {
        // Accept actual connection from the client
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

        if (newsockfd == -1) {
            // No one accepted
            break;
        }

        // Handle client
        clientThread = new thread(runThread, newsockfd, clientHandler);
        MyParallelServer::threads.push_back(clientThread);
    }

    // Wait for client threads
    joinClientThreads();

    // Close the socket
    close(sockfd);
}

bool server_side::MyParallelServer::shouldStop = false;

vector<thread *> server_side::MyParallelServer::threads = vector<thread *>();
vector<thread *> server_side::MyParallelServer::mainThreads = vector<thread *>();
