#include "init.h"

// 用于注册的窗口类名
const char szClassName[] = "myWindowClass";

LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	// 客户区坐标
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
	POINT logicalPostion;
	// 鼠标点击实际点计算转化来的逻辑点对应的实际点
	POINT changedActualPosition;
	// 记录逻辑位置的数组，其中BLACK_FLAG为黑子，WHITE_FLAG为白子，NULL_FLAG为空白
	static int chessPoints[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1] = { NULL_FLAG };
	// 胜利者
	int winner = NULL_FLAG;
	// 函数返回值
	HRESULT hResult = S_FALSE;

	switch (msg) {
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_LBUTTONDOWN:	// 黑子
		// 获得实际点
		actualPosition.x = LOWORD(lParam);
		actualPosition.y = HIWORD(lParam);
		// 获得对应的计算过后的逻辑点
		hResult = ExChangeLogicalPosition(actualPosition, ptLeftTop, cxClient, cyClient, &logicalPostion);
		if (S_FALSE == hResult) {
			return 0;
		}
		// 将逻辑点记录下来
		chessPoints[logicalPostion.x][logicalPostion.y] = BLACK_FLAG;
		// 获得一小格的宽度和高度
		GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
		// 将逻辑点转化为实际点
		POINT changedActualPosition;
		ExchangeActualPositon(logicalPostion, cxCell, cyCell, ptLeftTop, &changedActualPosition);
		// 绘制实际点
		hdc = GetDC(hwnd);
		DrawBlackSolidPoint(hdc, CHESS_PIECE_RADIUS, changedActualPosition);
		ReleaseDC(hwnd, hdc);
		// 计算胜利
		IsSomeoneWin(chessPoints, &winner);
		if (BLACK_FLAG == winner) {
			MessageBox(hwnd, TEXT("黑棋获胜！"), TEXT("提示"), NULL);
		}
		if (WHITE_FLAG == winner) {
			MessageBox(hwnd, TEXT("白棋获胜！"), TEXT("提示"), NULL);
		}
		return 0;

	case WM_RBUTTONDOWN:	// 白子
		actualPosition.x = LOWORD(lParam);
		actualPosition.y = HIWORD(lParam);
		// 获得对应的计算过后的逻辑点
		hResult = ExChangeLogicalPosition(actualPosition, ptLeftTop, cxClient, cyClient, &logicalPostion);
		if (S_FALSE == hResult) {
			return 0;
		}
		// 将逻辑点记录下来
		chessPoints[logicalPostion.x][logicalPostion.y] = WHITE_FLAG;
		// 获得一小格的宽度和高度
		GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
		// 将逻辑点转化为实际点
		ExchangeActualPositon(logicalPostion, cxCell, cyCell, ptLeftTop, &changedActualPosition);
		// 绘制实际点
		hdc = GetDC(hwnd);
		DrawWhiteHollowPoint(hdc, CHESS_PIECE_RADIUS, changedActualPosition);
		ReleaseDC(hwnd, hdc);
		// 计算胜利
		IsSomeoneWin(chessPoints, &winner);
		if (BLACK_FLAG == winner) {
			MessageBox(hwnd, TEXT("黑棋获胜！"), TEXT("提示"), NULL);
		}
		if (WHITE_FLAG == winner) {
			MessageBox(hwnd, TEXT("白棋获胜！"), TEXT("提示"), NULL);
		}
		return 0;

	case WM_MBUTTONDOWN:	// 初始化棋盘
		for (int row = 0; row < BOARD_CELL_NUM + 1; ++row) {
			for (int col = 0; col < BOARD_CELL_NUM + 1; ++col) {
				chessPoints[row][col] = 0;
			}
		}
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		// 初始化棋盘
		DrawChessBoard(hdc, ptLeftTop, cxClient, cyClient);			// 绘制棋盘
		DrawFiveHeavyPoint(hdc, ptLeftTop, cxClient, cyClient);		// 绘制五个着重点

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// 2)注册
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, TEXT("窗口注册失败!"), TEXT("错误"), MB_ICONEXCLAMATION | MB_OK);
		exit(0); // 进程退出
	}
}


HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow) {
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		szClassName,
		TEXT("我的窗口名称"),
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

