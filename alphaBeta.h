//
// Created by 2w6f8c on 2019/5/20.
//

#ifndef GOBANG_ALPHABETA_H
#define GOBANG_ALPHABETA_H

#include "def.h"
#include <windows.h>

/**
 * 通过α-β剪枝算法得到下一步落子位置
 * @param depth
 * @return
 */
POINT NextPoint(int depth);

#endif //GOBANG_ALPHABETA_H
