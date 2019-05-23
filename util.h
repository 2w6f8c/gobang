#ifndef GAME_UTIL

#define GAME_UTIL

#include <windows.h>
#include <stdio.h>
#include "def.h"

// ��ȡһС���Ⱥ͸߶�
HRESULT GetCellWidthAndHeight(POINT ptLeftTop, int cxClient, int cyClient, int *cxCell, int *cyCell);

// ��ʵ������ת��Ϊ�߼����꣬������Ҫ����ʵ�ʵ㵽���̵��ת��
HRESULT
ExChangeLogicalPosition(POINT actualPostion, POINT ptLeftTop, int cxClient, int cyClient, POINT *logicalPostion);

// ���߼�����ת��Ϊʵ������
HRESULT ExchangeActualPosition(POINT logicalPos, int cxCell, int cyCell, POINT ptLeftTop, POINT *actualPos);

// �жϵ�ǰ�߼����ָ���������Ƿ������ڵ�
HRESULT
IsSidewardHasSamePoint(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point, GameDirection direction,
                       BOOLEAN *bSame, POINT *movedPoint);

// ���㵱ǰ�����ȥ��ͬ�����ӵĸ���
HRESULT CountSameDircetionPointsNumber(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point,
                                      GameDirection direction, int *count);

// �ж��Ƿ�ʤ��
HRESULT IsSomeoneWin(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], int *winner);

// ��ӡ����
void PrintBoard(int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1]);

#endif // !GAME_UTIL
