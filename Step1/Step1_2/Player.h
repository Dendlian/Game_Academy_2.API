#pragma once
#include "GameNode.h"
#include "framework.h"
#include "KeyManager.h"

class Player : public GameNode
{
private:
	POINT			Player_pt{ 100,100 };		// ������ ��Ʈ�� ��ǥ��
	RECT			Player_Rect;				// ������ ��Ʈ
	float			MoveSpeed = 20.0f;			// ������ ��Ʈ�� �̵��ӵ�
	KeyManager		*keyManager;				// Ű �Ŵ����� �޾ƿ� ������ ����

public:
	Player() = default;
	~Player() = default;

	// GameNode�� ���� ���
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:
	RECT& GetPlayerBox() { return Player_Rect; }
};

