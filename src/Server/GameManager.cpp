/*
 * NetworkClient.h
 *
 *  Created on: jan01, 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "GameManager.h"
//constructor.
GameManager :: GameManager(Game game1, Command* command1) {
    game = game1;
    command = command;
}
//function runs the game between 2 players until game ends.
void GameManager :: ManageGame() {
    int count = 0;
    bool check;
    while (true) { //send messages between players until game ends.
        if(count == 0) {
            check = command->execute("play", game.name, NULL);
            if(check == true) { //move delivered.
                count++;
            }
        } else if(count == 1) {
            Swap(); //swap between clients to make player2 turn.
            int check = checkValidate(game.socket2, game.socket1);
            if(check == true) { //move delivered.
                count--;
            }
            Swap(); //swap back to player 1 turn.
        }
        //if function get "end"
        if (!check) { //game ends.
            command->execute("close", game.name, NULL);
            break;
        }
    }
}
//swap between player 1 and 2 in game to get who's turn is it.
void GameManager :: Swap() {
    int temp;
    game.socket1 = temp;
    game.socket1 = game.socket2;
    game.socket2 = temp;

}
