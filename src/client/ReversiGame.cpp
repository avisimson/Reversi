/*
 * ReversGame.h
 *
 *  Created on: Nov 10, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
 */
#include <iostream>
#include <sstream>
#include "ReversiGame.h"
#define PLAYERONE 1
#define PLAYERTWO 2
#define FILENAME "info configuration.txt"
using namespace std;
//constructor, initialize board, possible points matrix and players
//parameters-p1, p2 are player 1 and 2 names, and the type of player1, and size for board.
ReversiGame :: ReversiGame(char p1, char p2, char p1Type, int boardSize) {
    display = new ConsoleDisplay(); //initial print system.
    player1 = new Player(p1, p1Type, PLAYERONE); //HUMAN PLAYER
    //initial player 2 to be computer or human player.
    display->initialMenu();   //print start menu to choose game type.
    char choice;
    cin >> choice;
    //check if input is ok.
    while(choice != PC && choice != HUMAN && choice != QUIT
          && choice != REMOTE) {
        display->printNoOption();   //print no such option.
        cin >> choice;
    }
    if(choice != QUIT) { //game being played.
        switch(choice) { //check what player 2 should be.
            case PC:
                player2 = new Player(p2, PC, PLAYERTWO); //COMPUTER PLAYER
                break;
            case HUMAN:
                player2 = new Player(p2, HUMAN, PLAYERTWO); //HUMAN PLAYER
                break;
            case REMOTE:
                player2 = new Player(p2, REMOTE, PLAYERTWO); //REMOTE PLAYER
                break;
            default: //will never happen because of before checking but it will
                //finish the game.
                space = -1;
                break;
        }
        int size = boardSize;
        board = new Board(p1, p2, size);
        space = ((board->getSize()) * board->getSize()) - 4;
        //allocate memory for possible points matrix for player 1 and 2,
        // and initialize their values to -1.
        possiblePointsone = new int *[space];
        for (int i = 0; i < space; i++) {
            possiblePointsone[i] = new int[2];
            for (int j = 0; j < 2; j++) {
                possiblePointsone[i][j] = -1;
            }
        }
        possiblePointstwo = new int *[space];
        for (int i = 0; i < space; i++) {
            possiblePointstwo[i] = new int[2];
            for (int j = 0; j < 2; j++) {
                possiblePointstwo[i][j] = -1;
            }
        }
    } else { //player want to quit game.
        space = -1;
    }
}
//destructor-releases all memory from system.
ReversiGame :: ~ReversiGame() {
    delete player1;
    delete player2;
    if(space == -1) {
        delete[] possiblePointsone;
        delete[] possiblePointstwo;
    } else {
        for (int i = 0; i < ((board->getSize()) * board->getSize()) - 4; i++) {
            delete possiblePointsone[i];
        }
        delete[] possiblePointsone;
        for (int i = 0; i < ((board->getSize()) * board->getSize()) - 4; i++) {
            delete possiblePointstwo[i];
        }
        delete[] possiblePointstwo;
    }
    delete display;
    delete board;
}
//function runs reversi game until both players can't play or board is full.
//at the end of the game function prints the score and the winner.
void ReversiGame :: playGame() {
    if(space == -1) { //quit game.
        return;
    }
    //check if numbers of players 1,2 are wrong and fix it if needbe.
    if(player1->getNum() != PLAYERONE || player2->getNum() != PLAYERTWO) {
        player1->setNum(PLAYERONE);
        player2->setNum(PLAYERTWO);
    }
    int currentTurn = 1; //tells who's turn is it player1/player2.
    int cantPlay = 0; //counts if both players cant play to finish game.
    bool b = true;
    //check if to start a network game of user against remote player.
    if(player1->getType() == HUMAN && player2->getType() == REMOTE) {
        playGameVsRemote(); //playing game against remote until game ends
        //or one of the players disconnected.
        scoreGame();
        return;
    }
    display->printBoard(board);
    //game is PC-PC, HUMAN-PC, PC-HUMAN, HUMAN-HUMAN. remote wasn't chosen.
    //check if player1 and player2 initialized as C or H type to play.
    if(player1->getType() != PC && player1->getType() != HUMAN)
    {
        display->playerTypeWrong(PLAYERONE);
        return;
    }
    if(player2->getType() != PC && player2->getType() != HUMAN)
    {
        display->playerTypeWrong(PLAYERTWO);
        return;
    }
    //Game loop.
    while(space > 0 && cantPlay < 2) {
        if(currentTurn == 1) {
            if(player1->getType() == PC) {
                b = ComputerplayOneTurn(player1);
            } else {
                b = HumanplayOneTurn(player1);
            }
            currentTurn++;
            if (b == false) {
                cantPlay++;
            } else {
                cantPlay = 0;
                space--;
            }
        } else if (cantPlay < 2) {
            if(player2->getType() == PC) {
                b = ComputerplayOneTurn(player2);
            } else {
                b = HumanplayOneTurn(player2);
            }
            currentTurn--;
            if (b == false) {
                cantPlay++;
            } else {
                cantPlay = 0;
                space--;
            }
        }
    }
    //game ended, print score of the game.
    scoreGame();
}
//parameters: player is the char sign for the player which is his turn.
//function plays on turn of reversi by checking possible moves for the player,
//and plays the turn for him.
//return: true is player played turn, false if not.
bool ReversiGame :: HumanplayOneTurn(Player* player) {
    checkPossibleMoves(player, board);
    int** possiblePoints;
    //create new matrix that will point on the correct matrix according to
    // if player is player 1 or 2.
    if(player->getNum() == PLAYERONE) {
        possiblePoints = possiblePointsone;
    } else if(player->getNum() == PLAYERTWO) {
        possiblePoints = possiblePointstwo;
    } else {
        display->notInitializedTypes(player->getName()); //print player types wrong.
        return false;
    }
    if (possiblePoints[0][0] == -1) { //player has no possible moves, cant play
        display->noPossibleMoves(player->getName()); //print no possible moves.
        return false;
    } else { //player can play
        display->printItsYourMove(player->getName()); //print its your move.
        int index = 0;
        //print possible moves for player.
        while(possiblePoints[index][0] > -1) {
            display->printRowCol(possiblePoints[index][0], possiblePoints[index][1]);
            if(possiblePoints[index + 1][0] != -1) {
                display->printPsik(); //print ,
            }
            index++;
        }
        display->printLineDrop(); //get one line down.
        int row, col, i, counter = 0;
        string row1, col1;
        //player enters row,col and the game makes sure that he played,
        //a legal move.
        while (counter == 0) {
            display->printEnterMove(); //print enter move.
            cin >> row1 >> col1;
            istringstream buffer(row1);
            buffer >> row;
            istringstream buffer2(col1);
            buffer2 >> col;
            for(i = 0; i < space; i++) {
                if(row == possiblePoints[i][0]) {
                    if(col == possiblePoints[i][1]) {
                        break;
                    }
                }
            }
            if(i >= space) {
                display->printWrongInput(); // print wrong input.
            } else {
                counter = 1;
                board->setBoard(row, col, player->getName());
                playPossiblePoints(player, row, col, board);
                i = 0;
                //reset possible moves for next turn.
                while(possiblePoints[i][0] != -1) {
                    possiblePoints[i][0] = -1;
                    possiblePoints[i][1] = -1;
                    i++;
                }
                display->printBoard(board); //print board.
                display->printPlayerPlayedRowCol(player->getName(), row, col);
                return true;
            }
        }
    }
}
//parameters: player is the char sign for the player which is his turn.
//function plays the turn for pc by checking if he has options to play,
//and if he does have, it checks what is the most efficient move for pc and
//plays the most efficient move.
//return: true is player played turn, false if not.
bool ReversiGame :: ComputerplayOneTurn(Player* player) {
    checkPossibleMoves(player, board);
    int** possiblePointsPlayer;
    int** possiblePointsOppose;
    //create new matrixes that will point on the correct matrix according to
    // if player is player 1 or 2.
    Player* opposePlayer;
    if(player->getNum() == PLAYERONE) {
        opposePlayer = player2;
        possiblePointsPlayer = possiblePointsone;
        possiblePointsOppose = possiblePointstwo;
    } else { //player is player2.
        possiblePointsPlayer = possiblePointstwo;
        possiblePointsOppose = possiblePointsone;
        opposePlayer = player1;
    }
    if (possiblePointsPlayer[0][0] == -1) { //player has no possible moves,
        // cant play
        display->noPossibleMoves(player->getName()); //print no moves.
        return false;
    } else { //player can play
        //creating a clone of deep copy to the board current positions.
        Board* clone = new Board(board->getSize());
        Board* clone2 =  new Board(board->getSize());;
        int i, j, x, y; //indexes for loops.
        for(i = 1; i <= clone->getSize(); i++) {
            for(j = 1; j <= clone->getSize(); j++) {
                clone->setBoard(i, j, board->getBoard()[i][j]);
            }
        }
        i = 0, j;
        int minRow = -1, minCol = -1,
                minvalue = board->getSize() * board->getSize(),
                maxValue = 0, maxRow = -1, maxCol = -1, k = 0;
        //playing on clone the computers turn on each possible point and play,
        //the opponets possible movers after and update min value.
        while(possiblePointsPlayer[i][0] != -1) {
            j = 0;
            //play the computers turn on clone board.
            clone->setBoard(possiblePointsPlayer[i][0],
            possiblePointsPlayer[i][1], player->getName());
            playPossiblePoints(player, possiblePointsPlayer[i][0],
                               possiblePointsPlayer[i][1], clone);
            //filling opposing players possible points after computer,
            //played on clone.
            checkPossibleMoves(opposePlayer, clone);
            //playing on clone 2 opposing players possible moves.
            while(possiblePointsOppose[j][0] != -1) {
                //copying clone 2 to clone 1.
                for(x = 1; x <= clone->getSize(); x++) {
                    for(y = 1; y <= clone->getSize(); y++) {
                        clone2->setBoard(x, y, clone->getBoard()[x][y]);
                    }
                }
                //opposing player plays.
                clone2->setBoard(possiblePointsOppose[j][0],
                                 possiblePointsOppose[j][1],
                                 opposePlayer->getName());
                playPossiblePoints(opposePlayer, possiblePointsOppose[j][0],
                                   possiblePointsOppose[j][1], clone2);
                //check score after opposing player played.
                int oposseScore = checkBoard(clone2, player);
                //check the best move for opposing player to play.
                if(oposseScore > maxValue) {
                    maxValue = oposseScore;
                    maxCol = possiblePointsPlayer[i][1];
                    maxRow = possiblePointsPlayer[i][0];
                }
                j++;
            }
            //check what is the best scenario for current pc player turn.
            if(maxValue < minvalue) {
                minvalue = maxValue;
                minRow = maxRow;
                minCol = maxCol;
            }
            i++;
        }
        //save the first possible point of pc player to be able to play
        //even if oppose player can't play(connection with if few lines under),
        int playerRow = possiblePointsPlayer[0][0];
        int playerCol = possiblePointsPlayer[0][1];
        //return possible points array to no possible points.
        while(possiblePointsPlayer[k][0] != -1) {
            possiblePointsPlayer[k][0] = -1;
            possiblePointsPlayer[k][1] = -1;
            k++;
        }
        //remove 2 clone boards from heap and return to playgame function.
        delete clone;
        delete clone2;
        if(minRow == -1 || minCol == -1) { //if oppose player doesnt have
            //possible moves.
            if(playerRow != -1) {
                board->setBoard(playerRow, playerCol, player->getName());
                playPossiblePoints(player, playerRow, playerCol, board);
                display->printBoard(board);
                display->printPlayerPlayedRowCol(player->getName(), playerRow, playerCol);
                return true;
            }
            display->printComCantPlay(player->getName()); //print computer cant play.
            return false;
        }
        board->setBoard(minRow, minCol, player->getName());
        playPossiblePoints(player, minRow, minCol, board);
        display->printBoard(board);
        display->printPlayerPlayedRowCol(player->getName(), playerRow, playerCol);
        return true;
    }
}
//parameters: player is the current player who plays, i and j are row and col
//for a move, and b1 is the board being played.
//function plays a turn for player.
void ReversiGame :: playPossiblePoints(Player* player, int i, int j, Board *b1) {
    checkUp(player, i, j, true, b1);
    checkDown(player, i, j, true, b1);
    checkLeft(player, i, j, true, b1);
    checkRight(player, i, j, true, b1);
    checkUpLeft(player, i, j, true, b1);
    checkUpRight(player, i, j, true, b1);
    checkDownLeft(player, i, j, true, b1);
    checkDownRight(player, i, j, true, b1);
}
/*
 * function gets board as a parameter and a player and checks which player has
 * more points on board. function returns integer of opposing player minus
 * current player's turn(opposing-player).
 */
