/*
 *  Created on: jan01, 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "GameManager.h"
//constructor.
GameManager :: GameManager(Game game1, Command* command1) {
    game = game1;
    command = command1;
}
//function runs the game between 2 players until game ends.
void GameManager :: ManageGame() {
    int count = 0;
    bool check;
    while (true) { //send messages between players until game ends.
        if(count == 0) {
            check = command->execute("play", game.name, 0);
            if(check == true) { //move delivered.
                count++;
            }
        } else if(count == 1) {
            Swap(); //swap between clients to make player2 turn.
            check = command->execute("play", game.name, 0);
            if(check == true) { //move delivered.
                count--;
            }
            Swap(); //swap back to player 1 turn.
        }
        //if function get "end"
        if (!check) { //game ends.
            command->execute("close", game.name, 0);
            break;
        }
    }
}
//swap between player 1 and 2 in game to get who's turn is it.
void GameManager :: Swap() {
    int i, size = command->getListOfGames()->size();
    vector<Game> *checker = command->getListOfGames();
    for(i = 0; i < size; i++) { //search the specific game in list.
        if(game.name == (*checker)[i].name) {
            break;
        }
    }
    long temp;
    temp = (*checker)[i].socket1;
    (*checker)[i].socket1 = (*checker)[i].socket2;
    (*checker)[i].socket2 = temp;
}