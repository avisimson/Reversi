/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "DirectorCommand.h"
//constructor-initializes all command options in this command.
DirectorCommand :: DirectorCommand(vector<Game> *listOfGames1) {
    listOfGames = listOfGames1;
    commandsMap["start"] = new StartCommand(listOfGames);
    commandsMap["close"] = new CloseCommand(listOfGames);
    commandsMap["list"] = new GameListCommand(listOfGames);
    commandsMap["join"] = new JoinGameCommand(listOfGames);
    commandsMap["play"] = new MakeMoveCommand(listOfGames);
}
//function gets a command and a name of a game and a socket of client.
//command executes the command by the map of the class with string command.
bool DirectorCommand :: execute(string command, string args, int client) {
    Command *commandObj = commandsMap[command]; //understand which command we are in.
    bool answer = commandObj->execute(command, args, client); //execute.
    return answer;
}
//destructor, delete all from heap.
DirectorCommand :: ~DirectorCommand() {
    map<string, Command *> :: iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}