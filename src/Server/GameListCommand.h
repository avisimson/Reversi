#ifndef REVERSI_GAMELISTCOMMAND_H
#define REVERSI_GAMELISTCOMMAND_H

#include "Command.h"
class GameListCommand: public Command {
public:
    GameListCommand(vector<Game>& listOfGames, int socket);
    virtual void execute(vector<string> args);
private:
    vector<Game> &m_listOfGames;
    int socket;
};


#endif //REVERSI_GAMELISTCOMMAND_H
