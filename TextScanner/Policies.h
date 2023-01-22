#pragma once
#include <type_traits>
#include "Traits.h"


template<typename Type>
class AbstractPolicy
{
public:
	AbstractPolicy() = default;
	virtual ~AbstractPolicy() = default;
	virtual Type calculate(std::initializer_list<Type> list) const = 0;
};

template<typename Type, std::enable_if_t<(std::is_arithmetic_v<Type>), int> = 0>
class MaxPolicy : public AbstractPolicy<Type>
{
public:
	MaxPolicy() = default;
	~MaxPolicy() = default;
	Type calculate(std::initializer_list<Type> list) const override
	{
		return std::max(list);
	}
};

template<typename Type, std::enable_if_t<(std::is_arithmetic_v<Type>), int> = 0>
class MinPolicy : public AbstractPolicy<Type>
{
public:
	MinPolicy() = default;
	~MinPolicy() = default;
	Type calculate(std::initializer_list<Type> list) const override
	{
		return std::min(list);
	}
};

template<typename Type, std::enable_if_t<(std::is_arithmetic_v<Type>), int> = 0>
class AveragePolicy : public AbstractPolicy<Type>
{
public:
	AveragePolicy() = default;
	~AveragePolicy() = default;
	Type calculate(std::initializer_list<Type> list) const override
	{
		typedef typename Traits<Type>::Trait Trait;
		Trait sum = Trait();
		for (const auto& elem : list) {
			sum = sum + elem;
		}
		return static_cast<Type>(sum / list.size());
	}
};