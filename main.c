#include <windows.h>
#include <math.h>
#include "init.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
