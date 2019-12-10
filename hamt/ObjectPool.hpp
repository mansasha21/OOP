#pragma once
#include <vector>


template<typename T>
class ObjectPool final
{
	T* data;
	size_t size_;
	size_t capacity;
	std::vector<bool> accessibility;

public:

	ObjectPool() = delete;
	ObjectPool(const ObjectPool& obj);
	ObjectPool(ObjectPool&& obj) noexcept;
	ObjectPool(size_t capacity);
	
	ObjectPool& operator=(const ObjectPool& obj);
	ObjectPool& operator=(ObjectPool&& obj)noexcept;
	
	template<typename ... Args>
	T* alloc(size_t index, Args&& ... args);
	
	void delete_obj(T* obj);
	
	T& operator[] (size_t index);
	const T& operator[] (size_t index) const;
	
	void clear();
	
	bool empty_block(size_t index) const;
	bool empty() const;
	size_t size() const;
	
	T& firstNonEmpty();
	
	~ObjectPool();
};

template<typename T>
template <typename... Args>
T* ObjectPool<T>::alloc(size_t index, Args&& ... args)
{
	if (accessibility[index])
	{
		accessibility[index] = false;
		++size_;
		return new (data + index) T(std::forward<Args>(args)...);
	}
	return nullptr;
}

template<typename T>
ObjectPool<T>::ObjectPool(size_t capacity) :data(static_cast<T*> (operator new[](sizeof(T)* capacity))), size_{}, capacity(capacity)
{
	accessibility.resize(capacity, true);
}

template <typename T>
bool ObjectPool<T>::empty_block(size_t index) const
{
	return accessibility.at(index);
}


template<typename T>
void ObjectPool<T>::delete_obj(T* obj)
{
	auto i = obj - data;
	if (i < capacity && !accessibility[i])
	{
		accessibility[i] = true;
		data[i].~T();
		--size_;
	}
}

template <typename T>
T& ObjectPool<T>::operator[](size_t index)
{
	if (index < 0 || index >= capacity || accessibility[index])
		throw std::out_of_range("");
	return *(data + index);
}

template <typename T>
const T& ObjectPool<T>::operator[](size_t index) const
{
	return *(data + index);
}



template<typename T>
ObjectPool<T>::~ObjectPool()
{
	for (size_t i = 0; i < capacity; ++i)
		delete_obj(data + i);
	operator delete[](data);
}

template <typename T>
bool ObjectPool<T>::empty() const
{
	return size_ == 0;
}

template <typename T>
ObjectPool<T>::ObjectPool(const ObjectPool& obj) :data(static_cast<T*> (operator new[](sizeof(T)* obj.capacity))), size_{}, capacity(obj.capacity), accessibility(obj.accessibility)
{
	for (int i = 0; i < obj.accessibility.size(); ++i) {
		if (!obj.accessibility[i])
		{
			accessibility[i] = false;
			++size_;
			new (data + i) T(*(obj.data + i));
		}
	}
}

template <typename T>
ObjectPool<T>& ObjectPool<T>::operator=(const ObjectPool& obj)
{
	for (size_t i = 0; i < capacity; ++i)
		delete_obj(data + i);
	operator delete[](data);
	data = static_cast<T*>(operator new[](sizeof(T)* obj.capacity));
	for (unsigned int i = 0; i < obj.accessibility.size(); ++i) {
		if (!obj.accessibility[i])
		{
			accessibility[i] = false;
			++size_;
			new (data + i) T(T(*(obj.data + i)));
		}
	}
	return *this;
}

template <typename T>
void ObjectPool<T>::clear()
{
	for (size_t i = 0; i < capacity; ++i)
	{
		delete_obj(data + i);
		accessibility[i] = true;
	}
	size_ = 0;
}

template <typename T>
ObjectPool<T>::ObjectPool(ObjectPool&& obj)noexcept: data{obj.data}, size_{obj.size_}, capacity{obj.capacity}, accessibility(std::move(obj.accessibility))
{
	obj.data = nullptr;
	obj.size_ = 0;
	obj.capacity = 0;
}

template <typename T>
ObjectPool<T>& ObjectPool<T>::operator=(ObjectPool&& obj) noexcept
{
	for (size_t i = 0; i < capacity; ++i)
		delete_obj(data + i);
	operator delete[](data);
	std::swap(accessibility, obj.accessibility);
	data = obj.data;
	size_ = obj.size_;
	capacity = obj.capacity;
	obj.data = nullptr;
	obj.capacity = 0;
	obj.size_ = 0;
	return *this;
}

template <typename T>
size_t ObjectPool<T>::size() const
{
	return size_;
}

template <typename T>
T& ObjectPool<T>::firstNonEmpty()
{
	if (empty())
		throw std::out_of_range("empty pool");
	for(auto i = 0; i < accessibility.capacity(); ++i)
	{
		if (!accessibility[i])
			return *(data + i);
	}

}
