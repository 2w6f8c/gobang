#include "engine.h"
#include "evaluate.h"
#include "stdio.h"
#include "stack.h"

extern int winner;
extern Stack stack;

// ��ʼ��
void Init() {
    winner = NULL_FLAG;
    for (int i = 0; i < BOARD_CELL_NUM + 1; i++) {
        for (int j = 0; j < BOARD_CELL_NUM + 1; j++) {
            board[i][j] = NULL_FLAG;
            score[AI_FLAG][i][j] = 0;
            score[PLAYER_FLAG][i][j] = 0;
        }
    }

    if (stack) freeStack(stack);
    stack = newStack();

    // ��������
    POINT point = {7, 7};
    PutChess(point, AI_FLAG);
    printf("========================================\n");
    printf("computer put at (%d, %d)\n", point.x, point.y);
}

// ����
void Undo() {
    printf("undo...\n");
    winner = NULL_FLAG;
    // ���γ����������Ӻ��������
    if(!isEmpty(stack)) UnPutChess(pop(stack));
    if(!isEmpty(stack)) UnPutChess(pop(stack));
}

// ��ӡ����
void PrintBoard() {
    for(int i = 0; i < BOARD_CELL_NUM + 1; i++) {
        for(int j = 0; j < BOARD_CELL_NUM + 1; j++) {
            printf("%d ", board[j][i]);
        }
        printf("\n");
    }
}

// ���Ӳ����·���
void PutChess(POINT point, int role) {
    board[point.x][point.y] = role;
    UpdateScore(point);
}

// ȡ�����Ӳ����·���
void UnPutChess(POINT point) {
    board[point.x][point.y] = NULL_FLAG;
    UpdateScore(point);
}

// �жϵ�ǰ�߼����ָ���������Ƿ������ڵ�
void IsSidewardHasSamePoint(POINT point, GameDirection direction,
                            BOOLEAN *bSame, POINT *movedPoint) {
    // ��¼��ǰ���ֵ
    int curSideValue = board[point.x][point.y];
    // ����÷������һ���߼�������
    switch (direction) {
        case Direction_Top: {
            point.y -= 1;
            break;
        }

        case Direction_RightTop: {
            point.x += 1;
            point.y -= 1;
            break;
        }

        case Direction_Right: {
            point.x += 1;
            break;
        }

        case Direction_RightBottom: {
            point.x += 1;
            point.y += 1;
            break;
        }

        case Direction_Bottom: {
            point.y += 1;
            break;
        }

        case Direction_LeftBottom: {
            point.x -= 1;
            point.y += 1;
            break;
        }

        case Direction_Left: {
            point.x -= 1;
            break;
        }

        case Direction_LeftTop: {
            point.x -= 1;
            point.y -= 1;
            break;
        }
    }
    // �����Ƿ���ͬ
    if (point.x >= 0 && point.x < BOARD_CELL_NUM + 1 && point.y >= 0 && point.y < BOARD_CELL_NUM + 1) {
        *bSame = curSideValue == board[point.x][point.y];
        movedPoint->x = point.x;
        movedPoint->y = point.y;
    }
}

// ���㵱ǰ�����ȥ��ͬ�����ӵĸ���
void CountSameDirectionPointsNumber(POINT point, GameDirection direction, int *count) {
    (*count) += 1;
    BOOLEAN bSame = FALSE;
    POINT movedPoint = {point.x, point.y};
    IsSidewardHasSamePoint(point, direction, &bSame, &movedPoint);
    if (bSame == TRUE) {
        bSame = FALSE;
        CountSameDirectionPointsNumber(movedPoint, direction, count);
    }
}

// �ж��Ƿ�ʤ��
void IsSomeoneWin(int *winner) {
    // �����������ŵ�ʤ��
    for (int row = 0; row < BOARD_CELL_NUM + 1; ++row) {
        for (int col = 0; col < BOARD_CELL_NUM + 1; ++col) {
            if (board[row][col] != NULL_FLAG) {
                POINT point = {row, col};
                for (size_t direction = 0; direction < 8; ++direction) {
                    // ��ȡ��ǰ��˷�������ͬ��������
                    int count = 0;
                    CountSameDirectionPointsNumber(point, direction, &count);
                    // �ж��Ƿ�ʤ��
                    if (count >= 5) {
                        *winner = board[row][col];
                    }
                }
            }
        }
    }
}