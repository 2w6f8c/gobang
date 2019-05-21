#include "draw.h"
#include "def.h"
#include "util.h"

// ���ƺ�ɫʵ�ĵ�
HRESULT DrawBlackSolidPoint(HDC hdc, int radius, POINT position) {
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    Ellipse(hdc, position.x - radius, position.y - radius, position.x + radius, position.y + radius);
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));

    return S_OK;
}

// ���ư�ɫ���ĵ�
HRESULT DrawWhiteHollowPoint(HDC hdc, int radius, POINT position) {
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    Ellipse(hdc, position.x - radius, position.y - radius, position.x + radius, position.y + radius);

    return S_OK;
}

// ��������
HRESULT DrawChessBoard(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient) {
    // ���һС��Ŀ�Ⱥ͸߶�
    int cxCell = 0, cyCell = 0;
    GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
    // ��������
    for (int col = 0; col < BOARD_CELL_NUM + 1; ++col) {
        MoveToEx(hdc, ptLeftTop.x + col * cxCell, ptLeftTop.y, NULL);
        LineTo(hdc, ptLeftTop.x + col * cxCell, ptLeftTop.y + BOARD_CELL_NUM * cyCell);
    }
    // ���ƻ�ɫ�ĺ���
    HPEN hPen, hOldPen;
    hPen = CreatePen(PS_SOLID, 1, RGB(190, 190, 190));
    hOldPen = SelectObject(hdc, hPen);
    for (int row = 0; row < 7; ++row) {
        MoveToEx(hdc, ptLeftTop.x, ptLeftTop.y + cyCell + row * 2 * cyCell, NULL);
        LineTo(hdc, ptLeftTop.x + BOARD_CELL_NUM * cxCell, ptLeftTop.y + cyCell + row * 2 * cyCell);
    }
    SelectObject(hdc, hOldPen);
    // ���ƺ�ɫ�ĺ���
    for (int row = 0; row < 8; ++row) {
        MoveToEx(hdc, ptLeftTop.x, ptLeftTop.y + row * 2 * cyCell, NULL);
        LineTo(hdc, ptLeftTop.x + BOARD_CELL_NUM * cxCell, ptLeftTop.y + row * 2 * cyCell);
    }

    return S_OK;
}

// ����������ص�
HRESULT DrawFiveHeavyPoint(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient) {
    // ���һС��Ŀ�Ⱥ͸߶�
    int cxCell = 0, cyCell = 0;
    GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
    // ���߼���ת��Ϊʵ�ʵ�
    POINT logicalPoint[5] = {3, 3, 3, 11, 11, 3, 11, 11, 7, 7};
    POINT actualPoint[5] = {0};
    for (int cPt = 0; cPt < 5; ++cPt) {
        ExchangeActualPosition(logicalPoint[cPt], cxCell, cyCell, ptLeftTop, &actualPoint[cPt]);
    }
    // ���������ɫʵ�ĵ�
    for (int cPt = 0; cPt < 5; ++cPt) {
        DrawBlackSolidPoint(hdc, FIVE_MARK_POINT_RADIUS, actualPoint[cPt]);
    }

    return S_OK;
}