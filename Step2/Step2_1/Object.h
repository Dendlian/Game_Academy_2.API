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
	int BlockDelay;		// ThrowBox�� ���� ���� ������
	int RandDelay;
	int Level;			// ���� ���̵�
	bool isFlying;
	int RandFly;

public:
	Object() = default;
	~Object() = default;

	// GameNode�� ���� ���
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:
	vector<BlockBox>& GetBox() { return vecBox; }
	__forceinline void SetLevel(int level) { Level = level; }
};

