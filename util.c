#include "util.h"
#include <math.h>

// ��ȡһС���Ⱥ͸߶�
HRESULT GetCellWidthAndHeight(POINT ptLeftTop, int cxClient, int cyClient, int *cxCell, int *cyCell) {
    *cxCell = (cxClient - ptLeftTop.x * 2) / BOARD_CELL_NUM;
    *cyCell = (cyClient - ptLeftTop.y * 2) / BOARD_CELL_NUM;

    return S_OK;
}

// ��ʵ������ת��Ϊ�߼����꣬������Ҫ����ʵ�ʵ㵽���̵��ת��
HRESULT
ExChangeLogicalPosition(POINT actualPosition, POINT ptLeftTop, int cxClient, int cyClient, POINT *logicalPosition) {
    // ���һС��Ŀ�Ⱥ͸߶�
    int cxCell = 0, cyCell = 0;
    GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
    // �������Ч��
    if (actualPosition.x < ptLeftTop.x || actualPosition.x > ptLeftTop.x + BOARD_CELL_NUM * cxCell ||
        actualPosition.y < ptLeftTop.y || actualPosition.y > ptLeftTop.y + BOARD_CELL_NUM * cyCell) {
        MessageBox(NULL, TEXT("�������������壡"), TEXT("��ʾ"), MB_OK);
        return S_FALSE;
    }
    // ��ȡ�����ĸ���
    int xCount = 0, yCount = 0;
    POINT sidePoints[4] = {0};
    for (int x = ptLeftTop.x; x <= ptLeftTop.x + BOARD_CELL_NUM * cxCell; x += cxCell, xCount++) {
        if (actualPosition.x >= x && actualPosition.x <= x + cxCell) {
            sidePoints[0].x = x;
            sidePoints[2].x = x;
            sidePoints[1].x = x + cxCell;
            sidePoints[3].x = x + cxCell;
            break;
        }
    }
    for (int y = ptLeftTop.y; y <= ptLeftTop.y + BOARD_CELL_NUM * cyCell; y += cyCell, yCount++) {
        if (actualPosition.y >= y && actualPosition.y <= y + cyCell) {
            sidePoints[0].y = y;
            sidePoints[1].y = y;
            sidePoints[2].y = y + cyCell;
            sidePoints[3].y = y + cyCell;
            break;
        }
    }
    // ���㵱ǰ�㵽�ĸ��㵽��ǰ�����
    double lengthCount[4] = {0};
    for (int item = 0; item < 4; ++item) {
        lengthCount[item] =
                pow(abs(sidePoints[item].x - actualPosition.x), 2) + pow(abs(sidePoints[item].y - actualPosition.y), 2);
    }
    // ��ȡ�ĸ�����ֵ����̵�һ��
    int shortestIndex = 0;
    for (int item = 0; item < 4; ++item) {
        if (lengthCount[item] < lengthCount[shortestIndex]) {
            shortestIndex = item;
        }
    }
    // �����߼����꣬�����±�Ϊ0�ĵ�Ϊ��׼��
    if (1 == shortestIndex) {
        xCount += 1;
    } else if (2 == shortestIndex) {
        yCount += 1;
    } else if (3 == shortestIndex) {
        xCount += 1;
        yCount += 1;
    }
    logicalPosition->x = xCount;
    logicalPosition->y = yCount;

    return S_OK;
}

// ���߼�����ת��Ϊʵ������
HRESULT ExchangeActualPosition(POINT logicalPos, int cxCell, int cyCell, POINT ptLeftTop, POINT *actualPos) {
    actualPos->x = ptLeftTop.x + logicalPos.x * cxCell;
    actualPos->y = ptLeftTop.y + logicalPos.y * cyCell;

    return S_OK;
}


// �жϵ�ǰ�߼����ָ���������Ƿ������ڵ�
HRESULT
IsSidewardHasSamePoint(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point, GameDirection direction,
                       BOOLEAN *bSame, POINT *movedPoint) {
    // ��¼��ǰ���ֵ
    int curSideValue = board[point.x][point.y];
    // ����÷������һ���߼�������
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
    // �����Ƿ���ͬ
    if (point.x >= 0 && point.x < BOARD_CELL_NUM + 1 && point.y >= 0 && point.y < BOARD_CELL_NUM + 1) {
        *bSame = curSideValue == board[point.x][point.y];
        movedPoint->x = point.x;
        movedPoint->y = point.y;
    }

    return S_OK;
}

// ���㵱ǰ�����ȥ��ͬ�����ӵĸ���
HRESULT CountSameDirectionPointsNumber(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point,
                                      GameDirection direction, int *count) {
    (*count) += 1;
    BOOLEAN bSame = FALSE;
    POINT movedPoint = {point.x, point.y};
    IsSidewardHasSamePoint(board, point, direction, &bSame, &movedPoint);
    if (bSame == TRUE) {
        bSame = FALSE;
//        POINT movedPoint = {movedPoint.x, movedPoint.y};
        CountSameDirectionPointsNumber(board, movedPoint, direction, count);
    }

    return S_OK;
}

// �ж��Ƿ�ʤ��
HRESULT IsSomeoneWin(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], int *winner) {
    // �����������ŵ�ʤ��
    for (int row = 0; row < BOARD_CELL_NUM + 1; ++row) {
        for (int col = 0; col < BOARD_CELL_NUM + 1; ++col) {
            if (board[row][col] != NULL_FLAG) {
                POINT point = {row, col};
                for (size_t direction = 0; direction < 8; ++direction) {
                    // ��ȡ��ǰ��˷�������ͬ��������
                    int count = 0;
                    CountSameDirectionPointsNumber(board, point, direction, &count);
                    // �ж��Ƿ�ʤ��
                    if (count >= 5) {
                        if (board[row][col] == PLAYER_FLAG) {
                            MessageBox(NULL, TEXT("�����ʤ��"), TEXT("��ʾ"), MB_OK);
                        } else if (board[row][col] == AI_FLAG) {
                            MessageBox(NULL, TEXT("�����ʤ��"), TEXT("��ʾ"), MB_OK);
                        }
                    }
                }
            }
        }
    }

    return S_OK;
}