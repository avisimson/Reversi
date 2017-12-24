/*
 * NetworkClient.h
 *
 *  Created on: Dec 07, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib> //for std::atoi
#include "Display.h"
using namespace std;
enum StatusForClient {
    NoMove = 100, End = 101
};
typedef struct Info {
    int x;
    int y;
}Info;
#ifndef REVERSI_NETWORKCLIENT_H
class NetworkClient {
    private:
        int port;
        int clientSocket;
        const char* ipServer;
    public:
        NetworkClient(string filename);
        ~NetworkClient() { delete ipServer; }
        void connectToServer(Display* display);
        void sendMove(int x, int y);
        void sendNoMove();
        void sendEnd();
        struct Info getMove();
        int getType();
};
#define REVERSI_NETWORKCLIENT_H

#endif //REVERSI_NETWORKCLIENT_H
