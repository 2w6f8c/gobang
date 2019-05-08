#ifndef GAME_INIT

#define GAME_INIT

#include <windows.h>
#include "def.h"
#include "draw.h"
#include "util.h"

LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void RegisterMyWindow(HINSTANCE hInstance);
HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow);

#endif // !GAME_INIT
