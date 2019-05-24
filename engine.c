#include "engine.h"

// 判断当前逻辑点的指定方向上是否有相邻点
HRESULT
IsSidewardHasSamePoint(POINT point, GameDirection direction,
                       BOOLEAN *bSame, POINT *movedPoint) {
    // 记录当前点的值
    int curSideValue = board[point.x][point.y];
    // 计算该方向的下一个逻辑点坐标
    switch (direction) {
        case Direction_Top: {
            point.y -= 1;
            break;
        }

        case Direction_RightTop: {
            point.x += 1;
            point.y -= 1;
            break;
        }

        case Direction_Right: {
            point.x += 1;
            break;
        }

        case Direction_RightBottom: {
            point.x += 1;
            point.y += 1;
            break;
        }

        case Direction_Bottom: {
            point.y += 1;
            break;
        }

        case Direction_LeftBottom: {
            point.x -= 1;
            point.y += 1;
            break;
        }

        case Direction_Left: {
            point.x -= 1;
            break;
        }

        case Direction_LeftTop: {
            point.x -= 1;
            point.y -= 1;
            break;
        }
    }
    // 返回是否相同
    if (point.x >= 0 && point.x < BOARD_CELL_NUM + 1 && point.y >= 0 && point.y < BOARD_CELL_NUM + 1) {
        *bSame = curSideValue == board[point.x][point.y];
        movedPoint->x = point.x;
        movedPoint->y = point.y;
    }

    return S_OK;
}

// 计算当前方向过去的同类棋子的个数
HRESULT CountSameDirectionPointsNumber(POINT point,
                                      GameDirection direction, int *count) {
    (*count) += 1;
    BOOLEAN bSame = FALSE;
    POINT movedPoint = {point.x, point.y};
    IsSidewardHasSamePoint(point, direction, &bSame, &movedPoint);
    if (bSame == TRUE) {
        bSame = FALSE;
        CountSameDirectionPointsNumber(movedPoint, direction, count);
    }

    return S_OK;
}

// 判定是否胜利
HRESULT IsSomeoneWin(int *winner) {
    // 计算连续竖着的胜利
    for (int row = 0; row < BOARD_CELL_NUM + 1; ++row) {
        for (int col = 0; col < BOARD_CELL_NUM + 1; ++col) {
            if (board[row][col] != NULL_FLAG) {
                POINT point = {row, col};
                for (size_t direction = 0; direction < 8; ++direction) {
                    // 获取当前点此方向的最大同类棋子数
                    int count = 0;
                    CountSameDirectionPointsNumber(point, direction, &count);
                    // 判定是否胜利
                    if (count >= 5) {
                        *winner = board[row][col];
                    }
                }
            }
        }
    }

    return S_OK;
}

void PrintBoard() {
    for(int i = 0; i < BOARD_CELL_NUM + 1; i++) {
        for(int j = 0; j < BOARD_CELL_NUM + 1; j++) {
            printf("%d ", board[j][i]);
        }
        printf("\n");
    }
}