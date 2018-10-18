#pragma once

template <typename T>

class Singleton
{
protected:
	static T *m_Instance;

public:
	Singleton() {}

	virtual ~Singleton() {}

	static T* Instance()
	{
		if (m_Instance == 0)
			m_Instance = new T;

		return m_Instance;
	}

	static void Destroy()
	{
		if (m_Instance != 0)
		{
			delete m_Instance;
			m_Instance = 0;
		}
	}
};

template <typename T> T * Singleton <T>::m_Instance = 0;
