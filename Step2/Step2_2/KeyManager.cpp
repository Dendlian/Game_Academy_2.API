#include "KeyManager.h"
#include "KeyManager.h"
#include "framework.h"

void KeyManager::SetUp()
{
	BitKey_Down.reset();
	BitKey_Up.reset();
}

bool KeyManager::IsOnceKeyDown(int key)
{
/*
 // GetAsyncKeyState : Ű �Է� ó�� �Լ�
 // Ű �Է� ���¿� ���� Ư���� ���� ��ȯ�ϴ� �Ѽ�
 // ��Ʈ ���� ó�� �Լ�
 // 0x0000 : ������ ���� ���� ���� ȣ�� �������� ������ ���� ���� ����
 // 0x0001 : ������ ���� ���� �ְ� ȣ�� �������� ������ ���� ���� ����
 // 0x8000 : ������ ���� ���� ���� ȣ�� �������� ������ �ִ� ����
 // 0x8001 : ������ ���� ���� �ְ� ȣ�� �������� ������ �ִ� ����
*/
	
	// 0x8000 (1000,0000 0000,0000)
	// & 0x0000 (0000,0000 0000,0000)
	// = 0

	if (GetAsyncKeyState(key) & 0x8000)
	{
		// test(value) : ���� ����� ��Ʈ�� value�� ������ ��
		if (!BitKey_Down.test(key)) // Ű�� ������ ������ ���� ���¶��
		{
			BitKey_Down.set(key, true);
			// set(key, value) : ���� ����� ��Ʈ�� key������ ��ȯ
			// true�� ������ �Ű������� ������ �Ǿ� �־ ���� ǥ�� ���ص� ����
			return true;
		}
	}
	else
		BitKey_Down.set(key, false);
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		BitKey_Up.set(key, false);
	else
	{
		if (BitKey_Up.test(key))
		{
			BitKey_Up.set(key, false);
			return true;
		}
	}
	return false;
}


bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool KeyManager::IsKeyToggle(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!BitKey_Down.test(key)) {
			BitKey_Down.set(key, true);
			return true;
		}
		else BitKey_Down.set(key, false);
		return true;
	}
	return false;
}
// 8000, 8001�� �������� ���ϱ� ������ ���ǹ��� �ϳ� �߰