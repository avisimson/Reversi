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
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib> //for std::atoi
enum StatusForClient {
    NoMove = -2, End = -3
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
        const char* ip;
    public:
        NetworkClient(char* filename);
        ~NetworkClient() { delete ip; }
        void connectToServer();
        void sendMove(int x, int y);
        void sendNoMove();
        void sendEnd();
        struct Info getMove();
        int getType();
};
#define REVERSI_NETWORKCLIENT_H

#endif //REVERSI_NETWORKCLIENT_H
