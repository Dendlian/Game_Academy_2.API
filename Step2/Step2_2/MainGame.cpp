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
	ScoreDelay = 0;
	Level = 1;

	// 존재한다면 초기화
	if (_Player) _Player->Init();
	if (_Object) _Object->Init();
}

void MainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, false);							// buffer step 4
	Level = Score / 100 + 1;
	_Object->SetLevel(Level);

	_Player->Update();
	_Object->Update();

	vector<ThrowBox>::iterator iter;

	for (iter = _Object->GetBox().begin(); iter != _Object->GetBox().end(); iter++)
	{
		switch (iter->initspace)
		{
		case TOP:
			iter->rt.top += iter->speed;
			iter->rt.bottom += iter->speed;
			iter->rt.left += iter->v_speed;
			iter->rt.right += iter->v_speed;
			break;
		case BOTTOM:
			iter->rt.top -= iter->speed;
			iter->rt.bottom -= iter->speed;
			iter->rt.left += iter->v_speed;
			iter->rt.right += iter->v_speed;
			break;
		case LEFT:
			iter->rt.left += iter->speed;
			iter->rt.right += iter->speed;
			iter->rt.top += iter->v_speed;
			iter->rt.bottom += iter->v_speed;
			break;
		case RIGHT:
			iter->rt.left -= iter->speed;
			iter->rt.right -= iter->speed;
			iter->rt.top += iter->v_speed;
			iter->rt.bottom += iter->v_speed;
			break;
		}

		RECT rt;
		RECT rtlter = iter->rt;

		if (iter->initspace == TOP)
		{
			if (rtlter.left > WINSIZEX || rtlter.right < 0 || rtlter.top > WINSIZEY)
			{
				_Object->GetBox().erase(iter);
				break;
			}
		}
		else if (iter->initspace == BOTTOM)
		{
			if (rtlter.left > WINSIZEX || rtlter.right < 0 || rtlter.bottom < 0)
			{
				_Object->GetBox().erase(iter);
				break;
			}
		}
		else if (iter->initspace == LEFT && rtlter.left > WINSIZEX)
		{
			if (rtlter.top > WINSIZEY || rtlter.bottom < 0 || rtlter.left > WINSIZEX)
			{
				_Object->GetBox().erase(iter);
				break;
			}
		}
		else if (iter->initspace == RIGHT && rtlter.right < 0)
		{
			if (rtlter.top > WINSIZEY || rtlter.bottom < 0 || rtlter.right < 0)
			{
				_Object->GetBox().erase(iter);
				break;
			}
		}


		if (IntersectRect(&rt, &_Player->GetPlayerBox(), &rtlter))
		{
			Score = 0;
			_Object->GetBox().erase(iter);
			break;
		}
	}
	if (ScoreDelay == 15)
	{
		Score++;
		ScoreDelay = 0;
	}
	ScoreDelay++;
}

void MainGame::Render()
{
	PAINTSTRUCT ps;
	HBRUSH Brush, oBrush;

	HDC hdc = BeginPaint(g_hWnd, &ps);								// buffer step 1
	PatBlt(g_Hdc, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);				// buffer step 2

	_Object->Render();

	Brush = CreateSolidBrush(RGB(200, 0, 0));
	oBrush = (HBRUSH)SelectObject(g_Hdc, Brush);
	_Player->Render();
	SelectObject(g_Hdc, oBrush);
	DeleteObject(Brush);

	string str;

	str = "Score";
	TextOutA(g_Hdc, 10, 30, str.c_str(), str.length());

	str = to_string(Score);
	TextOutA(g_Hdc, 50, 30, str.c_str(), str.length());

	str = "Level";
	TextOutA(g_Hdc, 10, 10, str.c_str(), str.length());

	str = to_string(Level);
	TextOutA(g_Hdc, 50, 10, str.c_str(), str.length());

	BitBlt(hdc, 0, 0, WINSIZEX, WINSIZEY, g_Hdc, 0, 0, SRCCOPY);	 // buffer step 3

	EndPaint(g_hWnd, &ps);
}
