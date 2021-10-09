#pragma once

/*
 // ������ ����
   - ���� ����ϴ� ���� ���¸� ����ȭ�Ͽ� �̸� �������� ������ ��

 // �̱��� ����
   - ������ ������ ���� �� �ϳ��� ���� ��ü ������ ������ �ǹ�
   - Ư�� Ŭ������ ��ü�� �� �Ѱ��� �ʿ��� ��� ���
   - Example
     KeyManager (Class) : � Ű�� ���ȴ��� Ȯ���ϴ� �뵵

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
	__forceinline static T* GetInstance() // ����
	{
		if (!Instance) Instance = new T;  // ó�� ȣ������ �� Instance�� ���� ������ ���� ����
		return Instance;				  // �ι� °���ʹ� ��� ����� �� �ֵ��� ���� �� ��ȯ
	}

	template<typename T>
	__forceinline void ReleaseInstance() // ����
	{
		if (Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}
};

template<typename T>
T * GameManager<T>::Instance = nullptr;
// static �����̱� ������ Ŭ���� �ۿ��� �ʱ�ȭ
