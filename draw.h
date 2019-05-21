#ifndef GAME_DRAW

#define GAME_DRAW

#include<windows.h>

// ���ƺ�ɫʵ�ĵ�
HRESULT DrawBlackSolidPoint(HDC hdc, int radius, POINT position);

// ���ư�ɫ���ĵ�
HRESULT DrawWhiteHollowPoint(HDC hdc, int radius, POINT position);

// ��������
HRESULT DrawChessBoard(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient);

// ����������ص�
HRESULT DrawFiveHeavyPoint(HDC hdc, POINT ptLeftTop, int cxClient, int cyClient);

#endif // !GAME_DROW
