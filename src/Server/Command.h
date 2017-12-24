#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H

#include <vector>
#include <string>
#include <ReversiServer.h>
using namespace std;
class Command {
public:
    // global function of execute actions that needs for the server
    virtual void execute(vector<string> args) = 0;
    //destructor
    virtual ~Command() {}
};


#endif //REVERSI_COMMAND_H
