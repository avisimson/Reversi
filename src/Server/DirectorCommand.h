#ifndef REVERSI_DIRECTORCOMMAND_H
#define REVERSI_DIRECTORCOMMAND_H

#include <map>
#include "Command.h"
#include "ReversiServer.h"

class DirectorCommand {
public:
    DirectorCommand(vector<Game> &listOfGames, int socket);
    ~DirectorCommand();
    void executeCommand(string command,
                        vector<string> args);
private:
    map<string, Command*> commandsMap;
    vector<Game> listOfGames;
    int socket;
};


#endif //REVERSI_DIRECTORCOMMAND_H
