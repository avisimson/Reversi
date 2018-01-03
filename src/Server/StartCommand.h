/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#ifndef REVERSI_STARTCOMMAND_H
#define REVERSI_STARTCOMMAND_H
#include "Command.h"
class StartCommand: public Command {
    public:
        //constructor.
        StartCommand(vector<Game> *listOfGames1);
        //start a new game.
        bool execute(string command, string args, int client);
    private:
        pthread_mutex_t lock;
};


#endif //REVERSI_STARTCOMMAND_H
