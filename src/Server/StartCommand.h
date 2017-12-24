#ifndef REVERSI_STARTCOMMAND_H
#define REVERSI_STARTCOMMAND_H
#include "Command.h"
#include "ReversiServer.h"
class StartCommand: public Command {
public:
    //constructor.
    StartCommand(vector<Game>& listOfGames, int socket);
    //start a new game.
    virtual void execute(vector<string> args);
private:
    vector<Game> &m_listOfGames;
    int socket;
};


#endif //REVERSI_STARTCOMMAND_H
