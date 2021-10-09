#pragma once
#include "GameManager.h"
#include <bitset>

using namespace std;

#define KEYMAX 256

class KeyManager : public GameManager<KeyManager>
{
private:
	bitset<KEYMAX>BitKey_Up;
	bitset<KEYMAX>BitKey_Down;

public:
	// 키 매니저 초기화
	void SetUp();

	// 키가 한 번 눌렸을 때 검사
	bool IsOnceKeyDown(int key);

	// 키가 한 번 떨어졌을 때 검사
	bool IsOnceKeyUp(int key);

	// 키를 누르고 있는지를 검사
	bool IsStayKeyDown(int key);
};

