/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
using namespace std;
#ifndef REVERSI_GAMEMANAGER_H
#define REVERSI_GAMEMANAGER_H
#include <pthread.h>
#include <cmath>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "MakeMoveCommand.h"
#include "CloseCommand.h"
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
#endif //REVERSI_GAMEMANAGER_H
