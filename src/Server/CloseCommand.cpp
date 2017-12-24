#include "CloseCommand.h"
#include <unistd.h>
#include <iostream>
using namespace std;
#define SUCCESSFUL_CLOSE 2000
//constructor, get list of games and a socket and initial them.
CloseCommand :: CloseCommand(vector<Game>& listOfGames, int socket):
        m_listOfGames(listOfGames), socket(socket){
}
//get vector of strings and get a name of a game to close.
void CloseCommand :: execute(vector<string> args){
    for(int i = 0; i < m_listOfGames.size(); i++) {
        //if name of game that want to close equal to game in list games.
        if(m_listOfGames[i].name == args[0]) {
            int num = SUCCESSFUL_CLOSE;
            int n = write(m_listOfGames[i].socket1, &num,
                          sizeof(moveToSendToOtherClient));
            if (n == -1) {
                cout << "Error writing to socket1 that game ended." << endl;
                return;
            }
            n = write(m_listOfGames[i].socket2, &num,
                      sizeof(moveToSendToOtherClient));
            if (n == -1) {
                cout << "Error writing to socket2 that game ended." << endl;
                return;
            }
            close(m_listOfGames[i].socket1);
            close(m_listOfGames[i].socket2);
            cout << "Game: " << m_listOfGames[i].name << "Has been closed" <<
                 endl;
            m_listOfGames.erase(m_listOfGames.begin() + i); //erase game from list of games.
            break;
        }
    }
}
