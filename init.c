#include "init.h"
#include "randomPlay.h"
#include "alphaBeta.h"
#include <stdio.h>

// ����ע��Ĵ�������
const char szClassName[] = "myWindowClass";

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
    // ��¼�߼�λ�õ����飬����PLAYER_FLAGΪ���ӣ�AI_FLAGΪ���ӣ�NULL_FLAGΪ�հ�
    static int board[BOARD_CELL_NUM + 1][BOARD_CELL_NUM + 1] = {NULL_FLAG};
    // ʤ����
    int winner = NULL_FLAG;
    // ��������ֵ
    HRESULT hResult = S_FALSE;

    switch (msg) {
        // ���ڴ�С�ı�
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            return 0;

            // ����
        case WM_LBUTTONDOWN:
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
            // ���߼����¼����
            board[logicalPosition.x][logicalPosition.y] = PLAYER_FLAG;
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
            IsSomeoneWin(board, &winner);
            if (PLAYER_FLAG == winner) {
                MessageBox(hwnd, TEXT("��һ�ʤ��"), TEXT("��ʾ"), NULL);
            }
            if (AI_FLAG == winner) {
                MessageBox(hwnd, TEXT("���Ի�ʤ��"), TEXT("��ʾ"), NULL);
            }

            /**
             * ��������
             */
            logicalPosition = NextPoint(board, ALPHA_BETA_DEPTH);
            // logicalPosition = RandomPlay(board);
            // ���߼����¼����
            board[logicalPosition.x][logicalPosition.y] = AI_FLAG;
            printf("computer put at (%d, %d)\n", logicalPosition.x, logicalPosition.y);
            for(int i = 0; i < BOARD_CELL_NUM + 1; i++) {
                for(int j = 0; j < BOARD_CELL_NUM + 1; j++) {
                    printf("%d ", board[j][i]);
                }
                printf("\n");
            }
            // ���һС��Ŀ�Ⱥ͸߶�
            GetCellWidthAndHeight(ptLeftTop, cxClient, cyClient, &cxCell, &cyCell);
            // ���߼���ת��Ϊʵ�ʵ�
            ExchangeActualPosition(logicalPosition, cxCell, cyCell, ptLeftTop, &changedActualPosition);
            // ����ʵ�ʵ�
            hdc = GetDC(hwnd);
            DrawWhiteHollowPoint(hdc, CHESS_PIECE_RADIUS, changedActualPosition);
            ReleaseDC(hwnd, hdc);
            // ����ʤ��
            IsSomeoneWin(board, &winner);
            if (PLAYER_FLAG == winner) {
                MessageBox(hwnd, TEXT("��һ�ʤ��"), TEXT("��ʾ"), NULL);
            }
            if (AI_FLAG == winner) {
                MessageBox(hwnd, TEXT("���Ի�ʤ��"), TEXT("��ʾ"), NULL);
            }

            return 0;

            // ��ʼ������
        case WM_MBUTTONDOWN:
            for (int row = 0; row < BOARD_CELL_NUM + 1; ++row) {
                for (int col = 0; col < BOARD_CELL_NUM + 1; ++col) {
                    board[row][col] = 0;
                }
            }
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;

            // ��ͼ
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            // ��ʼ������
            DrawChessBoard(hdc, ptLeftTop, cxClient, cyClient);            // ��������
            DrawFiveHeavyPoint(hdc, ptLeftTop, cxClient, cyClient);        // ����������ص�

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