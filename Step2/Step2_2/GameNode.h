#pragma once
#define PURE = 0

class GameNode
{
public:
	GameNode() = default;
	~GameNode() = default;

	// ���������Լ�
	// Init() : Ŭ������ �ɹ����� �ʱ�ȭ�ϴ� �Լ�
	virtual void Init() PURE;
	// Update() : Ŭ���� �ɹ��� ���� ����ؼ� ������ �� ȣ���ϴ� �Լ�
	virtual void Update() PURE;
	// Render() L �ð����� ��Ұ� ��ȭ�� �� ȣ���ϴ� �Լ�
	virtual void Render() PURE;
};