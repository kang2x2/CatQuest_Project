// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// ������ ���� 2��(api���� �������� wmv�� ��� ����.)
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")
// << : fmode
#include "../FMOD/inc/fmod.h"
//#include "../FMOD/inc/fmod.hpp"
//#pragma comment(lib, "fmod_vc.lib")
//#pragma comment(lib, "fmodex_vc.lib")

#ifdef UNICODE
#define PlaySound  PlaySoundW
#else
#define PlaySound  PlaySoundA
#endif // !UNICODE

#include <io.h>

// >> : fmode
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#include <d3d9.h>
#include <d3dx9.h>

#include <list>
#include <vector>
#include <map>
#include <string>
#include <queue>

#include <random>

#include <algorithm>

#include <process.h>

#include <iostream>

extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

using namespace std;
