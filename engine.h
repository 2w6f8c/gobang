#ifndef GAME_UTIL

#define GAME_UTIL

#include <windows.h>
#include <stdio.h>
#include "def.h"

typedef enum Enum_Direction {
    Direction_Top = 0,
    Direction_RightTop = 1,
    Direction_Right = 2,
    Direction_RightBottom = 3,
    Direction_Bottom = 4,
    Direction_LeftBottom = 5,
    Direction_Left = 6,
    Direction_LeftTop = 7
} GameDirection;

// 游戏初始化
void Init();

// 打印棋盘
void PrintBoard();

// 下子并更新分数
void PutChess(POINT point, int role);

// 取消下子并更新分数
void UnPutChess(POINT point);

// 悔棋
void Undo();

// 判断当前逻辑点的指定方向上是否有相邻点
void IsSidewardHasSamePoint(POINT point, GameDirection direction, BOOLEAN *bSame, POINT *movedPoint);

// 计算当前方向过去的同类棋子的个数
void CountSameDirectionPointsNumber(POINT point, GameDirection direction, int *count);

// 判定是否胜利
void IsSomeoneWin(int *winner);

#endif // !GAME_UTIL
