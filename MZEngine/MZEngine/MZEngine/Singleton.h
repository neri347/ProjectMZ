#pragma once

template <typename T>
class Singleton
{
public:
	static T& Instance()
	{
		if (_instance == nullptr)
			_instance = new T();
		return *_instance;
	}

	static void Release()
	{
		delete _instance;
		_instance = nullptr;
	}

	virtual ~Singleton()
	{

	}

protected:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton(const Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(const Singleton&&) = delete;

private:
	static T* _instance;
};

template<typename T>
T* Singleton<T>::_instance = nullptr;