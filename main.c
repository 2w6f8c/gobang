#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "init.h"

int accumulate = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // todo: test only
    srand(time(0));
    HWND hwnd;
    MSG msg;
    // ��һ��,ע�ᴰ����
    RegisterMyWindow(hInstance);
    // �ڶ���:��������
    hwnd = CreateMyWindow(hInstance, nCmdShow);
    // ������:��Ϣѭ��
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
