#ifndef GAME_UTIL

#define GAME_UTIL

#include <windows.h>
#include "def.h"

// ��ȡһС���Ⱥ͸߶�
HRESULT _GetCellWidthAndHeight(POINT ptLeftTop, int cxClient, int cyClient, int *cxCell, int *cyCell);

// ��ʵ������ת��Ϊ�߼����꣬������Ҫ����ʵ�ʵ㵽���̵��ת��
HRESULT _ExChangeLogicalPosition(POINT actualPostion, POINT ptLeftTop, int cxClient, int cyClient, POINT *logicalPostion);

// ���߼�����ת��Ϊʵ������
HRESULT _ExchangeActualPositon(POINT logicalPos, int cxCell, int cyCell, POINT ptLeftTop, POINT *actualPos);

// �жϵ�ǰ�߼����ָ���������Ƿ������ڵ�
HRESULT _IsSidewardHasSamePoint(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point, GameDirection direction, BOOLEAN *bSame, POINT *movedPoint);

// ���㵱ǰ�����ȥ��ͬ�����ӵĸ���
HRESULT _CountSameDiretionPointsNumber(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], POINT point, GameDirection direction, int *count);

// �ж��Ƿ�ʤ��
HRESULT IsSomeoneWin(int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1], int *winner);

#endif // !GAME_UTIL
