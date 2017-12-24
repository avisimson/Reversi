#ifndef REVERSI_MAKEMOVECOMMAND_H
#define REVERSI_MAKEMOVECOMMAND_H

#include <vector>
#include "Command.h"
class MakeMoveCommand: public Command {
public:
    //constructor.
    MakeMoveCommand(vector<Game>& listOfGames, int socket);
    virtual void execute(vector<string> args);
private:
    vector<Game> &m_listOfGames;
    int socket;
};


#endif //REVERSI_MAKEMOVECOMMAND_H
