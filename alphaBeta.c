//
// Created by 2w6f8c on 2019/5/20.
//

#include "alphaBeta.h"
#include "evaluate.h"

int AlphaBeta(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], int player, int depth, int alpha, int beta) {
    if (depth == 0) return evaluate(chessPoints, player);

    int n = BOARD_CELL_NUM + 1;

    if (player == AI_FLAG) {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                if (chessPoints[i][j] == NULL_FLAG) {
                    chessPoints[i][j] = AI_FLAG;
                    int ans = AlphaBeta(chessPoints, PLAYER_FLAG, --depth, alpha, beta);
                    chessPoints[i][j] = NULL_FLAG;
                    if (ans > alpha) alpha = ans;
                    if (alpha >= beta) return alpha;
                }
            }
        }
        return alpha;
    }else {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                if (chessPoints[i][j] == NULL_FLAG) {
                    chessPoints[i][j] = PLAYER_FLAG;
                    int ans = AlphaBeta(chessPoints, AI_FLAG, --depth, alpha, beta);
                    chessPoints[i][j] = NULL_FLAG;
                    if (ans < beta) beta = ans;
                    if (alpha >= beta) return alpha;
                }
            }
        }
        return beta;
    }

}

POINT NextPoint(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], int depth, int alpha, int beta) {

    int n = BOARD_CELL_NUM + 1;
    POINT point;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (chessPoints[i][j] == NULL_FLAG) {
                chessPoints[i][j] = AI_FLAG;
                int ans = AlphaBeta(chessPoints, PLAYER_FLAG, --depth, alpha, beta);
                chessPoints[i][j] = NULL_FLAG;
                if (ans > alpha) {
                    alpha = ans;
                    point.x = i;
                    point.y = j;
                }
            }
        }

    }

    return point;

}

