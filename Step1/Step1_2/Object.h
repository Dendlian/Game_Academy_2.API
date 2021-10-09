#pragma once
#include "GameNode.h"
#include "framework.h"

struct ThrowBox
{
	RECT rt;
	float speed;
};

class Object : public GameNode
{
private:
	vector<ThrowBox> vecBox;
	int ThrowDelay;		// ThrowBox의 생성 간격 딜레이
	int Level;			// 게임 난이도

public:
	Object() = default;
	~Object() = default;

	// GameNode를 통해 상속
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:
	vector<ThrowBox>& GetBox() { return vecBox; }
	__forceinline void SetLevel(int level) { Level = level; }
};

