#include "draw.h"
#include "def.h"
#include "engine.h"
#include <math.h>

// 绘制黑色实心点
HRESULT DrawBlackSolidPoint(HDC hdc, int radius, POINT position) {
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    Ellipse(hdc, position.x - radius, position.y - radius, position.x + radius, position.y + radius);
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));

    return S_OK;
}

// 绘制白色空心点
HRESULT DrawWhiteHollowPoint(HDC hdc, int radius, POINT position) {
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    Ellipse(hdc, position.x - radius, position.y - radius, position.x + radius, position.y + radius);

    return S_OK;
}

// 绘制棋盘
HRESULT DrawChessBoard(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient) {
    // 获得一小格的宽度和高度
    int cxCell = 0, cyCell = 0;
    GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
    // 绘制竖线
    for (int col = 0; col < BOARD_CELL_NUM + 1; ++col) {
        MoveToEx(hdc, ptLeftTop.x + col * cxCell, ptLeftTop.y, NULL);
        LineTo(hdc, ptLeftTop.x + col * cxCell, ptLeftTop.y + BOARD_CELL_NUM * cyCell);
    }
    // 绘制灰色的横线
    HPEN hPen, hOldPen;
    hPen = CreatePen(PS_SOLID, 1, RGB(190, 190, 190));
    hOldPen = SelectObject(hdc, hPen);
    for (int row = 0; row < 7; ++row) {
        MoveToEx(hdc, ptLeftTop.x, ptLeftTop.y + cyCell + row * 2 * cyCell, NULL);
        LineTo(hdc, ptLeftTop.x + BOARD_CELL_NUM * cxCell, ptLeftTop.y + cyCell + row * 2 * cyCell);
    }
    SelectObject(hdc, hOldPen);
    // 绘制黑色的横线
    for (int row = 0; row < 8; ++row) {
        MoveToEx(hdc, ptLeftTop.x, ptLeftTop.y + row * 2 * cyCell, NULL);
        LineTo(hdc, ptLeftTop.x + BOARD_CELL_NUM * cxCell, ptLeftTop.y + row * 2 * cyCell);
    }

    return S_OK;
}

// 绘制五个着重点
HRESULT DrawFiveHeavyPoint(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient) {
    // 获得一小格的宽度和高度
    int cxCell = 0, cyCell = 0;
    GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
    // 将逻辑点转换为实际点
    POINT logicalPoint[5] = {3, 3, 3, 11, 11, 3, 11, 11, 7, 7};
    POINT actualPoint[5] = {0};
    for (int cPt = 0; cPt < 5; ++cPt) {
        ExchangeActualPosition(logicalPoint[cPt], cxCell, cyCell, ptLeftTop, &actualPoint[cPt]);
    }
    // 绘制五个黑色实心点
    for (int cPt = 0; cPt < 5; ++cPt) {
        DrawBlackSolidPoint(hdc, FIVE_MARK_POINT_RADIUS, actualPoint[cPt]);
    }

    return S_OK;
}

// 获取一小格宽度和高度
HRESULT GetCellWidthAndHeight(POINT ptLeftTop, int cxClient, int cyClient, int *cxCell, int *cyCell) {
    *cxCell = (cxClient - ptLeftTop.x * 2) / BOARD_CELL_NUM;
    *cyCell = (cyClient - ptLeftTop.y * 2) / BOARD_CELL_NUM;

    return S_OK;
}

// 将实际坐标转化为逻辑坐标，这里需要进行实际点到棋盘点的转化
HRESULT
ExChangeLogicalPosition(POINT actualPosition, POINT ptLeftTop, int cxClient, int cyClient, POINT *logicalPosition) {
    // 获得一小格的宽度和高度
    int cxCell = 0, cyCell = 0;
    GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
    // 检查点击有效性
    if (actualPosition.x < ptLeftTop.x || actualPosition.x > ptLeftTop.x + BOARD_CELL_NUM * cxCell ||
        actualPosition.y < ptLeftTop.y || actualPosition.y > ptLeftTop.y + BOARD_CELL_NUM * cyCell) {
        MessageBox(NULL, TEXT("请点击棋盘内下棋！"), TEXT("提示"), MB_OK);
        return S_FALSE;
    }
    // 获取相邻四个点
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
    // 计算当前点到四个点到当前点距离
    double lengthCount[4] = {0};
    for (int item = 0; item < 4; ++item) {
        lengthCount[item] =
                pow(abs(sidePoints[item].x - actualPosition.x), 2) + pow(abs(sidePoints[item].y - actualPosition.y), 2);
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
    logicalPosition->x = xCount;
    logicalPosition->y = yCount;

    return S_OK;
}

// 将逻辑坐标转化为实际坐标
HRESULT ExchangeActualPosition(POINT logicalPos, int cxCell, int cyCell, POINT ptLeftTop, POINT *actualPos) {
    actualPos->x = ptLeftTop.x + logicalPos.x * cxCell;
    actualPos->y = ptLeftTop.y + logicalPos.y * cyCell;

    return S_OK;
}