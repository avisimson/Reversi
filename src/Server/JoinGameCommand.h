/*
 *
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#ifndef REVERSI_JOINGAMECOMMAND_H
#define REVERSI_JOINGAMECOMMAND_H

#include "Command.h"
class JoinGameCommand: public Command {
public:
    JoinGameCommand(vector<Game> *listOfGames);
    bool execute(string command, string args, int client);
};

#endif //REVERSI_JOINGAMECOMMAND_H
