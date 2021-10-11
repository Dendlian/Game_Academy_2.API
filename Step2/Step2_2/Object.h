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
	int ThrowDelay;		// ThrowBox�� ���� ���� ������
	int Level;			// ���� ���̵�
	int RandOriental;	// 4���� ���� �� �ڽ� ���� ��Ҹ� �������� ���Ͽ� ����
	int RandMove;		// �ڽ��� �����̴� ������ ����

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

