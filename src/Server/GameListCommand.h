#ifndef REVERSI_GAMELISTCOMMAND_H
#define REVERSI_GAMELISTCOMMAND_H

#include "Command.h"
class GameListCommand: public Command {
public:
    GameListCommand(vector<Game> *listOfGames);
    bool execute(string command, string args, int client);
};


#endif //REVERSI_GAMELISTCOMMAND_H
