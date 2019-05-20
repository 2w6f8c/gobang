//
// Created by 2w6f8c on 2019/5/20.
//

#include "randomPlay.h"
#include <stdlib.h>
#include <time.h>

/**
 * 电脑随机下棋，仅用于测试
 * @param chessPoints
 * @return
 */
POINT RandomPlay(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1]) {
    srand(time(0));
    POINT point;
    int count = 0;
    for (int i = 0; i < BOARD_CELL_NUM + 1; i++)
        for (int j = 0; j < BOARD_CELL_NUM + 1; j++)
            if (chessPoints[i][j] == NULL_FLAG) count++;


    int index = rand() % count;
    count = 0;
    for (int i = 0; i < BOARD_CELL_NUM + 1; i++) {
        for (int j = 0; j < BOARD_CELL_NUM + 1; j++) {
            if (chessPoints[i][j] == NULL_FLAG) count++;
            if (count == index + 1) {
                point.x = i;
                point.y = j;
                return point;
            }
        }
    }
}



