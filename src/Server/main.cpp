/*
 *  Created on: Nov 30,2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include <iostream>
#include "ReversiServer.h"
#define FILENAME "info configuration.txt"
using namespace std;
int main() {
    ReversiServer* server = new ReversiServer(FILENAME);
    try {
        server->start();
    } catch (const char *msg) {
        cout << "cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    server->stop();
    delete server;
    return 0;
}