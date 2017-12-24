#include <iostream>
#include <unistd.h>
#include "JoinGameCommand.h"
#define SUCCESSFUL_CONNECTION 1000
//constructor initial current socket and list of games in server.
JoinGameCommand::JoinGameCommand(vector<Game>& listOfGames, int socket):
        m_listOfGames(listOfGames), socket(socket){

}
//func gets a vector of commands,
// add socket to specific game as player2 and makes game active.
void JoinGameCommand :: execute(vector<string> args){
    for(int i = 0; i < m_listOfGames.size(); i++) {
        if (args[0] == m_listOfGames[i].name) {
            m_listOfGames[i].socket2 = socket;  //add socket as player 2 in game.
            sendGameStarts(m_listOfGames[i].socket1, m_listOfGames[i].socket2);
            m_listOfGames[i].status = Active; //game becomes active a starts.
            break;
        }
    }
    /// need to write to the socket if failed
}
//func gets 2 sockets of specific game and send them that game started.
void CommandJoin :: sendValueOfClient(int clientSocket1, int clientSocket2) {
    int num = SUCCESSFUL_CONNECTION;
    int n = write(clientSocket1, &num, sizeof(player1));
    if (n == -1) {
        cout << "Error writing to player 1 that game started." << endl;
        return;
    }
    n = write(clientSocket2, &num, sizeof(player2));
    if (n == -1) {
        cout << "Error writing to player2 that game started." << endl;
        return;
    }
}
