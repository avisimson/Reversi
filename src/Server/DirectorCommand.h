/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#ifndef REVERSI_DIRECTORCOMMAND_H
#define REVERSI_DIRECTORCOMMAND_H

#include <map>
#include "StartCommand.h"
#include "CloseCommand.h"
#include "GameListCommand.h"
#include "JoinGameCommand.h"
#include "MakeMoveCommand.h"
class DirectorCommand: public Command {
public:
    DirectorCommand(vector<Game> *listOfGames);
    ~DirectorCommand();
    bool execute(string command, string args, int client);
private:
    map<string, Command*> commandsMap;
};


#endif //REVERSI_DIRECTORCOMMAND_H
