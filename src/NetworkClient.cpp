/*
 * NetworkClient.h
 *
 *  Created on: Dec 07, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "NetworkClient.h"
//constructor initialize clientSocket to 0,
// and read ip and port of server from file.
NetworkClient ::NetworkClient(char *filename) {
    clientSocket = 0;
    string portLine, ipLine;
    ifstream infoAddress;
    infoAddress.open(fileName, std :: fstream :: in); //open file.
    getline(infoAddress, ipLine); //read first line of file-the ip
    getline(infoAddress, portLine); //read second line of file-the port.
    portLine.erase(portLine.begin(), portLine.begin() + strlen("Port = "));
    ipLine.erase(ipLine.begin(), ipLine.begin() + strlen("IP = "));
    //enter to port the currect value from the file
    port = atoi(portLine.c_str());
    ip = new char[ipLine.size() + 1]; //allocate enough memory in heap to ip.
    ip = ipLine.c_str();
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
    if (!inet_aton(serverIP, &address)) { //try to convert and check if fail.
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
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr
    *)&serverAddress, sizeof(serverAddress)) == -1) {//check if client-server
        throw "Error connecting to server";         //connection fail/succeed.
    }
    cout << "Connected to server" << endl;
}
