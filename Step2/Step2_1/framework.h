#pragma once
#include "targetver.h"
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN  

// 실습에 필요한 파일 작성 (파일 추가)
using namespace std;
extern HWND g_hWnd;
extern HDC g_Hdc;
extern POINT pt_Mouse;

#define PROGRAM_TITLE L"송명근"
#define WINSIZEX 640
#define WINSIZEY 480

#define UINT unsigned int
#define RECT_MAKE(x,y,s){ x - s / 2, y - s / 2, x + s / 2, y + s / 2 }
#define RECT_DRAW(rt) Rectangle(g_Hdc, rt.left, rt.top, rt.right, rt.bottom)

#include <string>
#include <vector>
#include <time.h>
#include "MainGame.h"
