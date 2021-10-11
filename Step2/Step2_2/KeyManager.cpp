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
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!BitKey_Down.test(key))
		{
			BitKey_Down.set(key, true);
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
