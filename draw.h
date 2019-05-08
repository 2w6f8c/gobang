#ifndef GAME_DROW

#define GAME_DROW

#include<windows.h>

// 绘制黑色实心点
HRESULT _DrawBlackSolidPoint(HDC hdc, int radius, POINT postion);

// 绘制白色空心点
HRESULT _DrawWhiteHollowPoint(HDC hdc, int radius, POINT postion);

// 绘制棋盘
HRESULT DrawChessBoard(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient);

// 绘制五个着重点
HRESULT DrawFiveHeavyPoint(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient);

#endif // !GAME_DROW
