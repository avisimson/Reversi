#ifndef REVERSI_JOINGAMECOMMAND_H
#define REVERSI_JOINGAMECOMMAND_H

#include "Command.h"
class JoinGameCommand: public Command {
public:
    JoinGameCommand(vector<Game> *listOfGames);
    bool execute(string command, string args, int client);
};

#endif //REVERSI_JOINGAMECOMMAND_H
