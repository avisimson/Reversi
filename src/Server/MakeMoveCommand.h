#ifndef REVERSI_MAKEMOVECOMMAND_H
#define REVERSI_MAKEMOVECOMMAND_H

#include "Command.h"
class MakeMoveCommand: public Command {
public:
    //constructor.
    MakeMoveCommand(vector<Game> *listOfGames1);
    bool execute(string command, string args, int client);
};


#endif //REVERSI_MAKEMOVECOMMAND_H
