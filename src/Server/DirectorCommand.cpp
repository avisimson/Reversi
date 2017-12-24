#include "DirectorCommand.h"
#include "Command.h"
#include "StartCommand.h"
#include "CloseCommand.h"
#include "GameListCommand.h"
#include "JoinGameCommand.h"
#include "MakeMoveCommand.h"
//constructor initialize list of games and a map of commands to specific socket.
CommandsManager::CommandsManager(vector<Game> &listOfGames, int socket):
        socket(socket), listOfGames(listOfGames) {
    commandsMap["start"] = new StartCommand(listOfGames, socket);
    commandsMap["close"] = new CloseCommand(listOfGames, socket);
    commandsMap["list_games"] = new GameListCommand(listOfGames, socket);
    commandsMap["join"] = new JoinGameCommand(listOfGames, socket);
    commandsMap["play"] = new MakeMoveCommand(listOfGames, socket);
}
//func get a command and execute it.
void CommandsManager :: executeCommand(string
                                     command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}
//destructor-kills all commands.
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}
