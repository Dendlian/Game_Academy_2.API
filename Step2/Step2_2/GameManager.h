#pragma once

/*
 // 디자인 패턴
   - 자주 사용하는 설계 형태를 정형화하여 이를 유형별로 만들어둔 것

 // 싱글톤 패턴
   - 디자인 패턴의 종류 중 하나로 단일 객체 디자인 패턴을 의미
   - 특정 클래스가 객체가 단 한개만 필요한 경우 사용
   - Example
	 KeyManager (Class) : 어떤 키가 눌렸는지 확인하는 용도

	 MovementClass
	 KeyManger = new KeyManager

	 AttackClass
	 keyManager = new KeyManger

	 SkillClass
	 keyManager = newkryManager

	 GameManager
	 {KeyManager, SoundManger, ...}
*/

#define GetManager(T) T::GetInstance<T>()
template <typename T>
class GameManager
{
protected:
	static T* Instance;

	GameManager() = default;
	~GameManager() = default;

public:
	template<typename T>
	__forceinline static T* GetInstance() // 설정
	{
		if (!Instance) Instance = new T;  // 처음 호출했을 때 Instance가 없기 때문에 새로 생성
		return Instance;				  // 두번 째부터는 계속 사용할 수 있도록 기존 값 반환
	}

	template<typename T>
	__forceinline void ReleaseInstance() // 해제
	{
		if (Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}
};

template<typename T>
T* GameManager<T>::Instance = nullptr;
// static 변수이기 때문에 클래스 밖에서 초기화
