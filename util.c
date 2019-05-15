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
ExChangeLogicalPosition(POINT actualPostion, POINT ptLeftTop, int cxClient, int cyClient, POINT *logicalPostion) {
    // ���һС��Ŀ�Ⱥ͸߶�
    int cxCell = 0, cyCell = 0;
    GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
    // �������Ч��
    if (actualPostion.x < ptLeftTop.x || actualPostion.x > ptLeftTop.x + BOARD_CELL_NUM * cxCell ||
        actualPostion.y < ptLeftTop.y || actualPostion.y > ptLeftTop.y + BOARD_CELL_NUM * cyCell) {
        MessageBox(NULL, TEXT("�������������壡"), TEXT("��ʾ"), MB_OK);
        return S_FALSE;
    }
    // ��ȡ�����ĸ���
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
    // ���㵱ǰ�㵽�ĸ��㵽��ǰ�����
    double lengthCount[4] = {0};
    for (int item = 0; item < 4; ++item) {
        lengthCount[item] =
                pow(abs(sidePoints[item].x - actualPostion.x), 2) + pow(abs(sidePoints[item].y - actualPostion.y), 2);
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
    logicalPostion->x = xCount;
    logicalPostion->y = yCount;

    return S_OK;
}

// ���߼�����ת��Ϊʵ������
HRESULT ExchangeActualPositon(POINT logicalPos, int cxCell, int cyCell, POINT ptLeftTop, POINT *actualPos) {
    actualPos->x = ptLeftTop.x + logicalPos.x * cxCell;
    actualPos->y = ptLeftTop.y + logicalPos.y * cyCell;

    return S_OK;
}


// �жϵ�ǰ�߼����ָ���������Ƿ������ڵ�
HRESULT
IsSidewardHasSamePoint(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point, GameDirection direction,
                       BOOLEAN *bSame, POINT *movedPoint) {
    // ��¼��ǰ���ֵ
    int curSideValue = chessPoints[point.x][point.y];
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
        *bSame = curSideValue == chessPoints[point.x][point.y];
        movedPoint->x = point.x;
        movedPoint->y = point.y;
    }

    return S_OK;
}

// ���㵱ǰ�����ȥ��ͬ�����ӵĸ���
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

// �ж��Ƿ�ʤ��
HRESULT IsSomeoneWin(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], int *winner) {
    // �����������ŵ�ʤ��
    for (int row = 0; row < BOARD_CELL_NUM + 1; ++row) {
        for (int col = 0; col < BOARD_CELL_NUM + 1; ++col) {
            if (chessPoints[row][col] != NULL_FLAG) {
                POINT point = {row, col};
                for (size_t direction = 0; direction < 8; ++direction) {
                    // ��ȡ��ǰ��˷�������ͬ��������
                    int count = 0;
                    CountSameDiretionPointsNumber(chessPoints, point, direction, &count);
                    // �ж��Ƿ�ʤ��
                    if (count >= 5) {
                        if (chessPoints[row][col] == BLACK_FLAG) {
                            MessageBox(NULL, TEXT("�����ʤ��"), TEXT("��ʾ"), MB_OK);
                        } else if (chessPoints[row][col] == WHITE_FLAG) {
                            MessageBox(NULL, TEXT("�����ʤ��"), TEXT("��ʾ"), MB_OK);
                        }
                    }
                }
            }
        }
    }

    return S_OK;
}