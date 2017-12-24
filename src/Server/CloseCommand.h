#ifndef REVERSI_CLOSECOMMAND_H
#define REVERSI_CLOSECOMMAND_H

#include "Command.h"

class CloseCommand: public Command {
public:
    //constructor of close command
    CloseCommand(vector<Game>& listOfGames, int socket);
    //function the execute the command
    virtual void execute(vector<string> args);
private:
    vector<Game> &m_listOfGames;
    int socket;

};


#endif //REVERSI_CLOSECOMMAND_H
