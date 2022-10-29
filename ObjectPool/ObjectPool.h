#pragma once
#include <vector>
#include <memory> 
#include <utility>

template<typename T>
class ObjectPool final
{
	std::unique_ptr<T[]> data;
	size_t size;
	std::vector<bool> is_empty;

public:

	ObjectPool() = delete;
	ObjectPool(size_t size) :data(std::make_unique<T[]>(size)), size(size)
	{
		is_empty.resize(size, true);
	}
	ObjectPool(const ObjectPool<T>& other) : data(new T(*other.data)), size(other.size),
		is_empty(other.is_empty) {};
	virtual ~ObjectPool()
	{
		for (size_t i = 0; i < size; ++i)
			free(data.get() + i);

		data.release();
	}
	ObjectPool<T>& operator=(const ObjectPool<T>& other)
	{
		data.reset(new T(*other.data));
		return *this;
	}

	template <typename... Args>
	T* alloc(Args&& ... args)
	{
		for (size_t i = 0; i < is_empty.size(); ++i)
		{
			if (is_empty[i])
			{
				is_empty[i] = false;
				return  (new (data.get() + i) T(std::forward<Args>(args)...));
			}
		}
		throw std::out_of_range("Pool is full");
	};


	void free(T* obj)
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (!is_empty[i] && (data.get() + i) == obj)
			{
				is_empty[i] = true;
				obj->~T();
				return;
			}
		}
	};
};