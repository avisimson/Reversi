/*
 * Board.h
 *
 *  Created on: Oct 29, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
 */
#ifndef BOARD_H_
#define BOARD_H_
//matrix is the board status.
class Board {
//board is the matrix of the game, and size is matrix length and width.
private:
    int size;
    char **board;
// constructor function and print function.
public:
    Board(char p1, char p2, int size1);
    Board(int size);
    ~Board();
    int getSize();
    char** getBoard();
    void setBoard(int row, int col, char val);
};
#endif /* BOARD_H_ */