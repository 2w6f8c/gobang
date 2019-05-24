//
// Created by 2w6f8c on 2019/5/20.
//

#ifndef GOBANG_EVALUATE_H
#define GOBANG_EVALUATE_H

#define SCORE_ONE 20
#define SCORE_TWO 120
#define SCORE_THREE 720
#define SCORE_FOUR 4320
#define SCORE_FIVE 50000
#define SCORE_BLOCKED_ONE 5
#define SCORE_BLOCKED_TWO 10
#define SCORE_BLOCKED_THREE 360
#define SCORE_BLOCKED_FOUR 1800


#include "def.h"
#include <windows.h>

// 评估函数
int Evaluate();

// 在当前位置下子后，更新当前位置及附近位置的评分
void UpdateScore(POINT point);

#endif //GOBANG_EVALUATE_H
