#ifndef GAME_INIT

#define GAME_INIT

#include <windows.h>
#include "def.h"
#include "draw.h"
#include "engine.h"

// 事件响应
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 注册窗口
void RegisterMyWindow(HINSTANCE hInstance);

// 创建窗口
HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow);

// 初始化
void Init();

#endif // !GAME_INIT
