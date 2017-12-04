/*
 * ReversiServer.h
 *
 *  Created on: Nov 30, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
//libraries to use Server
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ReversiGame.h"
#ifndef SERVER_REVERSISERVER_H
//class is a server between 2 remote players in ReversiGame in Reversi Project.
class ReversiServer {
    private:
        int port; //number in server we connect to.
        int serverSocket; //tells if connection is successfull and why if not.
        void handleReversiClient(int clientSocket);
    public:
        ReversiServer(int port);
        ~ReversiServer() {};
        void start();
        void stop();
};
#define SERVER_REVERSISERVER_H

#endif //SERVER_REVERSISERVER_H