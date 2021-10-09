#include "framework.h"
#include "Step1_2.h"


#define MAX_LOADSTRING 100

HINSTANCE hInst;                                        
WCHAR szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;          
WCHAR szWindowClass[MAX_LOADSTRING];                    

#pragma region User Global Variable
HWND g_hWnd; 
HDC g_Hdc;
POINT pt_Mouse;               
MainGame* g_MainGame;
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
    
    LoadStringW(hInstance, IDC_STEP12, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;       
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STEP12));

    g_MainGame = new MainGame;
    if (g_MainGame)g_MainGame->Init();

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    delete g_MainGame;
    g_MainGame = nullptr;

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STEP12));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    HWND hWnd = CreateWindowW(           
        szWindowClass,                   
        szTitle,                         
        WS_OVERLAPPEDWINDOW,             
        nWinPosX,                        
        nWinPosY,                        
        WINSIZEX,                        
        WINSIZEY,                        
        nullptr,                         
        nullptr,                         
        hInstance,                       
        nullptr                          
    );

    if (!hWnd)
    {
        return FALSE;
    }

    g_hWnd = hWnd;

#pragma region 좌표 나누기
    
    RECT rt = { nWinPosX, nWinPosY, nWinPosX + WINSIZEX, nWinPosY + WINSIZEY };

    AdjustWindowRect(
        &rt,                         
        WS_OVERLAPPEDWINDOW,         
        false                        
    );  
    
    MoveWindow(
        hWnd,
        rt.left,
        rt.top,
        rt.right - rt.left,
        rt.bottom - rt.top,
        true                          
    ); 
#pragma endregion

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);     // 윈도우 창을 업데이트 하며 다시 그리기 : PAINT 호출
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

    case WM_CREATE: 
        SetTimer ( hWnd, 1, 10, NULL );
        srand(time(NULL));
        break;
    case WM_TIMER:
        if (g_MainGame)g_MainGame->Update();
        break;
    case WM_MOUSEMOVE:
        pt_Mouse.x = LOWORD(lParam); 
        pt_Mouse.y = HIWORD(lParam);
        break;
    case WM_PAINT:
        if (g_MainGame)g_MainGame->Render();
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
