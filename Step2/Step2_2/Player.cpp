#include "Player.h"

void Player::Init()
{
	Player_pt = { WINSIZEX / 2, WINSIZEY / 2 };	// 조작할 렉트의 좌표값
	MoveSpeed = 10.0f;								// 조작할 렉트의 이동속도
	keyManager = GetManager(KeyManager);
	keyManager->SetUp();
}

void Player::Update()
{
	// VK_SPACE : 스페이스 단축키
	if (keyManager->IsStayKeyDown(VK_LEFT) || keyManager->IsStayKeyDown('A'))
		Player_pt.x -= (Player_Rect.left >= MoveSpeed) ? MoveSpeed : 0;
	else if (keyManager->IsStayKeyDown(VK_RIGHT) || keyManager->IsStayKeyDown('D'))
		Player_pt.x += (Player_Rect.right <= WINSIZEX - MoveSpeed) ? MoveSpeed : 0;
	else if (keyManager->IsStayKeyDown(VK_UP) || keyManager->IsStayKeyDown('W'))
		Player_pt.y -= (Player_Rect.top >= MoveSpeed) ? MoveSpeed : 0;
	else if (keyManager->IsStayKeyDown(VK_DOWN) || keyManager->IsOnceKeyDown('S'))
		Player_pt.y += (Player_Rect.bottom <= WINSIZEY - MoveSpeed) ? MoveSpeed : 0;
	Player_Rect = RECT_MAKE(Player_pt.x, Player_pt.y, 15);
}

void Player::Render()
{
	RECT_DRAW(Player_Rect);
}
