#include "MainGame.h"

MainGame::MainGame()
{
	_Player = new Player;
	_Object = new Object;
	ScoreDelay = 10;
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

	if (_Player) _Player->Init();
	if (_Object) _Object->Init();
}

void MainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, true);
	if (ScoreDelay > 10)
	{
		Score++;
		ScoreDelay = 0;
	}
	ScoreDelay++;
	
	Level = Score / 100 + 1;
	_Object->SetLevel(Level);

	_Player->Update();
	_Object->Update();

	vector<BlockBox>::iterator iter;
	

	for (iter = _Object->GetBox().begin(); iter != _Object->GetBox().end(); iter++)
	{
		iter->Player_Object.left -= iter->speed;
		iter->Player_Object.right -= iter->speed;
		
		RECT rt;
		RECT rtIter = iter->Player_Object;
	
		
		if (rtIter.right < 0)
		{
			_Object->GetBox().erase(iter);
			break;
		}
		else if (IntersectRect(&rt, &_Player->GetPlayerBox(0), &rtIter))
		{
			Score = 0;
			_Object->GetBox().erase(iter);
			break;
		}
		else if (IntersectRect(&rt, &_Player->GetPlayerBox(1), &rtIter))
		{
			Score = 0;
			_Object->GetBox().erase(iter);
			break;
		}
		else if (IntersectRect(&rt, &_Player->GetPlayerBox(2), &rtIter))
		{
			Score = 0;
			_Object->GetBox().erase(iter);
			break;
		}
		else if (IntersectRect(&rt, &_Player->GetPlayerBox(3), &rtIter))
		{
			Score = 0;
			_Object->GetBox().erase(iter);
			break;
		}
		else if (IntersectRect(&rt, &_Player->GetPlayerBox(4), &rtIter))
		{
			Score = 0;
			_Object->GetBox().erase(iter);
			break;
		}
		else if (IntersectRect(&rt, &_Player->GetPlayerBox(5), &rtIter))
		{
			Score = 0;
			_Object->GetBox().erase(iter);
			break;
		}
	}
}

void MainGame::Render()
{
	PAINTSTRUCT ps;
	g_Hdc = BeginPaint(g_hWnd, &ps);

	MoveToEx(g_Hdc, 0, WINSIZEY - 85, NULL);
	LineTo(g_Hdc, WINSIZEX, WINSIZEY - 85);

	_Object->Render();
	_Player->Render();

	string str = "Score";
	TextOutA(g_Hdc, 10, 30, str.c_str(), str.length());

	str = to_string(Score);
	TextOutA(g_Hdc, 50, 30, str.c_str(), str.length());

	str = "Level";
	TextOutA(g_Hdc, 10, 10, str.c_str(), str.length());

	str = to_string(Level);
	TextOutA(g_Hdc, 50, 10, str.c_str(), str.length());

	EndPaint(g_hWnd, &ps);
}
