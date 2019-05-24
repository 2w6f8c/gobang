#ifndef GAME_UTIL

#define GAME_UTIL

#include <windows.h>
#include <stdio.h>
#include "def.h"

// �жϵ�ǰ�߼����ָ���������Ƿ������ڵ�
HRESULT
IsSidewardHasSamePoint(POINT point, GameDirection direction,
                       BOOLEAN *bSame, POINT *movedPoint);

// ���㵱ǰ�����ȥ��ͬ�����ӵĸ���
HRESULT CountSameDircetionPointsNumber(POINT point,
                                      GameDirection direction, int *count);

// �ж��Ƿ�ʤ��
HRESULT IsSomeoneWin(int *winner);

// ��ӡ����
void PrintBoard();

// ���Ӳ����·���
void PutChess(POINT point, int role);

// ȡ�����Ӳ����·���
void UnPutChess(POINT point);

#endif // !GAME_UTIL
