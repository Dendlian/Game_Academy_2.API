/*
==Note==
Windows Application Program Interface (WinAPI)
Window : 운영체제 (Os, Operation System)
API : 제공하는 함수의 집합체
윈도우가 제공한 함수의 집합체

 // Handle : 운영체제 내부에 있는 리소스의 주소를 정수로 치환한 값
 // Resource : 각종 하드웨어 장치 또는 저장장치등에 들어있는 데이터 재료
 // HINSTANCE : 각종 하드웨어 장치 또는 저장장치등에 들어있는 데이터 재료
 // 프로세서 : 현재 실행되고 있는 프로그램

 // w_char
   - string str = "단어"; ("" : char[])
 // w_char (wide character) vs char
   - w_char     2       UNICODE
   - char       1       ASCII

*/



#include "framework.h"
#include "Step1_1.h"

#pragma region H.W PRACTICE FUNCTION

void Draw_Plaid(HDC hdc, UINT Interval);
void Draw_RE(HDC hdc, UINT InitX, UINT InitY, UINT Length, UINT Interval);

#pragma endregion



/// 매크로 상수 : 최대 로드할 문자열 길이
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                        /// 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;          /// 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];                    /// 기본 창 클래스 이름입니다.

/// POINT : X와 Y좌표를 가지고 있는 구조체
POINT   ptPos {0, 0};   /// 조작할 렉트의 좌표값
RECT    rtBox1;         /// 조작할 렉트

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/*
==NOTE==
 // APIENTRY : 윈도우 시작지점
 // wWinMain : main과 마찬가지로 WinAPI에서 사용하는 main 함수
*/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                 /// 프로그램의 핸들 인스턴스
                     _In_opt_ HINSTANCE hPrevInstance,          /// 이전에 실행된 핸들 인스턴스
                     _In_ LPWSTR    lpCmdLine,                  /// 명령행으로 입력된 프로그램의 인수
                     _In_ int       nCmdShow)                   /// 프로그램이 사작될 때의 형태 (최소화, 보통 등 상태값)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    /// LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_STEP11, szWindowClass, MAX_LOADSTRING);
    
    
    /// 창 클래스를 등록하는 부분
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;       // InitInstance가 거짓일 때 main문을 종료
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STEP11));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;   /// WNDCLASSEXW : 윈도우의 정보를 저장하기 위한 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);   /// 구조체의 크기 정보를 할당

    /// CS_HREDRAW : 가로
    /// CS_VERDRAW : 세로
    /// 가로와 세로가 변경될 때 스타일을 변경
    wcex.style          = CS_HREDRAW | CS_VREDRAW;                                  /// 윈도우 스타일
    wcex.lpfnWndProc    = WndProc;                                                  /// 메세지 처리함수
    wcex.cbClsExtra     = 0;                                                        /// 클래스 여분의 메모리
    wcex.cbWndExtra     = 0;                                                        /// 윈도우 여분의 메모리
    wcex.hInstance      = hInstance;                                                /// 인스턴스 핸들(주소값)
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STEP11));         /// 아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);                           /// 마우스 커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                                 /// 백그라운드의 색상
    wcex.lpszMenuName   = NULL;                                                     /// 메뉴
    wcex.lpszClassName  = szWindowClass;                                            /// 클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));     /// 작은 아이콘

    return RegisterClassExW(&wcex);     /// 윈도우 클래스 등록 (return 하는 이유 : ATOM이 반환값을 확인해서 생성이 잘 됐는지 확인)
    // ATOM : 반환값을 컴퓨터 프로그램에 넘겨 클래스가 정상적으로 등록됐는지 확인 -> 문제 발생시 프로그램 중단
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.


#pragma region 윈도우 창 생성시 화면의 중앙에 위치
   // 윈도우 창이 생성될 때 정 중앙에 생성 : (모니터의 길이 - 윈도우 창의 길이) / 2
   
   // 사용중인 모니터 해상도의 X, Y사이즈를 반환
   UINT nResolutionX = GetSystemMetrics(SM_CXSCREEN);
   UINT nResolutionY = GetSystemMetrics(SM_CYSCREEN);

   // 화면의 중앙위치
   int nWinPosX = nResolutionX / 2 - WINSIZEX / 2;
   int nWinPosY = nResolutionY / 2 - WINSIZEY / 2;
#pragma endregion


   /*
   ==NOTE==
    // 콘솔창이 아닌 윈도우 창을 생성
    // CreateWindowW : HWND을 반환
    // HWND 
      - 윈도우 콘솔창을 제어하는 공간은 콘솔창 자체의 공간과 별개로 따로 존재
      - HWND는 콘솔창을 제어하는 공간의 주소값을 나타내는 핸들
   */
   HWND hWnd = CreateWindowW(           /// 제대로 생성되지 않았다면 HWND는 nullpter (반환값 = 0)
       szWindowClass,                   /// 윈도우 클래스 이름
       szTitle,                         /// 타이틀바에 뛰울 이름
       WS_OVERLAPPEDWINDOW,             /// 윈도우 스타일
       nWinPosX,                        /// 윈도우 화면의 좌표 X (CW_USEDEFAULT : 컴퓨터가 값을 임의로 생성)
       nWinPosY,                        /// 윈도우 화면의 좌표 Y
       WINSIZEX,                        /// 윈도우 가로 사이즈
       WINSIZEY,                        /// 윈도우 세로 사이즈
       nullptr,                         /// 부모 윈도우 (사용X)
       nullptr,                         /// 메뉴 핸들
       hInstance,                       /// 인스턴스 지정
       nullptr                          /// 자식 윈도우 (사용X)
   );

   /// hwnd가 제대로 생성되지 않았을 때 main문을 종료
   if (!hWnd)
   {
      return FALSE;
   }

