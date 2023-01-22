#pragma once
#include <vector>
#include <memory> 
#include <utility>

template<typename T>
class ObjectPool final
{
	std::unique_ptr<uint8_t[]> data;
	size_t size;
	std::vector<bool> is_empty;

public:

	ObjectPool() = delete;
	ObjectPool(size_t size) :data(std::make_unique<uint8_t[]>(size * sizeof(T))), size(size), is_empty(size, true) {}

	virtual ~ObjectPool()
	{
		for (size_t i = 0; i < size; ++i) {
			if (!is_empty[i])
				reinterpret_cast<T*>(data.get() + i * sizeof(T))->~T();
		}
			
	}

	template <typename... Args>
	T& alloc(Args&& ... args)
	{
		for (size_t i = 0; i < is_empty.size(); ++i)
		{
			if (is_empty[i])
			{
				auto p = new(data.get() + i * sizeof(T)) T{ std::forward<Args>(args)... };
				is_empty[i] = false;
				return *p;
			}
		}
		throw std::out_of_range("Pool is full!");
	};


	void free(T& obj)
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (!is_empty[i] && (data.get() + i * sizeof(T)) == reinterpret_cast<uint8_t*>(&obj))
			{
				is_empty[i] = true;
				obj.~T();
				return;
			}
		}
		throw std::out_of_range("Pool is empty!");
	};
};