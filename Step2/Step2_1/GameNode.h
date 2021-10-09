#pragma once
#define PURE = 0
class GameNode
{
public:
	GameNode() = default;
	~GameNode() = default;

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
};