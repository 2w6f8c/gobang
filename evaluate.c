//
// �����㷨�����ο�https://github.com/lihongxun945/gobang/blob/master/src/ai/evaluate-point.js
//

#include "evaluate.h"
#include <stdlib.h>
#include <windows.h>

#include <stdio.h>

int times = 0;
int score[2][BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1] = {0};

/**
 * ��O��ʾ��ǰ��ɫ�����ӣ�X��ʾ��һ�������ӻ�߽磬_��ʾ��λ
 * ��__OOO_�У�empty=-1��count=3��block=0
 * ��__OOOX�У�empty=-1��count=3��block=1
 * ��XO_OOX�У�empty=1��count=3��block=2
 * @param count role��Ӧ�����ӵĸ���
 * @param block һ���嵽��߽�򱻶������ӵ�ס�Ķ˵ĸ���
 * @param empty һ�����п�λ��λ��
 * @return
 */
static int CastToScore(int count, int block, int empty) {
    //û�п�λ
    if (empty <= 0) {
        if (count >= 5) return SCORE_FIVE; // OOOOO
        if (block == 0) {
            switch (count) {
                case 1:
                    return SCORE_ONE; // _O_
                case 2:
                    return SCORE_TWO; // _OO_
                case 3:
                    return SCORE_THREE; // _OOO_
                case 4:
                    return SCORE_FOUR; // _OOOO_
            }
        }

        if (block == 1) {
            switch (count) {
                case 1:
                    return SCORE_BLOCKED_ONE; // _OX
                case 2:
                    return SCORE_BLOCKED_TWO; // _OOX
                case 3:
                    return SCORE_BLOCKED_THREE; // _OOOX
                case 4:
                    return SCORE_BLOCKED_FOUR; // _OOOOX
            }
        }

    } else if (empty == 1 || empty == count - 1) {
        //��1���ǿ�λ
        if (count >= 6) {
            return SCORE_FIVE; // O_OOOOO or OOOOO_O
        }
        if (block == 0) {
            switch (count) {
                case 2:
                    return SCORE_TWO / 2; // _O_O_
                case 3:
                    return SCORE_THREE; // _O_OO_
                case 4:
                    return SCORE_BLOCKED_FOUR; // _O_OOO_
                case 5:
                    return SCORE_FOUR; // _O_OOOO_
            }
        }

        // ���治�پ���
        if (block == 1) {
            switch (count) {
                case 2:
                    return SCORE_BLOCKED_TWO;
                case 3:
                    return SCORE_BLOCKED_THREE;
                case 4:
                    return SCORE_BLOCKED_FOUR;
                case 5:
                    return SCORE_BLOCKED_FOUR;
            }
        }
    } else if (empty == 2 || empty == count - 2) {
        //�ڶ����ǿ�λ
        if (count >= 7) {
            return SCORE_FIVE;
        }
        if (block == 0) {
            switch (count) {
                case 3:
                    return SCORE_THREE;
                case 4:
                case 5:
                    return SCORE_BLOCKED_FOUR;
                case 6:
                    return SCORE_FOUR;
            }
        }

        if (block == 1) {
            switch (count) {
                case 3:
                    return SCORE_BLOCKED_THREE;
                case 4:
                    return SCORE_BLOCKED_FOUR;
                case 5:
                    return SCORE_BLOCKED_FOUR;
                case 6:
                    return SCORE_FOUR;
            }
        }

        if (block == 2) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                    return SCORE_BLOCKED_FOUR;
            }
        }
    } else if (empty == 3 || empty == count - 3) {
        if (count >= 8) {
            return SCORE_FIVE;
        }
        if (block == 0) {
            switch (count) {
                case 4:
                case 5:
                    return SCORE_THREE;
                case 6:
                    return SCORE_BLOCKED_FOUR;
                case 7:
                    return SCORE_FOUR;
            }
        }

        if (block == 1) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                    return SCORE_BLOCKED_FOUR;
                case 7:
                    return SCORE_FOUR;
            }
        }

        if (block == 2) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                case 7:
                    return SCORE_BLOCKED_FOUR;
            }
        }
    } else if (empty == 4 || empty == count - 4) {
        if (count >= 9) {
            return SCORE_FIVE;
        }
        if (block == 0) {
            switch (count) {
                case 5:
                case 6:
                case 7:
                case 8:
                    return SCORE_FOUR;
            }
        }

        if (block == 1) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                case 7:
                    return SCORE_BLOCKED_FOUR;
                case 8:
                    return SCORE_FOUR;
            }
        }

        if (block == 2) {
            switch (count) {
                case 5:
                case 6:
                case 7:
                case 8:
                    return SCORE_BLOCKED_FOUR;
            }
        }
    } else if (empty == 5 || empty == count - 5) {
        return SCORE_FIVE;
    }

    return 0;
}

