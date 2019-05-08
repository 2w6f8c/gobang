#include <windows.h>
#include <math.h>
#include "init.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;
	// 第一步,注册窗口类
	RegisterMyWindow(hInstance);
	// 第二步:创建窗口
	hwnd = CreateMyWindow(hInstance, nCmdShow);
	// 第三步:消息循环
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
