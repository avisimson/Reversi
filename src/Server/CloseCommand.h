/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#ifndef REVERSI_CLOSECOMMAND_H
#define REVERSI_CLOSECOMMAND_H

#include "Command.h"
#include <unistd.h>
#include <iostream>
class CloseCommand: public Command {
public:
    //constructor of close command
    CloseCommand(vector<Game> *listOfGames1);
    //function the execute the command
    bool execute(string command, string args, int client);

};


#endif //REVERSI_CLOSECOMMAND_H
