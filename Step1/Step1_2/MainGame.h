#pragma once
#include "GameNode.h"
#include "framework.h"
#include "Player.h"
#include "Object.h"

class MainGame : public GameNode
{
private:
	class Player* _Player;
	class Object* _Object;

	int Score;
	int Level;
public:
	MainGame();
	~MainGame();

	// GameNode를 통해 상속
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:

};

