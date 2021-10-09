#pragma once
#include "GameNode.h"
#include "framework.h"

struct BlockBox
{
	RECT Player_Object;
	float speed;
};

class Object : public GameNode
{
private:
	vector<BlockBox> vecBox;
	int BlockDelay;		// ThrowBox의 생성 간격 딜레이
	int RandDelay;
	int Level;			// 게임 난이도
	bool isFlying;
	int RandFly;

public:
	Object() = default;
	~Object() = default;

	// GameNode를 통해 상속
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:
	vector<BlockBox>& GetBox() { return vecBox; }
	__forceinline void SetLevel(int level) { Level = level; }
};

