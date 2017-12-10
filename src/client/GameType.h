/*
 * Player.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
 */
#ifndef REVERSI_GAMETYPE_H
#define REVERSI_GAMETYPE_H
//GameType class is a virtual class that all games in project implement.
class GameType {
    public:
        virtual void playGame() {};
        virtual ~GameType() {};
};
#endif //REVERSI_GAMETYPE_H
