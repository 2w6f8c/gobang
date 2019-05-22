//
// Created by 2w6f8c on 2019/5/20.
//

#include "alphaBeta.h"
#include "evaluate.h"

#include <stdio.h>

extern accumulate;


int AlphaBeta(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], int role, int depth, int alpha, int beta) {
    if (depth == 0) return Evaluate(board);

    int n = BOARD_CELL_NUM + 1;

    if (role == AI_FLAG) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == NULL_FLAG) {
                    board[i][j] = AI_FLAG;
                    int ans = AlphaBeta(board, PLAYER_FLAG, depth - 1, alpha, beta);
                    board[i][j] = NULL_FLAG;
                    if (ans > alpha) alpha = ans;
                    if (alpha >= beta) return alpha;
                }
            }
        }
        return alpha;
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == NULL_FLAG) {
                    board[i][j] = PLAYER_FLAG;
                    int ans = AlphaBeta(board, AI_FLAG, depth - 1, alpha, beta);
                    board[i][j] = NULL_FLAG;
                    if (ans < beta) beta = ans;
                    if (alpha >= beta) return beta;
                }
            }
        }
        return beta;
    }

}

POINT NextPoint(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], int depth) {

    accumulate = 0;

    int alpha = -2147483648;
    int beta = 2147483647;

    int n = BOARD_CELL_NUM + 1;
    POINT point;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == NULL_FLAG) {
                board[i][j] = AI_FLAG;
                int ans = AlphaBeta(board, PLAYER_FLAG, depth - 1, alpha, beta);
                board[i][j] = NULL_FLAG;
                if (ans > alpha) {
                    alpha = ans;
                    point.x = i;
                    point.y = j;
                }
            }
        }

    }

    printf("times: %d\n", accumulate);

    return point;

}

