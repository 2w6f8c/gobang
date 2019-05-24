#include "init.h"
#include "randomPlay.h"
#include "alphaBeta.h"
#include "engine.h"
#include <stdio.h>

// ����ע��Ĵ�������
const char szClassName[] = "myWindowClass";
// ��¼�߼�λ�õ����飬����PLAYER_FLAGΪ���ӣ�AI_FLAGΪ���ӣ�NULL_FLAGΪ�հ�
int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1] = {0};
// ʤ����
static int winner = NULL_FLAG;

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

    // ��������
    POINT point = {7, 7};
    PutChess(point, AI_FLAG);
    printf("init: computer put at (%d, %d)\n", point.x, point.y);
}

// �¼���Ӧ
// ���̿���
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    // �ͻ�������
    static int cxClient, cyClient;
    // ÿ������Ŀ�Ⱥ͸߶�
    int cxCell = 0, cyCell = 0;
    // �������Ͻ�����
    POINT ptLeftTop;
    ptLeftTop.x = 30;
    ptLeftTop.y = 40;
    // �����ʵ�ʵ�
    POINT actualPosition;
    // �����ʵ�ʵ����ת�������߼���
    POINT logicalPosition;
    // �����ʵ�ʵ����ת�������߼����Ӧ��ʵ�ʵ�
    POINT changedActualPosition;

    // ��������ֵ
    HRESULT hResult;

    switch (msg) {
        // ���ڴ�С�ı�
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            return 0;

            // ����
        case WM_LBUTTONDOWN:
            // �ѷֳ�ʤ����ֱ�ӷ���
            if (winner != NULL_FLAG) {
                MessageBox(hwnd, TEXT("ʤ���Ѿ���\n����껬���ؿ�"), TEXT("��ʾ"), NULL);
                return 0;
            }

            /**
             * �������
             */
            // ���ʵ�ʵ�
            actualPosition.x = LOWORD(lParam);
            actualPosition.y = HIWORD(lParam);
            // ��ö�Ӧ�ļ��������߼���
            hResult = ExChangeLogicalPosition(actualPosition, ptLeftTop, cxClient, cyClient, &logicalPosition);
            if (S_FALSE == hResult) {
                return 0;
            }
            if (board[logicalPosition.x][logicalPosition.y] != NULL_FLAG) return 0;
            PutChess(logicalPosition, PLAYER_FLAG);
            printf("player put at (%d, %d)\n", logicalPosition.x, logicalPosition.y);
            // ���һС��Ŀ�Ⱥ͸߶�
            GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
            // ���߼���ת��Ϊʵ�ʵ�
            ExchangeActualPosition(logicalPosition, cxCell, cyCell, ptLeftTop, &changedActualPosition);
            // ����ʵ�ʵ�
            hdc = GetDC(hwnd);
            DrawBlackSolidPoint(hdc, CHESS_PIECE_RADIUS, changedActualPosition);
            ReleaseDC(hwnd, hdc);
            // ����ʤ��
            IsSomeoneWin(&winner);
            if (winner == PLAYER_FLAG) {
                MessageBox(hwnd, TEXT("��һ�ʤ��"), TEXT("��ʾ"), NULL);
                return 0;
            }

            /**
             * ��������
             */
            logicalPosition = NextPoint(ALPHA_BETA_DEPTH);
            PutChess(logicalPosition, AI_FLAG);
            printf("computer put at (%d, %d)\n", logicalPosition.x, logicalPosition.y);
            // ���һС��Ŀ�Ⱥ͸߶�
            GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
            // ���߼���ת��Ϊʵ�ʵ�
            ExchangeActualPosition(logicalPosition, cxCell, cyCell, ptLeftTop, &changedActualPosition);
            // ����ʵ�ʵ�
            hdc = GetDC(hwnd);
            DrawWhiteHollowPoint(hdc, CHESS_PIECE_RADIUS, changedActualPosition);
            ReleaseDC(hwnd, hdc);
            // ����ʤ��
            IsSomeoneWin(&winner);
            if (winner == AI_FLAG) {
                MessageBox(hwnd, TEXT("���Ի�ʤ��"), TEXT("��ʾ"), NULL);
                return 0;
            }

            return 0;

            // ��ʼ������
        case WM_MBUTTONDOWN:
            Init();
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;

            // ��ͼ
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            // ��������
            DrawChessBoard(hdc, ptLeftTop, cxClient, cyClient);
            // ����������ص�
            DrawFiveHeavyPoint(hdc, ptLeftTop, cxClient, cyClient);
            // ��������
            DrawAllChess(hdc, ptLeftTop, cxClient, cyClient);

            EndPaint(hwnd, &ps);
            return 0;

            // ����
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ע�ᴰ��
void RegisterMyWindow(HINSTANCE hInstance) {
    WNDCLASSEX wc;

    // 1)���ô�������
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = MyWindowProc; // ���õ��Ĳ��Ĵ��ڹ��̻ص�����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // 2)ע��
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("����ע��ʧ��!"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // �����˳�
    }
}

// ��������
HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow) {
    HWND hwnd;
    hwnd = CreateWindow(
            szClassName,
            TEXT("������"),
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
        MessageBox(NULL, TEXT("���ڴ���ʧ��!"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // �����˳�
    }

    // ��ʾ����
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return hwnd;
}