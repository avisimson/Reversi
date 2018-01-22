/*
 * ReversiServer.h
 *
 *  Created on: Nov 30, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#define MAX_CLIENTS 2000
using namespace std;
#ifndef SERVER_REVERSISERVER_H
#define SERVER_REVERSISERVER_H
//libraries to use Server and reading from file.
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
#include "ThreadPool.h"
//class is a server between 2 remote players in ReversiGame in Reversi Project.
class ReversiServer {
private:
    int port; //number in server we connect to.
    int serverSocket; //tells if connection is successfull and why if not.
    ThreadPool* threads;
    pthread_t mainThread;
    HandleClient* handler;
public:
    ReversiServer(int port);
    ReversiServer(string fileName);
    ~ReversiServer() {};
    ThreadPool* getThreads() { return threads;}
    void start();
    void stop();
    static void *ClientConnections(void* server);
    int getServerSocket() {return serverSocket;}
    HandleClient* getHandler() {return handler;};
    void CloseThread(vector<pthread_t>* threads, pthread_t* currentThread);
};
#endif //SERVER_REVERSISERVER_H