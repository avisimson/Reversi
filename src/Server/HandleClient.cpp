/*
 *  Created on: DEC29, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "HandleClient.h"
#define LENGTH 300
//function is a new threa that get client socket and handles all the option in the clients menu.
//start a game, join a game and list of game options.
void* HandleClient :: InitialClientServerConversation(void *details1) {
    string nameOfGame, message;
    struct Details* details = (struct Details*) details1;
    long client = (long)details->clientSocket;
    int n;
    bool check;
    char command[LENGTH];
    n = read(client, &command, sizeof(command));
    if(n == 0) { //client disconnected.
        cout << "Client disconnected before recieving initial command." << endl;
        return 0;
    }
    if(n == -1) {
        cout << "error reading message from client" << endl;
        return 0;
    }
    char* splitCommand = strtok(command, " "); //get first word-list,start,join.
    //check if command is start a game.
    if(strcmp(splitCommand, "start") == 0) {
        splitCommand = strtok(NULL, " "); //name of game
        const char* command1 = splitCommand;
        nameOfGame = command1;
        check = details->commandOfClient->execute("start", nameOfGame, client);
        if(check == false) { //game name already exists.
            message = "AlreadyExist";
            strcpy(command, message.c_str()); //set message to a way it could be sent.
            n = write(client, &command, sizeof(command)); //write to client-already exist.
            if(n == -1) {
                cout << "error writing already exist message to socket." << endl;
                return 0;
            }
            InitialClientServerConversation(details1); //listen again to clients order.
        } else { //check == true and game started.
            message = "Started";
            strcpy(command, message.c_str()); //set message to a way it could be sent.
            n = write(client, &command, sizeof(command)); //write to client-Started.
            if(n == -1) {
                cout << "error writing started message to socket." << endl;
                return 0;
            }
        }
        return 0;
    }
    //check if command is list of games
    if(strcmp(command, "list") == 0) {
        try {
            check = details->commandOfClient->execute("list", "", client);
        } catch(const char* msg) {
            cout << msg << endl;
        }
        if(check == true) {
            InitialClientServerConversation(details1); //listen again to clients order.
        } else { //check == false and client disconnected.
            return 0;
        }
    }
    //check if command is join a game.
    if(strcmp(splitCommand, "join") == 0) {
        splitCommand = strtok(NULL, " "); //get second word
        nameOfGame = splitCommand;
        check = details->commandOfClient->execute("join", nameOfGame, client);
        if (check == false) { //game name already exists.
            message = "NotExist";
            strcpy(command, message.c_str()); //set message to a way it could be sent.
            n = write(client, &command, sizeof(command)); //write to client-not exist.
            if (n == -1) {
                cout << "error writing not-exist message to socket." << endl;
                return 0;
            }
            if (n == 0) {
                cout << "Client disconnected." << endl;
                return 0;
            }
            InitialClientServerConversation(details1); //listen again to clients order.
        } else { //check == true and client joined game.
            message = "Joined";
            strcpy(command, message.c_str()); //set message to a way it could be sent.
            n = write(client, &command, sizeof(command)); //write to client-joined.
            if (n == -1) {
                cout << "error writing joined message to socket." << endl;
                return 0;
            }
            if (n == 0) {
                cout << "Client disconnected." << endl;
                return 0;
            }
            vector<Game> *list = details->commandOfClient->getListOfGames(); //get the list of current games.
            for (int i = 0; i < list->size(); i++) { //start a game handling for the specific game,
                if ((*list)[i].name == nameOfGame) {    //that client just joined
                    GameManager *newGame = new GameManager((*list)[i], details->commandOfClient);
                    newGame->ManageGame(); //play remote game in current thread.
                    delete newGame;
                    break;
                }
            }
        }
    }
    return 0;
}