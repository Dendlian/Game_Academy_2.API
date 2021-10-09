#include "MainGame.h"

MainGame::MainGame()
{
	_Player = new Player;
	_Object = new Object;
}

MainGame::~MainGame()
{
	delete _Player;
	_Player = nullptr;

	delete _Object;
	_Object = nullptr;

	GetManager(KeyManager)->ReleaseInstance<KeyManager>();
}

void MainGame::Init()
{
	Score = 0;
	Level = 1;

	// 존재한다면 초기화
	if (_Player) _Player->Init();
	if (_Object) _Object->Init();
}

void MainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, true);
	Level = Score / 100 + 1;
	_Object->SetLevel(Level);

	_Player->Update();
	_Object->Update();

	vector<ThrowBox>::iterator iter;

	for(iter = _Object->GetBox().begin(); iter != _Object->GetBox().end(); iter++)
	{
		iter->rt.top += iter->speed;
		iter->rt.bottom += iter->speed;

		RECT rt;
		RECT rtlter = iter->rt;

		if (rtlter.top > WINSIZEY)
		{
			Score += 2;
			_Object->GetBox().erase(iter);
			break;
		}
		else if (IntersectRect(&rt, &_Player->GetPlayerBox(), & rtlter))
		{
			Score -= 10;
			_Object->GetBox().erase(iter);
			break;
		}
		else if (PtInRect(&rtlter, pt_Mouse))
		{
			Score += 5;
			_Object->GetBox().erase(iter);
			break;
		}
		if (Score < 0) Score = 0;
	}
}

void MainGame::Render()
{
	PAINTSTRUCT ps;
	g_Hdc = BeginPaint(g_hWnd, &ps);

	_Object->Render();
	_Player->Render();

	string str = to_string(Score);

	TextOutA(g_Hdc, 10, 30, str.c_str(), str.length());

	str = to_string(Level);

	TextOutA(g_Hdc, 10, 10, str.c_str(), str.length());

	EndPaint(g_hWnd, &ps);
}
