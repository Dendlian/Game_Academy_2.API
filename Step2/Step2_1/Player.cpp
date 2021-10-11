#include "Player.h"

void Player::Init()
{
	Player_pt = { 50,WINSIZEY - 130 };
	MoveSpeed = 8.0f;
	keyManager = GetManager(KeyManager);
	keyManager->SetUp();
	isjumping.ing_DOWN = false;
	isjumping.ing_UP = false;
	StepDelay = 0;
}

void Player::Update()
{
	if (keyManager->IsOnceKeyDown(VK_SPACE) && !isjumping.ing_DOWN && !isjumping.ing_UP)
		isjumping.ing_UP = true;
	if (isjumping.ing_UP && Player_pt.y > WINSIZEY - 280)
		Player_pt.y -= MoveSpeed;
	else
	{
		isjumping.ing_UP = false;
		isjumping.ing_DOWN = true;
	}
	if (isjumping.ing_DOWN && Player_pt.y < WINSIZEY - 130)
		Player_pt.y += MoveSpeed;
	else isjumping.ing_DOWN = false;

	Player_Rect[0] = RECT_MAKE(Player_pt.x, Player_pt.y, 50);
	Player_Rect[1] = { Player_pt.x / 2, Player_pt.y + 25, Player_pt.x / 2 + 20, Player_pt.y + 55 };
	Player_Rect[2] = { Player_pt.x / 2 + 30, Player_pt.y + 25, Player_pt.x / 2 + 50, Player_pt.y + 55 };
	Player_Rect[3] = { Player_pt.x / 2, Player_pt.y + 25, Player_pt.x / 2 + 20, Player_pt.y + 40 };
	Player_Rect[4] = { Player_pt.x / 2 + 30, Player_pt.y + 25, Player_pt.x / 2 + 50, Player_pt.y + 40 };
	Player_Rect[5] = RECT_MAKE(Player_pt.x + 35, Player_pt.y - 30, 40);


	if (keyManager->IsStayKeyDown(VK_DOWN) && !isjumping.ing_UP && !isjumping.ing_DOWN)
	{
		Player_Rect[5] = RECT_MAKE(Player_pt.x + 35, Player_pt.y, 40);
	}

}

void Player::Render()
{
	RECT_DRAW(Player_Rect[0]);
	
	if (!isjumping.ing_UP && !isjumping.ing_DOWN)
	{
		if (StepDelay > 0 && StepDelay <= 10)
		{
			RECT_DRAW(Player_Rect[1]);
			RECT_DRAW(Player_Rect[4]);
		}
		else if (StepDelay > 10 && StepDelay <= 20)
		{
			RECT_DRAW(Player_Rect[2]);
			RECT_DRAW(Player_Rect[3]);
		}
		else if (StepDelay > 20)
			StepDelay = 0;
	}
	else 
	{
		RECT_DRAW(Player_Rect[3]);
		RECT_DRAW(Player_Rect[4]);
	}

	StepDelay++;
	RECT_DRAW(Player_Rect[5]);

	HBRUSH Brush, oBrush;
	Brush = CreateSolidBrush(RGB(200, 0, 0));
	oBrush = (HBRUSH)SelectObject(g_Hdc, Brush);
	if (keyManager->IsStayKeyDown(VK_DOWN) && !isjumping.ing_UP && !isjumping.ing_DOWN)
		Ellipse(g_Hdc, Player_pt.x + 40, Player_pt.y - 10, Player_pt.x + 45, Player_pt.y - 5);
	else Ellipse(g_Hdc, Player_pt.x + 40, Player_pt.y - 40, Player_pt.x + 45, Player_pt.y - 35);
	SelectObject(g_Hdc, oBrush);
	DeleteObject(Brush);
}
