#include <vector>
#include <functional>
#include <list>
#include <deque>
#include <array>
#include "gtest/gtest.h"
#include "../FilterIterator/filter_iterator.h"

std::function<bool(int)> is_even = [](int x) {return x % 2 == 0; };

template<typename T>
std::function<bool(T)> is_greater_10 = [](T x) {return x > 10; };

template<typename T1, int Val>
using my_arr = std::array<T1, Val>;

class IsGreaterTen final
{
private:
	int ten = 10;
public:
	bool operator()(int num) { return ten < num; }
};

class IsTen final
{
private:
	int ten = 10;
public:
	bool operator()(int num) { return ten == num; }
};

TEST(Vector, NestedFilter)
{
	std::vector<int> v1{ 1, 8, 32, 4, 2, 132, 12, 44 };
	auto f1 = make_filter_iterator(is_even, v1.begin(), v1.end());
	EXPECT_EQ(8, *f1);
	auto f2 = make_filter_iterator(IsGreaterTen(), f1);
	EXPECT_EQ(32, *f2);

}


TEST(StdArray, MakeFilter1)
{
	EXPECT_TRUE(std::is_default_constructible_v<IsTen>);
	std::array<int, 5> v1 = { 1, 10, 3, 11, 10 };
	auto f1 = make_filter_iterator(IsTen(), v1.begin(), v1.end());
	EXPECT_EQ(10, *f1);

	auto end = filter_iterator<IsTen, std::array<int, 5>::iterator>();
	//filter_iterator<IsTen,my_arr<int, 5>> end();
	while (f1 != end)
	{
		EXPECT_NO_THROW(*f1);
		++f1;
	}
	EXPECT_ANY_THROW(++f1);
	EXPECT_ANY_THROW(*f1);
}


TEST(StdArray, MakeFilter2)
{
	EXPECT_TRUE(std::is_default_constructible_v<IsTen>);
	std::array<int, 5> v1 = { 1, 10, 3, 11, 10 };
	auto f1 = make_filter_iterator<IsTen>(v1.begin(), v1.end());
	EXPECT_EQ(10, *f1);
	auto end = filter_iterator<IsTen, std::array<int, 5>::iterator>();
	while (f1 != end)
	{
		EXPECT_NO_THROW(*f1);
		++f1;
	}
	EXPECT_ANY_THROW(*f1);
	EXPECT_ANY_THROW(++f1);
	EXPECT_ANY_THROW(*end);
	EXPECT_ANY_THROW(++end);
}

TEST(Deque, ThrowIsEvenInt)
{
	std::deque<int> v1{ 1, 3, 4, 5 };
	auto f1 = filter_iterator<std::function<bool(int)>, std::deque<int>::iterator>
		(is_greater_10<int>, v1.begin(), v1.end());
	EXPECT_ANY_THROW(*f1);
}

TEST(Vector, IsEvenInt) //*
{
	std::vector<int> v1{ 1, 2, 3, 4, 6, 8, 9, 7, 10 };
	auto f1 = make_filter_iterator(is_even, v1.begin(), v1.end());
	EXPECT_EQ(2, *f1);
	for (size_t i = 0; i < 2; i++)
	{
		++f1;
	}
	EXPECT_EQ(6, *f1);
}

TEST(Deque, IsGreaterDouble)
{
	std::deque<double> v1{ 1.0, 32.0, 4.0, 2.0, 132.0, 12.0, 44.0 };
	auto f1 = make_filter_iterator(is_greater_10<double>, v1.begin(), v1.end());
	EXPECT_EQ(32.0, *f1);
	for (size_t i = 0; i < 1; i++)
	{
		++f1;
	}
	EXPECT_EQ(132, *f1);
}

TEST(List, Constructor1)
{
	std::list<int> v1{ 1, 32, 323, 4, 2, 132, 12 };
	auto f1 = filter_iterator<std::function<bool(int)>, std::list<int>::iterator>
		(is_greater_10<int>, v1.begin(), v1.end());
	EXPECT_EQ(32, *f1);
	for (size_t i = 0; i < 2; i++)
	{
		++f1;
	}
	EXPECT_EQ(132, *f1);
}

TEST(List, Constructor2)
{
	EXPECT_TRUE(std::is_default_constructible_v<IsTen>);
	std::list<int> v1{ 1, 32, 10, 323, 4, 2, 132, 12, 10 };
	auto f1 = filter_iterator<IsTen, std::list<int>::iterator>
		(v1.begin(), v1.end());
	EXPECT_EQ(10, *f1);
	for (size_t i = 0; i < 1; i++)
	{
		++f1;
	}
	EXPECT_EQ(10, *f1);
}

TEST(StdArray, IsGreaterFloat)
{
	
	std::array<float, 5> v1 = { 1.0, 32.0, 7.0, 33.0, 34.0 };
	auto f1 = filter_iterator<std::function<bool(float)>, std::array<float, 5>::iterator>
		(is_greater_10<float>, v1.begin(), v1.end());
	EXPECT_EQ(v1[1], *f1);
	for (size_t i = 0; i < 2; i++)
	{
		++f1;
	}
	EXPECT_EQ(v1[4], *f1);
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}