#pragma region 좌표 나누기
   /// 실제 창 사이즈를 rt에 보관
   RECT rt = { nWinPosX, nWinPosY, nWinPosX + WINSIZEX, nWinPosY + WINSIZEY };

   /// AdjustWindowRect() : 윈도우의 렉트를 조정하는 함수
   AdjustWindowRect(
       &rt,                         /// 보관할 렉트를 사용 
       WS_OVERLAPPEDWINDOW,         /// 창을 만들 때의 스타일 옵션을 그대로 사용
       false                        /// 메뉴를 사용 X
   ); /// 타이틀 바를 제외한 부분의 크기를 설정

   /// MoveWindow() : 윈도우 창 이동
   MoveWindow(
       hWnd,
       rt.left,
       rt.top,
       rt.right - rt.left,
       rt.bottom - rt.top,
       true                          /// 윈도우 창을 다시 그리기
   ); /// AdjustWindowRect에서 설정한 창을 다시 그리기
#pragma endregion


   /// 윈도우 창 출력
   ShowWindow(hWnd, nCmdShow);
   /// 업데이트
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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

    case WM_CREATE :
        /// WM_CREATE : 프로그램이 실행될 때 한 번 호출 (초기화)
        /// 타이머 설정
        SetTimer
        (
            hWnd,
            1,          /// Timer의 넘버를 구분해주는 매개변수
            10,         /// 호출 주기
            NULL        
            /// Timer 주기 : 1000을 기준으로 1초에 1회 (100 = 1초에 10회)
        );
        break;
    case WM_TIMER :
        /// TIMER : 일정 주기마다 호출하기 위한 기능
        /// InvalidateRect : 화면을 갱신해주는 함수
        InvalidateRect(
            hWnd,       
            NULL,       /// NULL이라면 전체부분을 갱신 (위치를 저장한다면 그 부분만 갱신)
            true        /// false인 경우 과거의 값을 남긴 채로 출력
        );

        break;
    case WM_KEYDOWN : 
    {
        /// wParam : 키보드 입력에 대한 메세지
        switch (wParam)
        {
        case 'A':
            if(ptPos.x > 0)
            ptPos.x -= 1;
            break;
        case 'D':
            if(ptPos.x < 15)
            ptPos.x += 1;
            break;
        case 'W':
            if(ptPos.y > 0)
            ptPos.y -= 1;
            break;
        case 'S':
            if(ptPos.y < 8)
            ptPos.y += 1;
            break;
        }
    }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;                         /// ps : 그릴 수 있는 도구를 가지고 있는 구조체
            HDC hdc = BeginPaint(hWnd, &ps);        /// 페인트 그리기를 시작하는 지점
                                                    /// DC (Device Context) : 출력을 위한 모든 데이터를 가지는 구조체
            
            //wstring wstr = L"창을 생성하였습니다.";
            //TextOut(
            //    hdc,
            //    10,
            //    10,
            //    wstr.c_str(),   // c_str : C언어 형식으로 문자열을 변형
            //    wstr.Lengthgth()
            //    );
            int roomsize = WINSIZEY / 9;
            Draw_Plaid(hdc, roomsize);
            // Draw_RE(hdc, 50, 50, 50, 10);
           
            int ptX = ptPos.x * roomsize;
            int ptY = ptPos.y * roomsize;

            Rectangle(hdc, ptX + 10, ptY + 10, ptX + roomsize - 10, ptY + roomsize - 10);
            // Rectangle(hdc, rtBox1.left, rtBox1.top, rtBox1.right, rtBox1.bottom);

            EndPaint(hWnd, &ps);                    /// 페인트 그리기를 종료하는 지점
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

// 정보 대화 상자의 메시지 처리기입니다.
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


// H.W 9.30
void Draw_Plaid(HDC hdc, UINT Interval)
{
    /// 선 그리기       
    /// MoveToEx : 선의 시작지점을 정하는 함수
    for (int LINEX = 0; LINEX < WINSIZEX; LINEX += Interval)
    {
        MoveToEx(
            hdc,            /// 핸들
            LINEX,          /// X 좌표
            0,              /// Y 좌표
            NULL            /// 이전 포인터 값
        );
        LineTo(hdc, LINEX, WINSIZEY);
    }
    for (int LINEY = 0; LINEY < WINSIZEY; LINEY += Interval)
    {
        MoveToEx(
            hdc,           
            0,             
            LINEY,        
            NULL           
        );
        LineTo(hdc, WINSIZEX, LINEY);
    }
}


// H.W 10.01
void Draw_RE(HDC hdc, UINT InitX, UINT InitY, UINT Length, UINT Interval)
{
    int Line = 0;
    for (int i = 0; i < 25; i++)
    {
        if (i % 5 == 0) Line++;
        if (Line % 2 == 1)
        {
            Rectangle(
                hdc, 
                InitX + (i % 5) * (Length + Interval),                          // 왼쪽
                InitY + (Line - 1) * (Length + Interval),                       // 위쪽
                InitX + (i % 5) * (Length + Interval) + Length,                 // 오른쪽
                InitY + (Line - 1) * (Length + Interval) + Length);             // 아래쪽
        }
        else
        {
            Ellipse(
                hdc, 
                InitX + (i % 5) * (Length + Interval), 
                InitY + (Line - 1) * (Length + Interval), 
                InitX + (i % 5) * (Length + Interval) + Length, 
                InitY + (Line - 1) * (Length + Interval) + Length);
        }
    }
}




