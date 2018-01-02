#include "DirectorCommand.h"
//constructor-initializes all command options in this command.
DirectorCommand :: DirectorCommand(vector<Game> *listOfGames) {
    commandsMap["start"] = new StartCommand(listOfGames);
    commandsMap["close"] = new CloseCommand(listOfGames);
    commandsMap["list_games"] = new GameListCommand(listOfGames);
    commandsMap["join"] = new JoinGameCommand(listOfGames);
    commandsMap["play"] = new MakeMoveCommand(listOfGames);
}
//function gets a command and a name of a game and a socket of client.
//command executes the command by the map of the class with string command.
bool DirectorCommand :: execute(string command, string args, int client) {
    Command *commandObj = commandsMap[command]; //understand which command we are in.
    commandObj->execute(command, args, client); //execute.
    return true;
}
//destructor, delete all from heap.
DirectorCommand :: ~DirectorCommand() {
    map<string, Command *> :: iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}
