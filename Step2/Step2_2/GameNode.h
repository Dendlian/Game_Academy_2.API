#pragma once
#define PURE = 0

class GameNode
{
public:
	GameNode() = default;
	~GameNode() = default;

	// 순수가상함수
	// Init() : 클래스의 맴버들을 초기화하는 함수
	virtual void Init() PURE;
	// Update() : 클래스 맴버의 값이 계속해서 변동될 때 호출하는 함수
	virtual void Update() PURE;
	// Render() L 시각적인 요소가 변화할 때 호출하는 함수
	virtual void Render() PURE;
};