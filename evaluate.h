//
// Created by 2w6f8c on 2019/5/20.
//

#ifndef GOBANG_EVALUATE_H
#define GOBANG_EVALUATE_H

#define SCORE_ONE 10
#define SCORE_TWO 100
#define SCORE_THREE 1000
#define SCORE_FOUR 100000
#define SCORE_FIVE 10000000
#define SCORE_BLOCKED_ONE 1
#define SCORE_BLOCKED_TWO 10
#define SCORE_BLOCKED_THREE 100
#define SCORE_BLOCKED_FOUR 1000


#include "def.h"

// ÆÀ¹Àº¯Êý
int Evaluate(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1]);

#endif //GOBANG_EVALUATE_H
