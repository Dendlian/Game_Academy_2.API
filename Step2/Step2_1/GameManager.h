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
	__forceinline static T* GetInstance() 
	{
		if (!Instance) Instance = new T;  
		return Instance;				  
	}

	template<typename T>
	__forceinline void ReleaseInstance() 
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