#pragma once

template <typename T>
class Singleton
{
public:
	Singleton(T&&) = delete;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

public:
	static T& getInstance()
	{
		static T instance;
		return instance;
	};
};

