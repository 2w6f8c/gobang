//
// Created by 2w6f8c on 2019/5/20.
//

#ifndef GOBANG_EVALUATE_H
#define GOBANG_EVALUATE_H

#define SCORE_ONE 20
#define SCORE_TWO 120
#define SCORE_THREE 1600
#define SCORE_FOUR 20000
#define SCORE_FIVE 666666
#define SCORE_BLOCKED_ONE 5
#define SCORE_BLOCKED_TWO 10
#define SCORE_BLOCKED_THREE 233
#define SCORE_BLOCKED_FOUR 666


#include "def.h"
#include <windows.h>

// ��������
int Evaluate();

// �ڵ�ǰλ�����Ӻ󣬸��µ�ǰλ�ü�����λ�õ�����
void UpdateScore(POINT point);

#endif //GOBANG_EVALUATE_H
