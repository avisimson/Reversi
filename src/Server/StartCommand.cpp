#include <unistd.h>
#include <iostream>
#include "StartCommand.h"
#define WAITING 3000
//constructor get list of games and a socket and initial its private variables.
StartCommand::StartCommand(vector<Game>& listOfGames, int socket):
        m_listOfGames(listOfGames), socket(socket){


}
//func gets vector of commands and checks if new game name already exists.
//if new game already exists-send error to client.
//if new game name not exist-open a new game on server.
void StartCommand :: execute(vector<string> args){
    int error = -1;
    for(int i = 0; i < m_listOfGames.size(); i++) {
        if (args[0] == m_listOfGames[i].name) {
            int n = write(socket, &error, sizeof(error));
            cout << "send error - the name already exists in the list of games" << endl;
            if (n == -1) { //error in sending error to client.
                cout << "Error writing to socket CommandStart" << endl;
                return;
            }
            return; //return from the method, the name is not available
        }
    }
    Game game;
    game.name = args[0];
    game.socket1 = socket; //put socket as player 1 in new game.
    game.socket2 = 0;
    game.status = Waiting;
    int num = WAITING;
    //send player 1 that he needs to wait for player2.
    n = write(socket, &num,
              sizeof(moveToSendToOtherClient));
    if (n == -1) {
        cout << "Error writing to new player-waiting." << endl;
        return;
    }
    m_listOfGames.push_back(game); //add new game to list of games.
    cout << "New game added to server " << game.name << endl;
}
