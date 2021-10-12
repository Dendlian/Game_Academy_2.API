#include "KeyManager.h"
#include "KeyManager.h"
#include "framework.h"

void KeyManager::SetUp()
{
	/// reset() : bit를 모두 0으로 설정
	BitKey_Down.reset();
	BitKey_Up.reset();
}
#pragma region GetAsyncKeyState
/*
 // GetAsyncKeyState : 키 입력 처리 함수
   - 키 입력 상태에 따라 특정한 값을 반환하는 한수 (반환값 : short)

 // 비트 연산 처리 함수
 // 0x0000 : 이전에 누른 적이 없고 호출 시점에도 눌려져 있지 않은 상태
 // 0x0001 : 이전에 누른 적이 있고 호출 시점에는 눌려져 있지 않은 상태
 // 0x8000 : 이전에 누른 적이 없고 호출 시점에는 눌려져 있는 상태
 // 0x8001 : 이전에 누른 적이 있고 호출 시점에도 눌려져 있는 상태
*/
#pragma endregion

bool KeyManager::IsOnceKeyDown(int key)
{	
	if (GetAsyncKeyState(key) & 0x8000)
	{
		/// test(value) : 현재 저장된 비트와 value가 같은지 비교
		if (!BitKey_Down.test(key)) /// 키가 이전에 눌려진 상태가 아닐 때
		{
			BitKey_Down.set(key, true);
			/// set(key, value) : 현재 저장된 비트를 key값으로 전환
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
		if (!BitKey_Down.test(key)) 
		{
			BitKey_Down.set(key, true);
			return true;
		}
		else BitKey_Down.set(key, false);
		return true;
	}
	return false;
}
