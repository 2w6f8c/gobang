//
// Created by 2w6f8c on 2019/5/20.
//

#include "alphaBeta.h"
#include "evaluate.h"
#include "engine.h"
#include <stdio.h>
#include <time.h>

extern int times;

static double start = 0.0;
static int alphaCount = 0;
static int betaCount = 0;

// ��-�¼�֦�㷨
static int AlphaBeta(int role, int depth, int alpha, int beta) {
    if (depth == 0) return Evaluate();

    int n = BOARD_CELL_NUM + 1;
    POINT point;

    if (role == AI_FLAG) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == NULL_FLAG) {
                    point.x = i;
                    point.y = j;
                    PutChess(point, AI_FLAG);
                    int ans = AlphaBeta(PLAYER_FLAG, depth - 1, alpha, beta);
                    UnPutChess(point);
                    if (ans > alpha) alpha = ans;
                    if (alpha >= beta) {
                        ++alphaCount;
                        return alpha;
                    }
                }
            }
        }
        return alpha;
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == NULL_FLAG) {
                    point.x = i;
                    point.y = j;
                    PutChess(point, PLAYER_FLAG);
                    int ans = AlphaBeta(AI_FLAG, depth - 1, alpha, beta);
                    UnPutChess(point);
                    if (ans < beta) beta = ans;
                    if (alpha >= beta) {
                        ++betaCount;
                        return beta;
                    }
                }
            }
        }
        return beta;
    }

}

// ͨ����-�¼�֦�㷨�õ���һ������λ��
POINT NextPoint(int depth) {

    times = 0;
    alphaCount = 0;
    betaCount = 0;
    start = clock();

    int alpha = -2147483648;
    int beta = 2147483647;

    int n = BOARD_CELL_NUM + 1;
    POINT point, result;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == NULL_FLAG) {
                point.x = i;
                point.y = j;
                PutChess(point, AI_FLAG);
                int ans = AlphaBeta(PLAYER_FLAG, depth - 1, alpha, beta);
                UnPutChess(point);
                if (ans > alpha) {
                    alpha = ans;
                    result.x = i;
                    result.y = j;
                }
            }
        }

    }

    printf("�������: %d\n", ALPHA_BETA_DEPTH);
    printf("����֦����: %d\n", alphaCount);
    printf("�¼�֦����: %d\n", betaCount);
    printf("������ִ���: %d\n", times);
    printf("��ʱ: %.3fs\n", (clock() - start) / CLOCKS_PER_SEC);

    return result;

}

