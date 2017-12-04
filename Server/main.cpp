#include <iostream>
#include "ReversiServer.h"
#define PORT 5437
using namespace std;
int main() {
    ReversiServer server(PORT);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    return 0;
}