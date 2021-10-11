#pragma once
#include "GameNode.h"
#include "framework.h"

enum Init_Space { TOP, BOTTOM, LEFT, RIGHT };

struct ThrowBox
{
	RECT rt;
	float speed;
	float v_speed;
	Init_Space initspace;
};

class Object : public GameNode
{
private:
	vector<ThrowBox> vecBox;
	int ThrowDelay;		// ThrowBox의 생성 간격 딜레이
	int Level;			// 게임 난이도
	int RandOriental;	// 4개의 방향 중 박스 생성 장소를 무작위로 정하여 생성
	int RandMove;		// 박스가 움직이는 방향을 보조

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

