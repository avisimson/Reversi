/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
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
    string listOfAvailableGames = "List of games to join: \n";
    int i;
    for(i = 0; i < (*listOfGames).size(); i++) {
        if((*listOfGames)[i].status == Waiting) {
            listOfAvailableGames += (*listOfGames)[i].name + "\n";
        }
    }
    //print sending the list of available games to client
    char list[LENGTH];
    strcpy(list, listOfAvailableGames.c_str()); //turn the string to a way it could be sent.
    int n = write(client, &list, sizeof(list));
    cout << "send the list of available games to client "<< client << endl;
    if(n == 0) { //client disconnected.
        cout << "client disconnected before sending him list of games" << endl;
        return false;
    }
    if(n == -1) {
        cout << "ERROR WRITING LIST TO SOCKET" << endl;
        return false;
    }
    return true;
}