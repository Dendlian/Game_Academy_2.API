/*
==NOTE==
// framework.h
   - 자주 사용하지만 변경되지 않거나 표준 시스템을 포함하는 파일
   - 프로젝트의 특정 파일이 들어있는 헤더 파일
*/

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// 실습에 필요한 파일 작성 (파일 추가)

// L : w_char 형식으로 반환
#define PROGRAM_TITLE L"송명근"
#define WINSIZEX 1280
#define WINSIZEY 720
#define UINT unsigned int

#include <string>
using namespace std;