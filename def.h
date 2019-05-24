#ifndef GAME_DEF

#define GAME_DEF

#define BOARD_CELL_NUM 14
#define FIVE_MARK_POINT_RADIUS 4
#define CHESS_PIECE_RADIUS    13
#define PLAYER_FLAG 0
#define AI_FLAG 1
#define NULL_FLAG 2

// 搜索深度
#define ALPHA_BETA_DEPTH 3

extern int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1];
extern int scoreCache[2][BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1];

#endif // !GAME_DEF
