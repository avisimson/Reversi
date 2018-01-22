/*
 *  Created on: DEC29, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#ifndef REVERSI_HANDLECLIENT_H
#define REVERSI_HANDLECLIENT_H
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <sstream>
#include "DirectorCommand.h"
#include "GameManager.h"
using namespace std;
class HandleClient {
    public:
        HandleClient() {};
        ~HandleClient() {};
        static void* InitialClientServerConversation(void* clientID);
};
struct Details { //struct that we use in initial client server conversation method
    //to pass arguments between threads.
    int clientSocket; //client socket.
    Command* commandOfClient; //deliever command to thread.
};
#endif //REVERSI_HANDLECLIENT_H