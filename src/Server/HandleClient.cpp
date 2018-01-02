/*
 * ReversiServer.cpp
 *
 *  Created on: DEC29, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "HandleClient.h"
#define LENGTH 300
//function is a new threa that get client socket and handles all the option in the clients menu.
//start a game, join a game and list of game options.
static void* HandleClient :: InitialClientServerConversation(void *clientID) {
    string nameOfGame, message;
    long client = (long)clientID;
    int n;
    bool check;
    const char* command = new char[LENGTH];
    n = read(client_sd, &command, LENGTH);
    if(n == 0) { //client disconnected.
        throw "Client disconnected before recieving initial command. \n";
    }
    if(n == -1) {
        throw "error reading message from client \n";
    }
    //check if command is start a game.
    if(command[0] == 's' && command[1] == 't' && command[2] == 'a' && command[3] == 'r' && command[4] == 't') {
        char* command1 = command[6];
        nameOfGame = command1;
        check = commandOfClient->execute("start", nameOfGame, client);
        if(check == false) { //game name already exists.
            message = "AlreadyExist";
            command1 = message.c_str(); //turn the message to char*.
            n = write(client_sd, &command1, LENGTH); //write to client-already exist.
            if(n == -1) {
                throw "error writing already exist message to socket. \n";
            }
        } else { //check == true and game started.
            message = "Started";
            command1 = message.c_str(); //turn the message to char*.
            n = write(client_sd, &command1, LENGTH); //write to client-Started.
            if(n == -1) {
                throw "error writing started message to socket. \n";
            }
        }
        delete command;
        return;
    }
    //check if command is list of games.
    if(strcmp(command, "list") == 0) {
        check = commandOfClient->execute("list", NULL, client);
        if(check == true) {
            InitialClientServerConversation((void*)client);
        } else { //check == false and client disconnected.
            delete command;
            return;
        }
    }
    //check if command is join a game.
    if(command[0] == 'j' && command[1] == 'o' && command[2] == 'i' && command[3] == 'n') {
        char* command1 = command[5];
        nameOfGame = command1;
        check = commandOfClient->execute("join", nameOfGame, client);
        if(check == false) { //game name already exists.
            message = "NotExist";
            command1 = message.c_str(); //turn the message to char*.
            n = write(client_sd, &command1, LENGTH); //write to client-not exist.
            if(n == -1) {
                throw "error writing not-exist message to socket. \n";
            }
        } else { //check == true and client joined game.
            message = "Joined";
            command1 = message.c_str(); //turn the message to char*.
            n = write(client_sd, &command1, LENGTH); //write to client-joined.
            if (n == -1) {
                throw "error writing joined message to socket. \n";
            }
        }
        vector<Game> list = commandOfClient->getListOfGames(); //get the list of current games.
        for(int i = 0; i < list.size(); i++) { //start a game handling for the specific game,
            if(list[i].name == nameOfGame) {    //that client just joined.
                GameManager* newGame = new GameManager(list[i], commandOfClient);
                newGame->ManageGame(); //play remote game in current thread.
                break;
            }
        }
    }
    delete command;
    return;
}