/*
 * ReversiServer.h
 *
 *  Created on: Nov 30, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
//libraries to use Server and reading from file.
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib> //for std::atoi
using namespace std;
enum StatusForServer {
    NoMove = -2, End = -3
};
#ifndef SERVER_REVERSISERVER_H
//class is a server between 2 remote players in ReversiGame in Reversi Project.
class ReversiServer {
    private:
        int port; //number in server we connect to.
        int serverSocket; //tells if connection is successfull and why if not.
        bool endGame;
    public:
        ReversiServer(int port);
        ReversiServer(string fileName);
        ~ReversiServer() {};
        void start();
        void stop();
        int checkValidate(int socketClient1, int socketClient2);
        bool isClientClosed(int clientSocket1, int ClientSocket2);
};
#define SERVER_REVERSISERVER_H

#endif //SERVER_REVERSISERVER_H