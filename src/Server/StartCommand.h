#ifndef REVERSI_STARTCOMMAND_H
#define REVERSI_STARTCOMMAND_H
#include "Command.h"
class StartCommand: public Command {
public:
    //constructor.
    StartCommand(vector<Game> *listOfGames);
    //start a new game.
    bool execute(string command, string args, int client);
};


#endif //REVERSI_STARTCOMMAND_H
