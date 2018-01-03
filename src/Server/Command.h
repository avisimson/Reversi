/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H

#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;
enum StatusOfClientInGame {
    Active = 0, Waiting = 1
};
//struct that splits server into number of games. each game has a name,
// 2 sockets and a status.
struct Game {
    string name;
    int socket1;
    int socket2;
    StatusOfClientInGame status;
};
class Command {
protected: //all of the classes that include this interface will use this vector.
    vector<Game> *listOfGames;
public:
    
    // global function of execute actions that needs for the server
    virtual bool execute(string command, string args, int client) = 0;
    vector<Game>* getListOfGames() { return listOfGames;}
    //destructor
    virtual ~Command() {}
};


#endif //REVERSI_COMMAND_H
