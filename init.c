#include "init.h"
#include "randomPlay.h"
#include "alphaBeta.h"
#include "engine.h"
#include <stdio.h>

// 用于注册的窗口类名
const char szClassName[] = "myWindowClass";
// 记录逻辑位置的数组，其中PLAYER_FLAG为黑子，AI_FLAG为白子，NULL_FLAG为空白
int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1] = {0};
// 胜利者
static int winner = NULL_FLAG;

// 初始化
void Init() {
    winner = NULL_FLAG;
    for (int i = 0; i < BOARD_CELL_NUM + 1; i++) {
        for (int j = 0; j < BOARD_CELL_NUM + 1; j++) {
            board[i][j] = NULL_FLAG;
            score[AI_FLAG][i][j] = 0;
            score[PLAYER_FLAG][i][j] = 0;
        }
    }

    // 电脑先手
    POINT point = {7, 7};
    PutChess(point, AI_FLAG);
    printf("init: computer put at (%d, %d)\n", point.x, point.y);
}

// 事件响应
// 流程控制
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    // 客户端坐标
    static int cxClient, cyClient;
    // 每个方格的宽度和高度
    int cxCell = 0, cyCell = 0;
    // 棋盘左上角坐标
    POINT ptLeftTop;
    ptLeftTop.x = 30;
    ptLeftTop.y = 40;
    // 鼠标点击实际点
    POINT actualPosition;
    // 鼠标点击实际点计算转化来的逻辑点
    POINT logicalPosition;
    // 鼠标点击实际点计算转化来的逻辑点对应的实际点
    POINT changedActualPosition;

    // 函数返回值
    HRESULT hResult;

    switch (msg) {
        // 窗口大小改变
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            return 0;

            // 下棋
        case WM_LBUTTONDOWN:
            // 已分出胜负则直接返回
            if (winner != NULL_FLAG) {
                MessageBox(hwnd, TEXT("胜负已决！\n按鼠标滑轮重开"), TEXT("提示"), NULL);
                return 0;
            }

            /**
             * 玩家下棋
             */
            // 获得实际点
            actualPosition.x = LOWORD(lParam);
            actualPosition.y = HIWORD(lParam);
            // 获得对应的计算过后的逻辑点
            hResult = ExChangeLogicalPosition(actualPosition, ptLeftTop, cxClient, cyClient, &logicalPosition);
            if (S_FALSE == hResult) {
                return 0;
            }
            if (board[logicalPosition.x][logicalPosition.y] != NULL_FLAG) return 0;
            PutChess(logicalPosition, PLAYER_FLAG);
            printf("player put at (%d, %d)\n", logicalPosition.x, logicalPosition.y);
            // 获得一小格的宽度和高度
            GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
            // 将逻辑点转化为实际点
            ExchangeActualPosition(logicalPosition, cxCell, cyCell, ptLeftTop, &changedActualPosition);
            // 绘制实际点
            hdc = GetDC(hwnd);
            DrawBlackSolidPoint(hdc, CHESS_PIECE_RADIUS, changedActualPosition);
            ReleaseDC(hwnd, hdc);
            // 计算胜利
            IsSomeoneWin(&winner);
            if (winner == PLAYER_FLAG) {
                MessageBox(hwnd, TEXT("玩家获胜！"), TEXT("提示"), NULL);
                return 0;
            }

            /**
             * 电脑下棋
             */
            logicalPosition = NextPoint(ALPHA_BETA_DEPTH);
            PutChess(logicalPosition, AI_FLAG);
            printf("computer put at (%d, %d)\n", logicalPosition.x, logicalPosition.y);
            // 获得一小格的宽度和高度
            GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
            // 将逻辑点转化为实际点
            ExchangeActualPosition(logicalPosition, cxCell, cyCell, ptLeftTop, &changedActualPosition);
            // 绘制实际点
            hdc = GetDC(hwnd);
            DrawWhiteHollowPoint(hdc, CHESS_PIECE_RADIUS, changedActualPosition);
            ReleaseDC(hwnd, hdc);
            // 计算胜利
            IsSomeoneWin(&winner);
            if (winner == AI_FLAG) {
                MessageBox(hwnd, TEXT("电脑获胜！"), TEXT("提示"), NULL);
                return 0;
            }

            return 0;

            // 初始化棋盘
        case WM_MBUTTONDOWN:
            Init();
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;

            // 绘图
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            // 绘制棋盘
            DrawChessBoard(hdc, ptLeftTop, cxClient, cyClient);
            // 绘制五个着重点
            DrawFiveHeavyPoint(hdc, ptLeftTop, cxClient, cyClient);
            // 绘制棋子
            DrawAllChess(hdc, ptLeftTop, cxClient, cyClient);

            EndPaint(hwnd, &ps);
            return 0;

            // 销毁
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// 注册窗口
void RegisterMyWindow(HINSTANCE hInstance) {
    WNDCLASSEX wc;

    // 1)配置窗口属性
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = MyWindowProc; // 设置第四步的窗口过程回调函数
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // 2)注册
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("窗口注册失败!"), TEXT("错误"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // 进程退出
    }
}

// 创建窗口
HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow) {
    HWND hwnd;
    hwnd = CreateWindow(
            szClassName,
            TEXT("五子棋"),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            610,
            610,
            NULL,
            NULL,
            hInstance,
            NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("窗口创建失败!"), TEXT("错误"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // 进程退出
    }

    // 显示窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return hwnd;
}