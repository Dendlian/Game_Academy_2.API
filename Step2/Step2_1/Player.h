#pragma once
#include "GameNode.h"
#include "framework.h"
#include "KeyManager.h"

struct isJumping
{
	BOOL ing_UP;
	BOOL ing_DOWN;
};

class Player : public GameNode
{
private:
	POINT			Player_pt;
	RECT			Player_Rect[4];
	float			MoveSpeed;
	KeyManager*		keyManager;
	isJumping		isjumping;
	int				StepDelay;

public:
	Player() = default;
	~Player() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	RECT& GetPlayerBox(int num) { return Player_Rect[num]; }
};

