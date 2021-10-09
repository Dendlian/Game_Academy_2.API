#include "framework.h"
#include "Step2_1.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;                  
WCHAR szWindowClass[MAX_LOADSTRING];            
#pragma region User Global Variable
HWND g_hWnd;            // 콘솔창 관리도구 선언
HDC g_Hdc;              // 그리기 관리도구 선언
POINT pt_Mouse;         // 마우스 위치도구 선언
MainGame* g_MainGame;   // MainGame 선언
#pragma endregion

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDC_STEP21, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STEP21));

    g_MainGame = new MainGame;          // MainGame 생성 (동적할당)
    if (g_MainGame)g_MainGame->Init();  // INIT

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    delete g_MainGame;      // 동적할당된 MainGame 삭제
    g_MainGame = nullptr;   // MainGame을 가리키는 주소값 삭제

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STEP21));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_STEP21);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

#pragma region 윈도우 창 생성시 화면의 중앙에 위치
   UINT nResolutionX = GetSystemMetrics(SM_CXSCREEN);
   UINT nResolutionY = GetSystemMetrics(SM_CYSCREEN);
   int nWinPosX = nResolutionX / 2 - WINSIZEX / 2;
   int nWinPosY = nResolutionY / 2 - WINSIZEY / 2;
#pragma endregion

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      nWinPosX, nWinPosY, WINSIZEX, WINSIZEY, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

#pragma region 좌표 나누기
   RECT rt = { nWinPosX, nWinPosY, nWinPosX + WINSIZEX, nWinPosY + WINSIZEY };
   AdjustWindowRect( &rt, WS_OVERLAPPEDWINDOW, false );
   MoveWindow( hWnd, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, true );
#pragma endregion

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CREATE:                             // 첫 루틴에만 실행하는 경우
        SetTimer(hWnd, 1, 10, NULL);             /// 타이머 설정
        srand(time(NULL));                       /// 실시간 타임 설정
        break;
    case WM_TIMER:                              // 일정 주기마다 실행하는 경우
        if (g_MainGame)g_MainGame->Update();     /// UPDATE
        break;
    case WM_MOUSEMOVE:                          // 마우스를 통해 제어하는 경우
        pt_Mouse.x = LOWORD(lParam);    
        pt_Mouse.y = HIWORD(lParam);
        break;
    case WM_PAINT:
        if (g_MainGame)g_MainGame->Render();     /// RENDER
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
