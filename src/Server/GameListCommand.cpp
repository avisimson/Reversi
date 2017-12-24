#include <unistd.h>
#include <iostream>
#include "GameListCommand.h"
using namespace std;
//constructor initial socket and list of games.
GameListCommand :: GameListCommand(vector<Game>& listOfGames, int socket):
        m_listOfGames(listOfGames), socket(socket){
}
//function send to specific client socket the list of available games,
//he can play.
void GameListCommand :: execute(vector<string> args){
    string listOfAvailableGames = "List of games to connect: \n";
    for(int i = 0; i < m_listOfGames.size(); i++) {
        if(m_listOfGames[i].status == Waiting) {
            listOfAvailableGames += m_listOfGames[i].name + "\n";
        }
    }
    //send list of available games to client.
    int n = write(socket, &listOfAvailableGames, sizeof(listOfAvailableGames));
    if (n == -1) {
        cout << "Error writing to socket GameListCommand" << endl;
        return;
    }
}
