/*
 * ReversiServer.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "ReversiServer.h"
#define MAX_CLIENTS 2
//constructor to server class, gets a port and update port in server.
//constructor initialize serverSocket into 0.
ReversiServer :: ReversiServer(int port1) {
    serverSocket = 0;
    port = port1;
}
//function opens socket in server, connect client to server(throws
//exception if there is a problem in connection), and handles all communication
//between the clients until they disconnect.
void ReversiServer :: start() {
    //create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) { //check if socket opened.
        throw "Error opening socket";
    }
    //assign a local address to the socket
    struct sockaddr_in ServerAddress;
    bzero((void*)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADOR_ANY;
    serverAddress.sin_port = htons(port);
    if(bind(serverSocket, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    //start listening to incoming connections from clients.
    listen(serverSocket, MAX_CLIENTS);
    //define the client socket's structures for client 1 and 2.
    struct sockaddr_in clientAddress1;
    struct sockaddr_in clientAddress2;
    socklen_t clientAddressLen1;
    socklen_t clientAddressLen2;
    while(true) {
        cout << "Waiting for client connections .." << endl;
        //accept a new client connection
        int clientSocket1 = accept(serverSocket, (struct
                sockaddr*)&clientAddress1, &clientAddressLen1);
        int clientSocket2 = accept(serverSocket, (struct
                sockaddr*)&clientAddress2, &clientAddressLen2);
        cout << "Client Connection";
        //check if clients success in connection.
        if (clientSocket1 == -1 || clientSocket2 == -1) {
            throw "Error on accepting clients into socket";
        }
        handleClient(clientSocket);
        //close communication of socket with the clients
        close(clientSocket1);
        close(clientSocket2);
    }
}
//function closes socket of the server that initialized in start method.
void ReversiServer :: stop() {
    close(serverSocket);
}