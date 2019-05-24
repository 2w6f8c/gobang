//
// Created by 2w6f8c on 2019/5/20.
//

#ifndef GOBANG_ALPHABETA_H
#define GOBANG_ALPHABETA_H

#include "def.h"
#include <windows.h>

int AlphaBeta(int role, int depth, int alpha, int beta);

POINT NextPoint(int depth);


#endif //GOBANG_ALPHABETA_H
