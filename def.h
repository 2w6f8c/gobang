#ifndef GAME_DEF

#define GAME_DEF

#define BOARD_CELL_NUM 14
#define FIVE_MARK_POINT_RADIUS 4
#define CHESS_PIECE_RADIUS	13
#define BLACK_FLAG 1
#define WHITE_FLAG 2
#define NULL_FLAG 0
#define WIN_CONDITION 5

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

#endif // !GAME_DEF
