/*
 * Board_test.cpp
 *
 *  Created on: Nov 27, 2017
 *  Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#define SYMBOL1 'X'
#define SYMBOL2 'O'
#include "Board_test.h"
#define SIZE 5
//function TEST checks if SYMBOL2 in in place SIZE/2 after initialize,
// as requested.
TEST(value1, value2) {
    Board* board = new Board(SYMBOL1, SYMBOL2, SIZE);
    if(SIZE % 2 == 0) { //SIZE is even
        //expect SYMBOL2 to be in the boards initialization place.
        EXPECT_EQ(SYMBOL2, board->getBoard()[SIZE/2][SIZE/2]);
        EXPECT_NE(SYMBOL1, board->getBoard()[SIZE/2][SIZE/2]);
    } else { //SIZE is odd
        //expect SYMBOL2 to be in the boards initialization place.
        EXPECT_EQ(SYMBOL2, board->getBoard()[SIZE/2 + 1][SIZE/2 + 1]);
        EXPECT_NE(SYMBOL1, board->getBoard()[SIZE/2 + 1][SIZE/2 + 1]);
    }
    delete board;
}