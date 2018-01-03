/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#ifndef REVERSI_MAKEMOVECOMMAND_H
#define REVERSI_MAKEMOVECOMMAND_H

#include "Command.h"
enum StatusForClient {
    NoMove = 100, End = 101
};
class MakeMoveCommand: public Command {
public:
    //constructor.
    MakeMoveCommand(vector<Game> *listOfGames1);
    bool execute(string command, string args, int client);
};


#endif //REVERSI_MAKEMOVECOMMAND_H
