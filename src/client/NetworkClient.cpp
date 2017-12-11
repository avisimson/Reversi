/*
 * NetworkClient.h
 *
 *  Created on: Dec 07, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include <string.h>
#include "NetworkClient.h"
//constructor initialize clientSocket to 0,
//
// and read ip and port of server from file.
NetworkClient :: NetworkClient(string filename) {
    clientSocket = 0;
    string portLine, ipLine;
    ifstream infoAddress;
    infoAddress.open(filename.c_str()); //open file.
    getline(infoAddress, ipLine); //read first line of file-the ip
    getline(infoAddress, portLine); //read second line of file-the port.
    portLine.erase(portLine.begin(), portLine.begin() + strlen("Port = "));
    ipLine.erase(ipLine.begin(), ipLine.begin() + strlen("IP = "));
    //enter to port the currect value from the file
    port = atoi(portLine.c_str());
    char* c = new char[ipLine.size() + 1]; //allocate enough memory in heap to ip.
    strcpy(c, ipLine.c_str());
    ipServer = c;
    infoAddress.close(); //close the file.
}
//function connects current client user to the reversi server.
void NetworkClient :: connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0); //trying to connect.
    if (clientSocket == -1) { //check if fail.
        throw "Error opening socket-client.";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(ipServer, &address)) { //try to convert and check if fail.
        throw "Can't parse IP address-client";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
    if (server == NULL) { //check if there is a server problem.
        throw "Host is unreachable-client.";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *)&address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr,
           (char*)server->h_addr, server->h_length);
    // htons converts values between host and network byte orders.
    serverAddress.sin_port = htons(port);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr
    *)&serverAddress, sizeof(serverAddress)) == -1) {//check if client-server
        throw "Error connecting to server";         //connection fail/succeed.
    }
    cout << "Connected to server" << endl;
    cout << "Waiting for other player to join " << endl;
}
//function gets a 2 integers move and deliver it to socket.
void NetworkClient :: sendMove(int x, int y) {
    //write the move that player enter
    int n = write(clientSocket, &x, sizeof(int));
    if(n == -1) {
        throw "Error writing row to socket";
    }
    n = write(clientSocket, &y, sizeof(int));
    if(n == -1) {
        throw "Error writing col to socket";
    }
}
//function gets information if player is player1 or player2.
int NetworkClient :: getType() {
    int n;
    int num;
    n = read(clientSocket, &num, sizeof(int));
    if (n == -1) {
        throw "Error reading player type from socket";
    }
    return num;
}
//function gets 2 integers(row and column) from socket.
//returns: a struct of 2 integers(x is row, y is col).
struct Info NetworkClient :: getMove() {
    int n;
    Info newInfo;
    n = read(clientSocket, &newInfo.x, sizeof(int));
    cout << newInfo.x << endl;
    if (n == -1) {
        throw "Error reading row from socket";
    }
    n = read(clientSocket, &newInfo.y, sizeof(int));
    if (n == -1) {
        throw "Error reading col from socket";
    }
    return newInfo;
}
//function sends to socket that client has no moves to play in this stage
//of the game.
void NetworkClient :: sendNoMove(){
    int noMove = NoMove;
    cout <<"sent" << endl;
    int n = write(clientSocket, &noMove, sizeof(int));
    if (n == -1) {
        throw "Error writing noMove to socket";
    }
    n = write(clientSocket, &noMove, sizeof(int));
    if (n == -1) {
        throw "Error writing noMove to socket";
    }
}
//function sends from client to socket a message to end the game.
void NetworkClient :: sendEnd() {
    int end = End;
    int n = write(clientSocket, &end, sizeof(int));
    if (n == -1) {
        throw "Error writing End to socket";
    }
    n = write(clientSocket, &end, sizeof(int));
    if (n == -1) {
        throw "Error writing End to socket";
    }
}