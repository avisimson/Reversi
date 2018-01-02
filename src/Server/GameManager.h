#include <pthread.h>
#include <cmath>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "MakeMoveCommand.h"
#include "CloseCommand.h"
using namespace std;
enum StatusForServer {
    NoMove = 100, End = 101
};
#ifndef REVERSI_GAMEMANAGER_H
class GameManager {
    private:
    Command* command;
        Game game;
    public:
        GameManager(Game game, Command* command);
        ~GameManager() {};
        void ManageGame();
        void Swap();
};
#define REVERSI_GAMEMANAGER_H

#endif //REVERSI_GAMEMANAGER_H
