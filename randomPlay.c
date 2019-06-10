#include "randomPlay.h"
#include <stdlib.h>

/**
 * 电脑随机下棋，仅用于测试
 * @param board
 * @return
 */
POINT RandomPlay() {
    POINT point;
    int count = 0;
    for (int i = 0; i < BOARD_CELL_NUM + 1; i++)
        for (int j = 0; j < BOARD_CELL_NUM + 1; j++)
            if (board[i][j] == NULL_FLAG) count++;


    int index = rand() % count;
    count = 0;
    for (int i = 0; i < BOARD_CELL_NUM + 1; i++) {
        for (int j = 0; j < BOARD_CELL_NUM + 1; j++) {
            if (board[i][j] == NULL_FLAG) count++;
            if (count == index + 1) {
                point.x = i;
                point.y = j;
                return point;
            }
        }
    }
}



