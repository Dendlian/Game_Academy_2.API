#pragma once
#include "GameNode.h"
#include "framework.h"
#include "KeyManager.h"

class Player : public GameNode
{
private:
	POINT			Player_pt{ 100,100 };		// 조작할 렉트의 좌표값
	RECT			Player_Rect;				// 조작할 렉트
	float			MoveSpeed = 20.0f;			// 조작할 렉트의 이동속도
	KeyManager* keyManager;				// 키 매니저를 받아올 포인터 변수

public:
	Player() = default;
	~Player() = default;

	// GameNode를 통해 상속
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:
	RECT& GetPlayerBox() { return Player_Rect; }
};

