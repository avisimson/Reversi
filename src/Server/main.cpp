#include <iostream>
#include "ReversiServer.h"
using namespace std;
int main() {
    ReversiServer server("info configuration.txt");
    try {
        server.start();
    } catch (const char *msg) {
        cout << "cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    return 0;
}