#ifndef REVERSI_JOINGAMECOMMAND_H
#define REVERSI_JOINGAMECOMMAND_H

#include "Command.h"
#include "DirectorCommand.h"
class JoinGameCommand: public Command {
public:
    JoinGameCommand(vector<Game>& listOfGames, int socket);
    virtual void execute(vector<string> args);
    void sendGameStarts(int clientSocket1, int clientSocket2);
private:
    vector<Game> &m_listOfGames;
    int socket;
};

#endif //REVERSI_JOINGAMECOMMAND_H
