#include "draw.h"
#include "def.h"
#include "util.h"

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