#pragma once
#include <vector>


template<typename T>
class ObjectPool final
{
	T* data;
	size_t size;
	std::vector<bool> accessibility;
	
public:

	ObjectPool() = delete;
	
	template<typename ... Args>
	T* alloc(Args&& ... args);
	ObjectPool(size_t size);
	void delete_obj(T* obj);
	~ObjectPool();
};

template<typename T>
template <typename... Args>
T* ObjectPool<T>::alloc(Args&& ... args)
{
	for (size_t i = 0; i < accessibility.size(); ++i)
	{
		if (accessibility[i])
		{
			accessibility[i] = false;
			return new (data + i) T(std::forward<Args>(args)...);
		}
	}
	throw std::length_error("Pool is full");
}

template<typename T>
ObjectPool<T>::ObjectPool(size_t size) :data(static_cast<T*> (operator new[] (sizeof(T) * size))), size(size)
{
	accessibility.resize(size, true);
}

template<typename T>
void ObjectPool<T>::delete_obj(T* obj)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (!accessibility[i] && (data + i) == obj)
		{
			accessibility[i] = true;
			data[i].~T();
			return;
		}
	}
}

template<typename T>
ObjectPool<T>::~ObjectPool()
{
	for (size_t i = 0; i < size; ++i)
		delete_obj(data+i);
	operator delete [] (data);
}