static void Reset(int *count, int *block, int *empty, int *secondCount) {
    *count = 1;
    *block = 0;
    *empty = -1;
    *secondCount = 0;
}

// �����ڵ�ǰλ�����Ӻ�õ��ķ���
// �����ǰλ�ò��Ǽ������ӣ��򽫵�ǰ��ɫ�ڴ�λ�õĵ÷���Ϊ0
static int UpdateSingleScore(POINT point, int role) {
    int px = point.x, py = point.y;
    score[role][px][py] = 0;

    if (board[px][py] != role) return 0;

    // empty��¼һ�����п�λ��λ�ã�count��role��Ӧ�����ӵĸ�����block��ʾ�����嵽��߽�򱻶������ӵ�ס�Ķ˵ĸ���
    // ��X��ʾ��ǰ��ɫ�����ӣ�O��ʾ��һ�������ӻ�߽磬_��ʾ��λ
    // ��__XXX_�У�empty=-1��count=3��block=0
    // ��__XXXO�У�empty=-1��count=3��block=1
    // ��OX_XXO�У�empty=1��count=3��block=2
    int empty = 0, count = 0, block = 0, secondCount = 0;
    int len = BOARD_CELL_NUM + 1;

    // -��
    Reset(&count, &block, &empty, &secondCount);
    for (int i = py + 1;; i++) {
        // ������
        if (i >= len) {
            block++;
            break;
        }
        int t = board[px][i];
        if (t == NULL_FLAG) {
            if (empty == -1 && i < len - 1 && board[px][i + 1] == role) {
                empty = count;
                continue;
            } else {
                break;
            }
        }
        if (t == role) {
            count++;
            continue;
        } else {
            block++;
            break;
        }
    }

    for (int i = py - 1;; i--) {
        if (i < 0) {
            block++;
            break;
        }
        int t = board[px][i];
        if (t == NULL_FLAG) {
            if (empty == -1 && i > 0 && board[px][i - 1] == role) {
                empty = 0;
                continue;
            } else {
                break;
            }
        }
        // �����߶����һ�����ӣ���ôemptyλ�ü�1
        if (t == role) {
            // ��һ�ߵ����Ӹ���
            secondCount++;
            empty != -1 && empty++;
            continue;
        } else {
            block++;
            break;
        }
    }

    count += secondCount;
    score[role][px][py] += CastToScore(count, block, empty);


    // |��
    Reset(&count, &block, &empty, &secondCount);
    for (int i = px + 1;; i++) {
        if (i >= len) {
            block++;
            break;
        }
        int t = board[i][py];
        if (t == NULL_FLAG) {
            if (empty == -1 && i < len - 1 && board[i + 1][py] == role) {
                empty = count;
                continue;
            } else {
                break;
            }
        }
        if (t == role) {
            count++;
            continue;
        } else {
            block++;
            break;
        }
    }

    for (int i = px - 1;; i--) {
        if (i < 0) {
            block++;
            break;
        }
        int t = board[i][py];
        if (t == NULL_FLAG) {
            if (empty == -1 && i > 0 && board[i - 1][py] == role) {
                empty = 0;
                continue;
            } else {
                break;
            }
        }
        if (t == role) {
            secondCount++;
            empty != -1 && empty++;
            continue;
        } else {
            block++;
            break;
        }
    }

    count += secondCount;
    score[role][px][py] += CastToScore(count, block, empty);


    // \��
    Reset(&count, &block, &empty, &secondCount);
    for (int i = 1;; i++) {
        int x = px + i, y = py + i;
        if (x >= len || y >= len) {
            block++;
            break;
        }
        int t = board[x][y];
        if (t == NULL_FLAG) {
            if (empty == -1 && (x < len - 1 && y < len - 1) && board[x + 1][y + 1] == role) {
                empty = count;
                continue;
            } else {
                break;
            }
        }
        if (t == role) {
            count++;
            continue;
        } else {
            block++;
            break;
        }
    }

    for (int i = 1;; i++) {
        int x = px - i, y = py - i;
        if (x < 0 || y < 0) {
            block++;
            break;
        }
        int t = board[x][y];
        if (t == NULL_FLAG) {
            if (empty == -1 && (x > 0 && y > 0) && board[x - 1][y - 1] == role) {
                empty = 0;
                continue;
            } else {
                break;
            }
        }
        if (t == role) {
            secondCount++;
            empty != -1 && empty++;
            continue;
        } else {
            block++;
            break;
        }
    }

    count += secondCount;
    score[role][px][py] += CastToScore(count, block, empty);


    // /��
    Reset(&count, &block, &empty, &secondCount);
    for (int i = 1;; i++) {
        int x = px + i, y = py - i;
        if (x < 0 || y < 0 || x >= len || y >= len) {
            block++;
            break;
        }
        int t = board[x][y];
        if (t == NULL_FLAG) {
            if (empty == -1 && (x < len - 1 && y > 0) && board[x + 1][y - 1] == role) {
                empty = count;
                continue;
            } else {
                break;
            }
        }
        if (t == role) {
            count++;
            continue;
        } else {
            block++;
            break;
        }
    }

    for (int i = 1;; i++) {
        int x = px - i, y = py + i;
        if (x < 0 || y < 0 || x >= len || y >= len) {
            block++;
            break;
        }
        int t = board[x][y];
        if (t == NULL_FLAG) {
            if (empty == -1 && (x > 0 && y < len - 1) && board[x - 1][y + 1] == role) {
                empty = 0;
                continue;
            } else {
                break;
            }
        }
        if (t == role) {
            secondCount++;
            empty != -1 && empty++;
            continue;
        } else {
            block++;
            break;
        }
    }

    count += secondCount;
    score[role][px][py] += CastToScore(count, block, empty);

    return score[role][px][py];
}


