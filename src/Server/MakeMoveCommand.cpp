#include "MakeMoveCommand.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>

using namespace std;
//constructor-initial private variables. connects the secific moves of game to
//a client and a specific game.
MakeMoveCommand :: MakeMoveCommand(vector<Game>& listOfGames, int socket):
        m_listOfGames(listOfGames), socket(socket){
}
/*function check which socket sent her a move, connects to specific game
 * and send move from a socket to the other one.*/
void MakeMoveCommand :: execute(vector<string> args){
    int moveToSendToOtherClient[2]; //array of row, col integers.
    moveToSendToOtherClient[0] = atoi(args[0].c_str()); //convert string to int
    moveToSendToOtherClient[1] = atoi(args[1].c_str());
    //check which socket to connect to.
    for(int i = 0; i < m_listOfGames.size(); i++) {
        if(socket == m_listOfGames[i].socket1) {
            //write row col from player1 of specific game to player2.
            int n = write(m_listOfGames[i].socket2, &moveToSendToOtherClient[0],
                          sizeof(moveToSendToOtherClient));
            if (n == -1) {
                cout << "Error writing to socket row" << endl;
                return;
            }
            n = write(m_listOfGames[i].socket2, &moveToSendToOtherClient[1],
                          sizeof(moveToSendToOtherClient));
            if (n == -1) {
                cout << "Error writing to socket col" << endl;
                return;
            }
            return;
        } else if(socket == m_listOfGames[i].socket2) {
            //write row col from player2 of specific game to player1.
            int n = write(m_listOfGames[i].socket1, &moveToSendToOtherClient[0],
                          sizeof(moveToSendToOtherClient));
            if (n == -1) {
                cout << "Error writing to socket row" << endl;
                return;
            }
            n = write(m_listOfGames[i].socket1, &moveToSendToOtherClient[1],
                          sizeof(moveToSendToOtherClient));
            if (n == -1) {
                cout << "Error writing to socket col" << endl;
                return;
            }
            return;
        }
    }
}
