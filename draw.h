#ifndef GAME_DRAW

#define GAME_DRAW

#include<windows.h>

// 绘制黑色实心点
HRESULT DrawBlackSolidPoint(HDC hdc, int radius, POINT position);

// 绘制白色空心点
HRESULT DrawWhiteHollowPoint(HDC hdc, int radius, POINT position);

// 绘制棋盘
HRESULT DrawChessBoard(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient);

// 绘制五个着重点
HRESULT DrawFiveHeavyPoint(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient);

// 获取一小格宽度和高度
HRESULT GetCellWidthAndHeight(POINT ptLeftTop, int cxClient, int cyClient, int *cxCell, int *cyCell);

// 将实际坐标转化为逻辑坐标，这里需要进行实际点到棋盘点的转化
HRESULT
ExChangeLogicalPosition(POINT actualPosition, POINT ptLeftTop, int cxClient, int cyClient, POINT *logicalPosition);

// 将逻辑坐标转化为实际坐标
HRESULT ExchangeActualPosition(POINT logicalPos, int cxCell, int cyCell, POINT ptLeftTop, POINT *actualPos);

#endif // !GAME_DROW
