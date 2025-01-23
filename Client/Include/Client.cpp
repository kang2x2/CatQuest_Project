#include "imgui_impl_win32.h"

#include "stdafx.h"
#include "Client.h"
#include "MainApp.h"
#include "Export_Function.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace Engine;

#define MAX_LOADSTRING 100

HINSTANCE			g_hInst;                              
HWND				g_hWnd;
WCHAR				szTitle[MAX_LOADSTRING];                  
WCHAR				szWindowClass[MAX_LOADSTRING];            
_bool               g_FinishLoading = FALSE;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    /*------------------ 콘솔 출력 매크로 (푸시시 해당 매크로 포함, cout 모두 주석처리 필수) ------------------*/

//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

     /*------------------ 마우스 커서 숨기기 (TRUE, FALSE) ------------------*/
    ShowCursor(FALSE);  

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	srand(unsigned(time(NULL)));

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
		return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	CMainApp*		pMainApp = CMainApp::Create();

	if (nullptr == pMainApp)
		return FALSE;

    MSG msg;
	msg.message = WM_NULL;

	FAILED_CHECK_RETURN(Engine::Ready_Timer(L"Timer_Immediate"), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Timer(L"Timer_FPS65"), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Frame(L"Frame65", 65.f), E_FAIL);

    while (true)
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			Engine::Set_TimeDelta(L"Timer_Immediate");
			_float	fTimer_Immediate = Engine::Get_TimeDelta(L"Timer_Immediate");

			if (Engine::Ispermit_Call(L"Frame65", fTimer_Immediate))
			{
				Engine::Set_TimeDelta(L"Timer_FPS65");
				_float	fTimer60 = Engine::Get_TimeDelta(L"Timer_FPS65");

				pMainApp->Update_MainApp(fTimer60);
				pMainApp->LateUpdate_MainApp();
				pMainApp->Render_MainApp();
			}			
		}
        
    }

	_ulong	dwRefCnt = 0;

	if (dwRefCnt = Safe_Release(pMainApp))
	{
		MSG_BOX("Main App Free Failed");
		return FALSE;
	}


    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance; 

   RECT	rc{ 0, 0, WINCX, WINCY };
   
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, L"Cat Quest", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0,
	   rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(g_hWnd);
			break;
		}

		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
