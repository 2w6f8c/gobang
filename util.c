#include "util.h"
#include <math.h>

// 获取一小格宽度和高度
HRESULT GetCellWidthAndHeight(POINT ptLeftTop, int cxClient, int cyClient, int *cxCell, int *cyCell) {
    *cxCell = (cxClient - ptLeftTop.x * 2) / BOARD_CELL_NUM;
    *cyCell = (cyClient - ptLeftTop.y * 2) / BOARD_CELL_NUM;

    return S_OK;
}

// 将实际坐标转化为逻辑坐标，这里需要进行实际点到棋盘点的转化
HRESULT
ExChangeLogicalPosition(POINT actualPostion, POINT ptLeftTop, int cxClient, int cyClient, POINT *logicalPostion) {
    // 获得一小格的宽度和高度
    int cxCell = 0, cyCell = 0;
    GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
    // 检查点击有效性
    if (actualPostion.x < ptLeftTop.x || actualPostion.x > ptLeftTop.x + BOARD_CELL_NUM * cxCell ||
        actualPostion.y < ptLeftTop.y || actualPostion.y > ptLeftTop.y + BOARD_CELL_NUM * cyCell) {
        MessageBox(NULL, TEXT("请点击棋盘内下棋！"), TEXT("提示"), MB_OK);
        return S_FALSE;
    }
    // 获取相邻四个点
    int xCount = 0, yCount = 0;
    POINT sidePoints[4] = {0};
    for (int x = ptLeftTop.x; x <= ptLeftTop.x + BOARD_CELL_NUM * cxCell; x += cxCell, xCount++) {
        if (actualPostion.x >= x && actualPostion.x <= x + cxCell) {
            sidePoints[0].x = x;
            sidePoints[2].x = x;
            sidePoints[1].x = x + cxCell;
            sidePoints[3].x = x + cxCell;
            break;
        }
    }
    for (int y = ptLeftTop.y; y <= ptLeftTop.y + BOARD_CELL_NUM * cyCell; y += cyCell, yCount++) {
        if (actualPostion.y >= y && actualPostion.y <= y + cyCell) {
            sidePoints[0].y = y;
            sidePoints[1].y = y;
            sidePoints[2].y = y + cyCell;
            sidePoints[3].y = y + cyCell;
            break;
        }
    }
    // 计算当前点到四个点到当前点距离
    double lengthCount[4] = {0};
    for (int item = 0; item < 4; ++item) {
        lengthCount[item] =
                pow(abs(sidePoints[item].x - actualPostion.x), 2) + pow(abs(sidePoints[item].y - actualPostion.y), 2);
    }
    // 获取四个距离值中最短的一个
    int shortestIndex = 0;
    for (int item = 0; item < 4; ++item) {
        if (lengthCount[item] < lengthCount[shortestIndex]) {
            shortestIndex = item;
        }
    }
    // 计算逻辑坐标，其中下标为0的点为基准点
    if (1 == shortestIndex) {
        xCount += 1;
    } else if (2 == shortestIndex) {
        yCount += 1;
    } else if (3 == shortestIndex) {
        xCount += 1;
        yCount += 1;
    }
    logicalPostion->x = xCount;
    logicalPostion->y = yCount;

    return S_OK;
}

// 将逻辑坐标转化为实际坐标
HRESULT ExchangeActualPositon(POINT logicalPos, int cxCell, int cyCell, POINT ptLeftTop, POINT *actualPos) {
    actualPos->x = ptLeftTop.x + logicalPos.x * cxCell;
    actualPos->y = ptLeftTop.y + logicalPos.y * cyCell;

    return S_OK;
}


// 判断当前逻辑点的指定方向上是否有相邻点
HRESULT
IsSidewardHasSamePoint(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point, GameDirection direction,
                       BOOLEAN *bSame, POINT *movedPoint) {
    // 记录当前点的值
    int curSideValue = chessPoints[point.x][point.y];
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
        *bSame = curSideValue == chessPoints[point.x][point.y];
        movedPoint->x = point.x;
        movedPoint->y = point.y;
    }

    return S_OK;
}

// 计算当前方向过去的同类棋子的个数
HRESULT CountSameDiretionPointsNumber(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point,
                                      GameDirection direction, int *count) {
    (*count) += 1;
    BOOLEAN bSame = FALSE;
    POINT movedPoint = {point.x, point.y};
    IsSidewardHasSamePoint(chessPoints, point, direction, &bSame, &movedPoint);
    if (bSame == TRUE) {
        bSame = FALSE;
        POINT movedmovedPoint = {movedPoint.x, movedPoint.y};
        CountSameDiretionPointsNumber(chessPoints, movedPoint, direction, count);
    }

    return S_OK;
}

// 判定是否胜利
HRESULT IsSomeoneWin(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], int *winner) {
    // 计算连续竖着的胜利
    for (int row = 0; row < BOARD_CELL_NUM + 1; ++row) {
        for (int col = 0; col < BOARD_CELL_NUM + 1; ++col) {
            if (chessPoints[row][col] != NULL_FLAG) {
                POINT point = {row, col};
                for (size_t direction = 0; direction < 8; ++direction) {
                    // 获取当前点此方向的最大同类棋子数
                    int count = 0;
                    CountSameDiretionPointsNumber(chessPoints, point, direction, &count);
                    // 判定是否胜利
                    if (count >= 5) {
                        if (chessPoints[row][col] == BLACK_FLAG) {
                            MessageBox(NULL, TEXT("黑棋获胜！"), TEXT("提示"), MB_OK);
                        } else if (chessPoints[row][col] == WHITE_FLAG) {
                            MessageBox(NULL, TEXT("白棋获胜！"), TEXT("提示"), MB_OK);
                        }
                    }
                }
            }
        }
    }

    return S_OK;
}