// �ڵ�ǰλ�����Ӻ󣬸��µ�ǰλ�ü�����λ�õ�����
void UpdateScore(POINT point) {
    int radius = 4;
    int px = point.x, py = point.y;
    int len = BOARD_CELL_NUM + 1;
    POINT tmp;

    // ����(px, py)�ķ���
    UpdateSingleScore(point, AI_FLAG);
    UpdateSingleScore(point, PLAYER_FLAG);

    // -��
    tmp.x = px;
    for (int i = py + 1; i < len && i <= py + radius; i++) {
        tmp.y = i;
        UpdateSingleScore(tmp, AI_FLAG);
        UpdateSingleScore(tmp, PLAYER_FLAG);
    }

    for (int i = py - 1; i >= 0 && i >= py - radius; i--) {
        tmp.y = i;
        UpdateSingleScore(tmp, AI_FLAG);
        UpdateSingleScore(tmp, PLAYER_FLAG);
    }

    // |��
    tmp.y = py;
    for (int i = px + 1; i < len && i <= px + radius; i++) {
        tmp.x = i;
        UpdateSingleScore(tmp, AI_FLAG);
        UpdateSingleScore(tmp, PLAYER_FLAG);
    }

    for (int i = px - 1; i >= 0 && i >= px - radius; i--) {
        tmp.x = i;
        UpdateSingleScore(tmp, AI_FLAG);
        UpdateSingleScore(tmp, PLAYER_FLAG);
    }

    // \��
    for (int i = 1; i <= radius && (py + i) < len && (px + i) < len; i++) {
        tmp.x = px + i;
        tmp.y = py + i;
        UpdateSingleScore(tmp, AI_FLAG);
        UpdateSingleScore(tmp, PLAYER_FLAG);
    }

    for (int i = 1; i <= radius && (py - i) >= 0 && (px - i) >= 0; i++) {
        tmp.x = px - i;
        tmp.y = py - i;
        UpdateSingleScore(tmp, AI_FLAG);
        UpdateSingleScore(tmp, PLAYER_FLAG);
    }

    // /��
    for (int i = 1; i <= radius && (py + i) < len && (px - i) >= 0; i++) {
        tmp.x = px - i;
        tmp.y = py + i;
        UpdateSingleScore(tmp, AI_FLAG);
        UpdateSingleScore(tmp, PLAYER_FLAG);
    }

    for (int i = 1; i <= radius && (py - i) >= 0 && (px + i) < len; i++) {
        tmp.x = px + i;
        tmp.y = py - i;
        UpdateSingleScore(tmp, AI_FLAG);
        UpdateSingleScore(tmp, PLAYER_FLAG);
    }
}


// ��������
int Evaluate() {
    ++times;

    int ans = 0;
    int n = BOARD_CELL_NUM + 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans += score[AI_FLAG][i][j] - score[PLAYER_FLAG][i][j];
        }
    }

    return ans;
}


