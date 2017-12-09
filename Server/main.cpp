#include <iostream>
#include "ReversiServer.h"
#define FILENAME "info configuration.txt"
using namespace std;
int main() {
    ReversiServer server(FILENAME);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    server.stop();
    return 0;
}