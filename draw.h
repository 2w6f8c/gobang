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

// ��ȡһС���Ⱥ͸߶�
HRESULT GetCellWidthAndHeight(POINT ptLeftTop, int cxClient, int cyClient, int *cxCell, int *cyCell);

// ��ʵ������ת��Ϊ�߼����꣬������Ҫ����ʵ�ʵ㵽���̵��ת��
HRESULT
ExChangeLogicalPosition(POINT actualPosition, POINT ptLeftTop, int cxClient, int cyClient, POINT *logicalPosition);

// ���߼�����ת��Ϊʵ������
HRESULT ExchangeActualPosition(POINT logicalPos, int cxCell, int cyCell, POINT ptLeftTop, POINT *actualPos);

#endif // !GAME_DROW
