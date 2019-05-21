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

#endif // !GAME_DROW
