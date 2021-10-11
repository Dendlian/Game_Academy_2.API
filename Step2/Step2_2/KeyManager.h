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
	// Ű �Ŵ��� �ʱ�ȭ
	void SetUp();

	// Ű�� �� �� ������ �� �˻�
	bool IsOnceKeyDown(int key);

	// Ű�� �� �� �������� �� �˻�
	bool IsOnceKeyUp(int key);

	// Ű�� ������ �ִ����� �˻�
	bool IsStayKeyDown(int key);
};

