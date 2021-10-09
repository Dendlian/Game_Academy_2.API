#include "Player.h"

void Player::Init()
{
	Player_pt = { WINSIZEX / 2, WINSIZEY - 30 };	// ������ ��Ʈ�� ��ǥ��
	MoveSpeed = 20.0f;								// ������ ��Ʈ�� �̵��ӵ�
	keyManager = GetManager(KeyManager);
	keyManager->SetUp();
}

void Player::Update()
{
	// VK_SPACE : �����̽� ����Ű
	if (keyManager->IsStayKeyDown(VK_LEFT) || keyManager->IsStayKeyDown('A'))
		Player_pt.x -= (Player_Rect.left >= MoveSpeed) ? MoveSpeed : 0;
	else if (keyManager->IsStayKeyDown(VK_RIGHT) || keyManager->IsStayKeyDown('D'))
		Player_pt.x += (Player_Rect.right <= WINSIZEX - MoveSpeed) ? MoveSpeed : 0;

	Player_Rect = RECT_MAKE(Player_pt.x, Player_pt.y, 50);
}

void Player::Render()
{ RECT_DRAW(Player_Rect); }
