#include "framework.h"
#include "Step2_2.h"

/*
 // Buffer
   - 컴퓨터가 어떠한 데이터를 주고 받을 때 둘 사이의 전송 속도를 해결하기 위해 전송한 정보를 임시로 저장하는 공간
   
 // 화면에 그려지는 버퍼에 바로 렌더(송출)를 할 경우 
   - 버퍼가 지워지는 순간, 또는 버퍼가 전체가 다 그려지기 전에 화면에 그려진다면 
     덜 그려진 부분이 화면에서잠깐 지워지는 상태가 되어 깜빡이는 것 처럼 보이는 현상이 발생
   - 이러한 문제를 해결하기 위해 백 버퍼를 생성하여 백 버퍼에 모든 내용을 저장 후 프론트 버퍼에 넘겨 화면에 랜더하는 방식을 사용
*/

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

    LoadStringW(hInstance, IDC_STEP22, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);


    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STEP22));

#pragma region Back Buffer 생성
    HDC hdc = GetDC(g_hWnd);
    g_Hdc = CreateCompatibleDC(hdc);
    HBITMAP hBitMap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
    // 비트맵 : 버퍼에 존재하는 데이터를 픽셀 단위로 찍어내어 보여주는 일종의 출력방식
    SelectObject(g_Hdc, hBitMap);
#pragma endregion

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STEP22));
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
        SetTimer(hWnd, 1, 10, NULL);
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