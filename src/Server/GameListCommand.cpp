#include <unistd.h>
#include <iostream>
#include "GameListCommand.h"
#include "HandleClient.h"
#define LENGTH 300
using namespace std;
//constructor.
GameListCommand :: GameListCommand(vector<Game> *listOfGames1) {
    listOfGames = listOfGames1;
}
//command is the start command, args is name of game, client is the socket of client.
//func returns true anyway and send to client the list of games he can join.
//if client disconnect func return false;
bool GameListCommand :: execute(string command, string args, int client){
    int clientSocket = data->clientSocket; //read socket of client.
    string listOfAvailableGames = "List of games to join: \n";
    for(int i = 0; i < listOfGames.size(); i++) {
        if(listOfGames[i].status == Waiting) {
            listOfAvailableGames += listOfGames[i]->name + "\n";
        }
    }
    //print sending the list of available games to client
    const char list = new char[LENGTH];
    list = listOfAvailableGames.c_str(); //turn the string to char array to send to client.
    int n = write(client, &list, LENGTH);
    delete list;
    cout << "send the list of available games to client "<< client << endl;
    if(n == 0) { //client disconnected.
        cout << "client disconnected before sending him list of games" << endl;
        return false;
    }
    if(n == -1) {
        throw "Error writing to socket CommandGetList \n";
    }
    return true;
}