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
#define LENGTH 300
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
    playerNum = 0;
}
//function connects current client user to the reversi server.
//func gets a print display as parameter.
void NetworkClient :: connectToServer(Display* display) {
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
}
//function gets a 2 integers move and deliver it to socket.
void NetworkClient :: sendMove(int x, int y) {
    //write the move that player enter
    int n = write(clientSocket, &x, sizeof(int));
    if(n == -1) {
        throw "Error writing row to socket";
    }
    if (n == 0) {
        throw "server has disconnected.";
    }
    n = write(clientSocket, &y, sizeof(int));
    if(n == -1) {
        throw "Error writing col to socket";
    }
    if (n == 0) {
        throw "server has disconnected.";
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
    if (n == 0) {
        throw "server has disconnected.";
    }
    return num;
}
//function gets 2 integers(row and column) from socket.
//returns: a struct of 2 integers(x is row, y is col).
struct Info NetworkClient :: getMove() {
    int n;
    Info newInfo;
    n = read(clientSocket, &newInfo.x, sizeof(int));
    if (n == -1) {
        throw "Error reading row from socket";
    }
    if(n == 0) {//other player disconnected
        newInfo.x = End;
    }
    n = read(clientSocket, &newInfo.y, sizeof(int));
    if (n == -1) {
        throw "Error reading col from socket";
    }
    if(n == 0) { //other player disconnected
        newInfo.y = End;
    }
    return newInfo;
}
//function sends to socket that client has no moves to play in this stage
//of the game.
void NetworkClient :: sendNoMove(){
    int noMove = NoMove;
    int n = write(clientSocket, &noMove, sizeof(int));
    if (n == -1) {
        throw "Error writing noMove to socket";
    }
    if (n == 0) {
        throw "server has disconnected.";
    }
}
//function sends from client to socket a message to end the game.
void NetworkClient :: sendEnd() {
    int end = End;
    int n = write(clientSocket, &end, sizeof(int));
    if (n == -1) {
        throw "Error writing End to socket";
    }
    if (n == 0) {
        throw "server has disconnected.";
    }
}
//function gets string name of a name of a game and operation and returns,
//the right operation to remote menu func.
string NetworkClient :: ParseOperation(int operation, string name) {
    switch(operation) {
        case 1:
            return "start " + name;
        case 2:
            return "list";
        case 3:
            return "join " + name;
        default:
            return "NotOption";
    }
}
/*
 *FUNCTION handles all of players options against remote opponet.
 * function gets display and uses it to print things to the screen.
 * function handles 1-start a game, 2-get list of games to join, 3-join game.
 * if it gets number thats not 1,2,3 it says wrong input and enter again.
 */
void NetworkClient :: MenuVsRemote(Display *display) {
    string command, roomName;
    int operation;
    bool inputILegal = true;
    connectToServer(display); //initial connection to server.
    while(inputILegal) {
        // printing client's menu before joining game
        display->printRemoteMenu();
        // get the operation of the client
        cin >> operation;
        //1 - start , 2 - list , 3 - join
        if(operation == 1 || operation == 3) {
            display->EnterNameOfGame();
            cin >> roomName;
        }
        // translating the command from a number into string
        command = ParseOperation(operation, roomName);
        if(command == "NotOption") { //client entered number > 3 or <0.
            display->printNoOption();
            continue;
        }
        // sending the command to the server
        try{
            writeToServer(command);
        } catch(const char *msg) {
            throw "Problem with sending menu command to server.";
        }
        // reading the servers answer from the socket
        try{
            command = readFromServer();
        } catch(const char *msg) {
            throw "Problem with reading menu command from server.";
        }
        // in option "join" - entering a name that isn't on the list
        if (command == "NotExist") {
            display->printNotExist();
            display->printLineDrop();
            continue;
            // in option "start" - entering a name that is already on the list
        } else if(command == "AlreadyExist") {
            display->printAlreadyExist();
            display->printLineDrop();
            continue;
        }
        // in case user entered an option not from the menu
        // if the input was legal
        string print;
        if(command == "Started") {
            playerNum = P1;
            print = "The room: " + roomName + " was created! \n";
            display->printString(print);
            display->PrintWaitForRemoteToJoin();
            inputILegal = false;
        } else if(command == "Joined") {
            playerNum = P2;
            print = "You have joined " + roomName + " room. Try to win \n";
            display->printString(print);
            inputILegal = false;
        } else { //list of games should be printed.
            print = command;
            display->printString(print);
            display->printLineDrop();
        }
    }
}
//func gets a command from menu and deliver it to the server.
void NetworkClient :: writeToServer(string command) {
    char command1[LENGTH];
    strcpy(command1, command.c_str());
    int n;
    n = write(clientSocket, &command1, sizeof(command1));
    if (n == -1) {  //error in writing to server
        throw "Error writing string command to server";
    }
}
//func reads answer from the server and returns it.
string NetworkClient :: readFromServer() {
    int n;
    char message[LENGTH];
    n = read(clientSocket, &message, sizeof(message));
    if (n == 0) {
        throw "Server disconnected";
    }
    //error in reading
    if (n == -1) {
        throw "Error reading string command from server";
    }
    string str = message;
    return str;
}
//get playerNum.
int NetworkClient ::getPlayerNum() {
    return playerNum;
}
