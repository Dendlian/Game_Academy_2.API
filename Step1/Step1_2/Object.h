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
	int ThrowDelay;		// ThrowBox�� ���� ���� ������
	int Level;			// ���� ���̵�

public:
	Object() = default;
	~Object() = default;

	// GameNode�� ���� ���
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:
	vector<ThrowBox>& GetBox() { return vecBox; }
	__forceinline void SetLevel(int level) { Level = level; }
};