int ReversiGame :: checkBoard(Board* board, Player* player) {
    int i, j, sum1 = 0, sum2 = 0;
    Player* oppose;
    if(player->getNum() == PLAYERONE) {
        oppose = player2;
    } else {
        oppose = player1;
    }
    for(i = 1; i <= board->getSize(); i++) {
        for(j = 1; j <= board->getSize(); j++) {
            if(board->getBoard()[i][j] == player->getName()) {
                sum1++;
            } else if(board->getBoard()[i][j] == oppose->getName()) {
                sum2++;
            }
        }
    }
    return sum2 - sum1;
}
//function checks who is the winner and prints the winner and the score.
//run on the board matrix and count how much player1 shows up and how much
//player 2 shows up.
void ReversiGame :: scoreGame() {
    int count1 = 0, count2 = 0, i, j;
    for(i = 1; i <= board->getSize(); i++) {
        for(j = 1; j <= board->getSize(); j++) {
            if(board->getBoard()[i][j] == player1->getName()) {
                count1++;
            } else if(board->getBoard()[i][j] == player2->getName()) {
                count2++;
            }
        }
    }
    //print score of the game.
    display->printScore(player1->getName(), player2->getName(), count1, count2);
}
//function gets a player as a parameter and update the possible moves of
//the player on the human/computer possible points array on boards parameter b.
void ReversiGame :: checkPossibleMoves(Player* player, Board* b) {
    int i, j, count = 0;
    for(i = 1; i <= b->getSize(); i++) {
        for(j = 1; j <= b->getSize(); j++) {
            if(b->getBoard()[i][j] == ' ') {
                if(checkUp(player, i, j, false, b)
                   || checkDown(player, i, j, false, b)
                   || checkLeft(player, i, j, false, b)
                   || checkRight(player, i, j, false, b)
                   || checkUpLeft(player, i, j, false, b)
                   || checkUpRight(player, i, j, false, b)
                   || checkDownLeft(player, i, j, false, b)
                   || checkDownRight(player, i, j, false, b)) {
                    if(player->getNum() == PLAYERONE) {
                        possiblePointsone[count][0] = i;
                        possiblePointsone[count][1] = j;
                    } else if(player->getNum() == PLAYERTWO){
                        possiblePointstwo[count][0] = i;
                        possiblePointstwo[count][1] = j;
                    } else {
                        return;
                    }
                    count++;
                }
            }
        }
    }
}
//function check for  possible moves for an i,j point,
//and flips disc if boolean flip is true.
//return: true if possible move or false if not.
//par:player is current player's turn, (i,j) are row and col of
// the point being checked. flip says weather to flip disc or not.
bool ReversiGame :: checkUp(Player* player, int i, int j, bool flip,
                            Board* b1) {
    int count2 = 0; //counts other player showings.
    if(i == 1 || i == 2) {
        return false;
    } else {
        i--;
        while(i > 0) {
            if(b1->getBoard()[i][j] != player->getName()
               && b1->getBoard()[i][j] != ' ') {
                count2++;
            }
            if(b1->getBoard()[i][j] == player->getName()) {
                if(count2 > 0) {
                    //change disc if flip is true.
                    if(flip) {
                        while(count2 > 0) {
                            b1->setBoard(i + count2, j, player->getName());
                            count2--;
                        }
                    }
                    return true;
                }
                return false;
            }
            if(b1->getBoard()[i][j] == ' ') {
                return false;
            }
            i--;
        }
        return false;
    }
}
//function check for  possible moves for an i,j point,
//and flips disc if boolean flip is true.
//return: true if possible move or false if not.
//par:player is current player's turn, (i,j) are row and col of
// the point being checked. flip says weather to flip disc or not.
bool ReversiGame :: checkDown(Player* player, int i, int j,
                              bool flip, Board* b1) {
    int count2 = 0; //counts other player showings.
    if(i == b1->getSize() - 1 || i == b1->getSize()) {
        return false;
    } else {
        i++;
        while(i <= b1->getSize()) {
            if(b1->getBoard()[i][j] != player->getName()
               && b1->getBoard()[i][j] != ' ') {
                count2++;
            }
            if(b1->getBoard()[i][j] == player->getName()) {
                if(count2 > 0) {
                    //change disc if flip is true.
                    if(flip) {
                        while(count2 > 0) {
                            b1->setBoard(i - count2, j, player->getName());
                            count2--;
                        }
                    }
                    return true;
                }
                return false;
            }
            if(b1->getBoard()[i][j] == ' ') {
                return false;
            }
            i++;
        }
        return false;
    }
}
//function check for possible moves for an i,j point,
//and flips disc if boolean flip is true.
//return: true if possible move or false if not.
//par:player is current player's turn, (i,j) are row and col of
// the point being checked. flip says weather to flip disc or not.
bool ReversiGame :: checkLeft(Player* player, int i, int j,
                              bool flip, Board* b1) {
    int count2 = 0; //counts other player showings.
    if(j == 1 || j == 2) {
        return false;
    } else {
        j--;
        while(j > 0) {
            if(b1->getBoard()[i][j] != player->getName()
               && b1->getBoard()[i][j] != ' ') {
                count2++;
            }
            if(b1->getBoard()[i][j] == player->getName()) {
                if(count2 > 0) {
                    //change disc if flip is true.
                    if(flip) {
                        while(count2 > 0) {
                            b1->setBoard(i, j + count2, player->getName());
                            count2--;
                        }
                    }
                    return true;
                }
                return false;
            }
            if(b1->getBoard()[i][j] == ' ') {
                return false;
            }
            j--;
        }
        return false;
    }
}
//function check for possible moves for an i,j point,
//and flips disc if boolean flip is true.
//return: true if possible move or false if not.
//par:player is current player's turn, (i,j) are row and col of
// the point being checked. flip says weather to flip disc or not.
bool ReversiGame :: checkRight(Player* player, int i, int j,
                               bool flip, Board* b1) {
    int count2 = 0; //counts other player showings.
    if(j == b1->getSize() - 1 || j == b1->getSize()) {
        return false;
    } else {
        j++;
        while(j <= b1->getSize()) {
            if(b1->getBoard()[i][j] != player->getName()
               && b1->getBoard()[i][j] != ' ') {
                count2++;
            }
            if(b1->getBoard()[i][j] == player->getName()) {
                if(count2 > 0) {
                    //change disc if flip is true.
                    if(flip) {
                        while(count2 > 0) {
                            b1->setBoard(i, j - count2, player->getName());
                            count2--;
                        }
                    }
                    return true;
                }
                return false;
            }
            if(b1->getBoard()[i][j] == ' ') {
                return false;
            }
            j++;
        }
        return false;
    }
}
//function check for possible moves for an i,j point,
//and flips disc if boolean flip is true.
//return: true if possible move or false if not.
//par:player is current player's turn, (i,j) are row and col of
// the point being checked. flip says weather to flip disc or not.
bool ReversiGame :: checkUpLeft(Player* player, int i, int j,
                                bool flip, Board* b1) {
    int count2 = 0; //counts other player showings.
    if(j == 1 || j == 2 || i == 1 || i == 2) {
        return false;
    } else {
        j--;
        i--;
        while(j > 0 && i > 0) {
            if(b1->getBoard()[i][j] != player->getName()
               && b1->getBoard()[i][j] != ' ') {
                count2++;
            }
            if(b1->getBoard()[i][j] == player->getName()) {
                if(count2 > 0) {
                    //change disc if flip is true.
                    if(flip) {
                        while(count2 > 0) {
                            b1->setBoard(i + count2, j + count2,
                                            player->getName());
                            count2--;
                        }
                    }
                    return true;
                }
                return false;
            }
            if(b1->getBoard()[i][j] == ' ') {
                return false;
            }
            j--;
            i--;
        }
        return false;
    }
}
//function check for possible moves for an i,j point,
//and flips disc if boolean flip is true.
//return: true if possible move or false if not.
//par:player is current player's turn, (i,j) are row and col of
// the point being checked. flip says weather to flip disc or not.
bool ReversiGame :: checkUpRight(Player* player, int i, int j,
                                 bool flip, Board* b1) {
    int count2 = 0; //counts other player showings.
    int size = b1->getSize();
    if(j == size - 1 || j == size || i == 1 || i == 2) {
        return false;
    } else {
        j++;
        i--;
        while(j <= size && i > 0) {
            if(b1->getBoard()[i][j] != player->getName()
               && b1->getBoard()[i][j] != ' ') {
                count2++;
            }
            if(b1->getBoard()[i][j] == player->getName()) {
                if(count2 > 0) {
                    //change disc if flip is true.
                    if(flip) {
                        while(count2 > 0) {
                            b1->setBoard(i + count2, j - count2,
                                            player->getName());
                            count2--;
                        }
                    }
                    return true;
                }
                return false;
            }
            if(b1->getBoard()[i][j] == ' ') {
                return false;
            }
            j++;
            i--;
        }
        return false;
    }
}
//function check for possible moves for an i,j point,
//and flips disc if boolean flip is true.
//return: true if possible move or false if not.
//par:player is current player's turn, (i,j) are row and col of
// the point being checked. flip says weather to flip disc or not.
bool ReversiGame :: checkDownLeft(Player* player, int i, int j, bool flip,
                                  Board* b1) {
    int count2 = 0; //counts other player showings.
    int size = b1->getSize();
    if(j == 1 || j == 2 || i == size - 1 || i == size) {
        return false;
    } else {
        j--;
        i++;
        while(j > 0 && i <= size) {
            if(b1->getBoard()[i][j] != player->getName()
               && b1->getBoard()[i][j] != ' ') {
                count2++;
            }
            if(b1->getBoard()[i][j] == player->getName()) {
                if(count2 > 0) {
                    //change disc if flip is true.
                    if(flip) {
                        while(count2 > 0) {
                            b1->setBoard(i - count2, j + count2,
                                            player->getName());
                            count2--;
                        }
                    }
                    return true;
                }
                return false;
            }
            if(b1->getBoard()[i][j] == ' ') {
                return false;
            }
            j--;
            i++;
        }
        return false;
    }
}
//function check for possible moves for an i,j point,
//and flips disc if boolean flip is true.
//return: true if possible move or false if not.
//par:player is current player's turn, (i,j) are row and col of
// the point being checked. flip says weather to flip disc or not.
bool ReversiGame :: checkDownRight(Player* player, int i, int j,
                                   bool flip, Board* b1) {
    int count2 = 0; //counts other player showings.
    int size = b1->getSize();
    if(j == size - 1 || j == size || i == size - 1 || i == size) {
        return false;
    } else {
        j++;
        i++;
        while(j <= size && i <= size) {
            if(b1->getBoard()[i][j] != player->getName()
               && b1->getBoard()[i][j] != ' ') {
                count2++;
            }
            if(b1->getBoard()[i][j] == player->getName()) {
                if(count2 > 0) {
                    //change disc if flip is true.
                    if(flip) {
                        while(count2 > 0) {
                            b1->setBoard(i - count2, j - count2,
                                            player->getName());
                            count2--;
                        }
                    }
                    return true;
                }
                return false;
            }
            if(b1->getBoard()[i][j] == ' ') {
                return false;
            }
            j++;
            i++;
        }
        return false;
    }
}
//return board of the game.
Board* ReversiGame :: getBoard() {
    return board;
}
//return player1 of the game.
Player* ReversiGame :: getPlayerOne() {
    return player1;
}
//return player2 of the game.
Player* ReversiGame :: getPlayerTwo() {
    return player2;
}
//return the number of spaces in the board matrix of the game.
int ReversiGame :: getBoardSpace() {
    return space;
}
int** ReversiGame :: getPossiblePointsOne() {
    return possiblePointsone;
}
int** ReversiGame :: getPossiblePointsTwo() {
    return possiblePointstwo;
}
//function plays game between user and remote player by using an external
//server.
void ReversiGame :: playGameVsRemote() {
    const string s = FILENAME;
    NetworkClient* client = new NetworkClient(s); //initialize client.
    try {
        client->MenuVsRemote(display); //try to connect to server and choose king of game.
    } catch(const char *msg) {
        display->printFailToConnect(msg);
        delete client;
        return;
    }
    int type;
    try {
        type = client->getPlayerNum(); //get 1,2 to know if client is player 1 or 2
    } catch(char* msg) {
        cout << msg;
    }
    struct Info info;
    int cantPlay = 0, turn = PLAYERONE;
    if(type == PLAYERONE) { //user is player 1.
        display->printYouArePlayer(PLAYERONE); //print you are player 1/2.
        while(true) { //stop doing anything until player 2 arrives.
            try {
                if(client->getType() == PLAYERTWO) {
                    break;
                }
            } catch(const char* msg) {
                cout << msg << endl;
                return;
            }
        }
        display->printBoard(board); //print board.
        while(cantPlay < 2 && space > 0) {
            if(turn == PLAYERONE) { //PLAYER1 TURN
                if(PlayTurnAgainstRemote(client, player1)) {
                    //played and sent row,col
                    cantPlay = 0;
                    turn++;
                    space--; // one empty place less on board
                } else { //player didnt have possible moves/sending move failed
                    if(possiblePointsone[0][0] == -1) { //didnt have moves.
                        if(cantPlay == 0) {
                            try {
                                client->sendNoMove();
                                cantPlay++;
                                turn++;
                            } catch(char* msg) {
                                cout << msg << endl;
                            }
                        } else { //cantplay == 1
                            try {
                                client->sendEnd();
                                cantPlay++;
                            } catch(char* msg) {
                                cout << msg << endl;
                            }
                        }
                    } else { //made the move but didnt send to other player
                        continue;
                    }
                }
            } else { //turn == PLAYERTWO
                display->printWaiting();
                try {
                    //remote play.
                    info = client->getMove();
                    //got end game from remote so exit func.
                    if(info.x == End) { return; }
                    if(info.x == NoMove) { //remote player did not have moves.
                        display->printRemoteCantPlay();
                        cantPlay++;
                        if(cantPlay == 2) { //send other player to finish game also.
                            try {
                                client->sendEnd();
                            } catch(char* msg1) { //fail to send.
                                cout << msg1 << endl;
                            }
                        }
                    } else {
                        board->setBoard(info.x, info.y, player2->getName());
                        playPossiblePoints(player2, info.x, info.y, board);
                        cantPlay = 0;
                        display->printBoard(board); //print board.
                        display->printPlayerPlayedRowCol(player2->getName(), info.x, info.y);
                        space--; // one empty place less on board
                    }
                    turn--;
                } catch(char* msg) {
                    cout << msg << endl;
                }
            }
        }
    } else if(type == PLAYERTWO) { //user is player 2
        display->printYouArePlayer(PLAYERTWO); //print you are player 1/2.
        display->printBoard(board);
        while(cantPlay < 2 && space > 0) {
            if(turn == PLAYERONE) {
                display->printWaiting();
                try {
                    //remote play.
                    info = client->getMove();
                    if(info.x == End) {
                        return; } //got end game from remote so exit func. or player1 disconnected.
                    if(info.x == NoMove) { //remote player did not have moves.
                        display->printRemoteCantPlay();
                        cantPlay++;
                        if(cantPlay == 2) { //send other player to finish game also.
                            try {
                                client->sendEnd();
                            } catch(char* msg1) { //fail to send.
                                cout << msg1 << endl;
                            }
                        }
                    } else {
                        board->setBoard(info.x, info.y, player1->getName());
                        playPossiblePoints(player1, info.x, info.y, board);
                        cantPlay = 0;
                        display->printBoard(board); //print board.
                        display->printPlayerPlayedRowCol(player1->getName(), info.x, info.y);
                        space--; // one empty place less on board
                    }
                    turn++;
                } catch(char* msg) {
                    cout << msg << endl;
                }
            } else { //turn == PLAYERTWO
                if(PlayTurnAgainstRemote(client, player2)) {
                    //played and sent row,col
                    cantPlay = 0;
                    turn--;
                    space--; // one empty place less on board
                } else { //player didnt have possible moves/sending move failed
                    if(possiblePointstwo[0][0] == -1) { //didnt have moves.
                        if(cantPlay == 0) {
                            try {
                                client->sendNoMove();
                                cantPlay++;
                                turn--;
                            } catch(char* msg) {
                                cout << msg << endl;
                            }
                        } else { //cantplay == 1
                            try {
                                client->sendEnd();
                                cantPlay++;
                            } catch(char* msg) {
                                cout << msg << endl;
                            }
                        }
                    } else { //made the move but didnt send to other player
                        continue;
                    }
                }
            }
        }
    }
    delete client; //remove client from heap.
}
//function plays one turn against remote
bool ReversiGame :: PlayTurnAgainstRemote(NetworkClient* client, Player* player) {
    checkPossibleMoves(player, board);
    string row1, col1; //helper for more simple input.
    int row, col;
    int** possiblePoints;
    //create new matrix that will point on the correct matrix according to
    // if player is player 1 or 2.
    if(player->getNum() == PLAYERONE) {
        possiblePoints = possiblePointsone;
    } else if(player->getNum() == PLAYERTWO) {
        possiblePoints = possiblePointstwo;
    }
    int i = space;
    if (possiblePoints[0][0] == -1) { //no possible moves, cant play
        display->noPossibleMoves(player->getName());
        return false;
    }
    //player has possible points and can play.
    while (i >= space) { //input from user to row and col, until good input
        display->printItsYourMove(player->getName());
        int index = 0;
        //print possible moves for player.
        while(possiblePoints[index][0] > -1) {
            display->printRowCol(possiblePoints[index][0], possiblePoints[index][1]);
            if(possiblePoints[index + 1][0] != -1) {
                display->printPsik(); //print ,
            }
            index++;
        }
        display->printEnterMove();
        cin >> row1 >> col1;
        istringstream buffer(row1);
        buffer >> row;
        istringstream buffer2(col1);
        buffer2 >> col;
        for (i = 0; i < space; i++) {
            if (row == possiblePoints[i][0]) {
                if (col == possiblePoints[i][1]) {
                    break;
                }
            }
        }
        if (i >= space) {
            display->printWrongInput();
        }
    }
    try { //sending move to socket.
        client->sendMove(row, col);
    } catch (const char* msg) { //fail to send move to socket.
        cout << msg << endl;
        return false;
    }
    board->setBoard(row, col, player->getName());
    playPossiblePoints(player, row, col, board);
    i = 0;
    //reset possible moves for next turn.
    while(possiblePoints[i][0] != -1) {
        possiblePoints[i][0] = -1;
        possiblePoints[i][1] = -1;
        i++;
    }
    display->printBoard(board); // print board.
    display->printPlayerPlayedRowCol(player->getName(), row, col);
    return true;
}