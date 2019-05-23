//
// Created by 2w6f8c on 2019/5/20.
//

#include "evaluate.h"
#include <stdlib.h>
#include <windows.h>

#include <stdio.h>

extern int accumulate;

int CastToScore(int count, int block, int empty) {
    //没有空位
    if (empty <= 0) {
        if (count >= 5) return SCORE_FIVE;
        if (block == 0) {
            switch (count) {
                case 1:
                    return SCORE_ONE;
                case 2:
                    return SCORE_TWO;
                case 3:
                    return SCORE_THREE;
                case 4:
                    return SCORE_FOUR;
            }
        }

        if (block == 1) {
            switch (count) {
                case 1:
                    return SCORE_BLOCKED_ONE;
                case 2:
                    return SCORE_BLOCKED_TWO;
                case 3:
                    return SCORE_BLOCKED_THREE;
                case 4:
                    return SCORE_BLOCKED_FOUR;
            }
        }

    } else if (empty == 1 || empty == count - 1) {
        //第1个是空位
        if (count >= 6) {
            return SCORE_FIVE;
        }
        if (block == 0) {
            switch (count) {
                case 2:
                    return SCORE_TWO / 2;
                case 3:
                    return SCORE_THREE;
                case 4:
                    return SCORE_BLOCKED_FOUR;
                case 5:
                    return SCORE_FOUR;
            }
        }

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
        //第二个是空位
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

void Reset(int *count, int *block, int *empty, int *secondCount) {
    *count = 1;
    *block = 0;
    *empty = -1;
    *secondCount = 0;
}

int ScorePoint(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point, int role) {
    int empty = 0, count = 0, block = 0, secondCount = 0;
    int len = BOARD_CELL_NUM + 1;
    int px = point.x, py = point.y;

    scoreCache[role][px][py] = 0;

    // -形
    Reset(&count, &block, &empty, &secondCount);
    for (int i = py + 1;; i++) {
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
    scoreCache[role][px][py] += CastToScore(count, block, empty);


    // |形
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
    scoreCache[role][px][py] += CastToScore(count, block, empty);


    // \形
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
    scoreCache[role][px][py] += CastToScore(count, block, empty);


    // /形
    Reset(&count, &block, &empty, &secondCount);
    for (int i = 1;; i++) {
        int x = px + i, y = py - i;
        if (x < 0 || y < 0 || x >= len || y >= len) {
            block++;
            break;
        }
        int t = board[x][y];
        if (t == NULL_FLAG) {
            if (empty == -1 && (x < len - 1 && y < len - 1) && board[x + 1][y - 1] == role) {
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
            if (empty == -1 && (x > 0 && y > 0) && board[x - 1][y + 1] == role) {
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
    scoreCache[role][px][py] += CastToScore(count, block, empty);


    return scoreCache[role][px][py];

}

// 评估函数
int Evaluate(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1]) {

    accumulate++;

    int ans = 0;
    int n = BOARD_CELL_NUM + 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            POINT point = {i, j};
            ans += ScorePoint(board, point, AI_FLAG) - ScorePoint(board, point, PLAYER_FLAG);
        }
    }

    return ans;
}


