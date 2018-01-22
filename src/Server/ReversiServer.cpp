/*
 * ReversiServer.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "ReversiServer.h"
#define THREADSSIZE 5
//constructor to server class, gets a port and update port in server.
//constructor initialize serverSocket into 0.
ReversiServer :: ReversiServer(int port1) {
    threads = new ThreadPool(THREADSSIZE);
    serverSocket = 0;
    port = port1;
    handler = new HandleClient();
    cout << "Server initialized through constructor" << endl;
}
//constructor that gets a name of a file and read the port from it.
ReversiServer :: ReversiServer(string filename) {
    threads = new ThreadPool(THREADSSIZE);
    handler = new HandleClient();
    serverSocket = 0;
    string buffer;
    ifstream config;
    config.open(filename.c_str()); //open file of ip and port
    if(!config) {
        cout << "Can't open file, aborting";
        exit(1);
    }
    while(!config.eof()) { //read every line until end of file
        config >> buffer;
        if(buffer == "Port") { // if port line
            config >> buffer;
            config >> buffer;
            port = atoi(buffer.c_str());
            return ;
        }
    }
    config.close();
    cout << "Server initialized through constructor" << endl;
}
//function opens socket in server and starts listening to clients.
//func opens threads of games and client connections to server.
void ReversiServer :: start() {
    //cleaning buffer (put zeros in all buffer array)
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
    //start listening for clients
    listen(serverSocket, MAX_CLIENTS);
    int rc = pthread_create(&mainThread,
                            NULL, &ClientConnections, (void*)this);
    if (rc) { //check if thread was created.
        cout << "Error: unable to create main thread, " << rc << endl;
        exit(-1);
    }
    string str;
    while(str != "exit") {
        cout << "Enter exit to close server" << endl;
        cin >> str;
    }
    stop();
}
//function gets ReversiServer member and connects between clients to server.
void* ReversiServer :: ClientConnections(void* server) {
    ReversiServer* rs = (ReversiServer*)server;
    //Server start on trying to connects clients and start games.
    int countOfClients = 0;
    //create a thread of connecting clients to server.
    struct Details* details = (struct Details*) malloc(sizeof(struct Details));
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    vector<Game>* vec = new vector<Game>();
    Command* commandsOfClient = new DirectorCommand(vec);
    details->commandOfClient = commandsOfClient;
    while (true) {
        cout << "Waiting for connections" << endl;
        //Accepting first client
        int client_sd = accept(rs->getServerSocket(),
                               (struct sockaddr *) &clientAddress,
                               &clientAddressLen);
        details->clientSocket = client_sd;
        countOfClients++;
        cout << "Client number " << countOfClients << " has entered!" << endl;
        //if have problem in accepting client close the server
        if (client_sd == -1) { //error accepting client-skip to next one.
            cout << "Error on accept client: " << countOfClients << endl;
            countOfClients--;
            continue;
        }
        //handle client to join/start game.
        Task* task = new Task(rs->getHandler()->InitialClientServerConversation, (void*)details);
        rs->getThreads()->addTask(task);
    }
}
//function closes/deletes all open threads, server socket and all helpers to reversi server class.
void ReversiServer :: stop() {
    threads->terminate(); //kill all threads.
    close(serverSocket); //close socket.
    pthread_cancel(mainThread); // close thread of -while true loop.
}