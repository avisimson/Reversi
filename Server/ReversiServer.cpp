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
#define BUFFER_SIZE 1024
//constructor to server class, gets a port and update port in server.
//constructor initialize serverSocket into 0.
ReversiServer :: ReversiServer(int port1) {
    serverSocket = 0;
    port = port1;
    cout << "Server initialized through constructor" << endl;
}
//constructor that gets a name of a file and read the port from it.
ReversiServer ::ReversiServer(char* fileName) {
    serverSocket = 0;
    string buffer, dummyLine;
    ifstream infoAddress;
    infoAddress.open(fileName, std :: fstream :: in);
    getline(infoAddress, dummyLine);
    //dummyLine contains the first line of file.
    getline(infoAddress, buffer);
    //erase the "Port = " to get the port itself
    buffer.erase(buffer.begin(), buffer.begin() + strlen("Port = "));
    //enter to port the currect value from the file
    port = atoi(buffer.c_str());
    //close the file.
    infoAddress.close();
    cout << "Server initialized through constructor" << endl;
}
//function opens socket in server, connect client to server(throws
//exception if there is a problem in connection), and handles all communication
//between the clients until they disconnect.
void ReversiServer :: start() {
    //sockets for both clients.
    int client1_sd, client2_sd;
    char buffer[BUFFER_SIZE]; //array of messages between players.
    //clients' variables
    struct sockaddr_in client1Address, client2Address;
    socklen_t client1AddressLen, client2AddressLen;
    //cleaning buffer (put zeros in all buffer array)
    memset(&buffer[0], 0, sizeof(buffer));
    //Creating the socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) { //opening socket in server failed.
        throw "Error opening socket";
    }
    //Creating socket address variable for binding
    struct sockaddr_in serverAddress;
    //initializing it to 0's
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    //Gets connections from anything
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    //binding
    if (bind(serverSocket, (struct sockaddr *) &serverAddress,
             sizeof(serverAddress)) == -1) { //binding fail.
        throw "Error on binding";
    }
    //If a game has ended, start a new one
    while (true) {
        //start listening for clients
        listen(serverSocket, MAX_CLIENTS);
        cout << "Waiting for connections" << endl;
        //Accepting first client
        client1_sd = accept(serverSocket,
                            (struct sockaddr *) &client1Address,
                            &client1AddressLen);
        cout << "Client 1 entered!" << endl;
        //Sending 1 to him to show him he is the first to enter
        buffer[0] = '1';
        //if have problem in accept
        if(client1_sd == -1) { //client 1 connection failed.
            throw "Error on accept";
        }
        //send client 1 a message that he is player 1.
        send(client1_sd, buffer, BUFFER_SIZE, 0);
        //Accepting second client
        client2_sd = accept(serverSocket,
                            (struct sockaddr *) &client1Address,
                            &client1AddressLen);
        cout << "Client 2 entered!";
        //Sending 2 to him to show him he is the second to enter
        buffer[0] = '2';
        //if have problem in accept
        if(client2_sd == -1) { //client 2 connection failed.
            throw "Error on accept";
        }
        //send client 1 a message that he is player 2.
        send(client2_sd, buffer, BUFFER_SIZE, 0);
        int count = 0;
        while (true) { //send messages between players until game ends.
            if(count == 0) {
                int check = checkValidate(client1_sd, client2_sd, buffer);
                if(check != -1) {
                    count++;
                }
            } else if(count == 1) {
                int check = checkValidate(client2_sd, client1_sd, buffer);
                if(check != -1) {
                    count--;
                }
            }
            //if function get "end"
            if (check == 1){
                close(client1_sd);
                close(client2_sd);
                break;
            }
        }
    }
}
//function closes socket of the server that initialized in start method.
void ReversiServer :: stop() {
    close(serverSocket);
}
//function gets 2 strings of clients and a server string and connects and
//deliver messages between clients through buffer.
//messages are row, col. return 0 to continue game, 1 to end, -1 to try turn again.
int ReversiServer :: checkValidate(char* socketClient1,
                                   char* socketClient2, char *buffer) {
    int rowInput , colInput; //get from one of players and send to other player,
    char dummy; // the "," between row and col.
    //taking input form client 1
    recv(socketClient1, buffer, BUFFER_SIZE, 0);
    //if player1 see that game is over
    if (strcmp(buffer, "End") == 0) {
        return 1;
    }
        //if to player1 no moves to play , send message to player1
    else if (strcmp(buffer, "NoMove") == 0) {
        //returning the message to player 2
        send(socketClient2, buffer, BUFFER_SIZE, 0);
    }
    //check if enter "x,y" and enter right.
    //read the current row
    int n = read(clientSocket1, &rowInput, sizeof(rowInput));
    if(n == -1) { //if reading row failed.
        cout << "Error reading row" << endl;
        return -1;
    }
    if(n == 0) { //check if player 1 disconnected
        cout << "client 1 disconnected";
        return 1;
    }
    //read the current ","
    n = read(clientSocket1, &dummy, sizeof(dummy));
    if(n == -1) {
        cout << "Error reading dummy" << endl;
        return -1;
    }
    //check the current col
    n = read(clientSocket1, &colInput, sizeof(colInput));
    if(n == -1) {
        cout << "Error reading col" << endl;
        return -1;
    }
    //send the move to player2
    n = write(clientSocket2, buffer, sizeof(BUFFER_SIZE));
    if(n == -1) { //check if message send
        cout << "Error writing to socket" << endl;
        return -1;
    }
    return 0; //turn success, game continues.
}