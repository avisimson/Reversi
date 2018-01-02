/*
 * ReversiServer.h
 *
 *  Created on: Nov 30, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
//libraries to use Server and reading from file.
#include <pthread.h>
#include <cmath>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib> //for std::atoi
#include "HandleClient.h"
#define MAX_CLIENTS 100
using namespace std;
#ifndef SERVER_REVERSISERVER_H
//class is a server between 2 remote players in ReversiGame in Reversi Project.
class ReversiServer {
    private:
        int port; //number in server we connect to.
        int serverSocket; //tells if connection is successfull and why if not.
        pthread_t threads[MAX_CLIENTS / 2];
        pthread_t mainThread;
        HandleClient* handler;
    public:
        ReversiServer(int port);
        ReversiServer(string fileName);
        ~ReversiServer() {};
        void start();
        void stop();
        static void *ClientConnections(void* server);
        int getServerSocket() {return serverSocket;}
        pthread_t* getThreadsOfGames() {return threads;}
        HandleClient* getHandler() {return handler;}
};
#define SERVER_REVERSISERVER_H

#endif //SERVER_REVERSISERVER_H