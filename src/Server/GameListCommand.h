/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#ifndef REVERSI_GAMELISTCOMMAND_H
#define REVERSI_GAMELISTCOMMAND_H

#include "Command.h"
class GameListCommand: public Command {
public:
    GameListCommand(vector<Game> *listOfGames);
    bool execute(string command, string args, int client);
};


#endif //REVERSI_GAMELISTCOMMAND_H
