#ifndef GAME_DROW

#define GAME_DROW

#include<windows.h>

// ���ƺ�ɫʵ�ĵ�
HRESULT _DrawBlackSolidPoint(HDC hdc, int radius, POINT postion);

// ���ư�ɫ���ĵ�
HRESULT _DrawWhiteHollowPoint(HDC hdc, int radius, POINT postion);

// ��������
HRESULT DrawChessBoard(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient);

// ����������ص�
HRESULT DrawFiveHeavyPoint(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient);

#endif // !GAME_DROW
