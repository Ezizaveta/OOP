#include "gtest/gtest.h"
#include <deque>
#include <array>
#include <random>
#include "../QuickSortMultithread/QuickSort.h"
#include "../QuickSortMultithread/Policies.h"


template<typename T>
bool compar_less(const T& a, const T& b) { return (a < b); }

template<typename T>
bool compar_greater(const T& a, const T& b) { return (a > b); }

using namespace std;

TEST(Vector, Double)
{
	std::vector<double> v1 = { 1.0, 2.0, 7.0, 3.0, 4.0 };
	std::vector<double> v2 = { 1.0, 2.0, 3.0, 4.0, 7.0 };
	quick_sort::sort(v1.begin(), v1.end(), compar_less<double>);
	EXPECT_EQ(v1, v2);
}

TEST(Vector, Char)
{
	std::vector<char> v1 = { 'a', 'c', 'd', 'b' };
	std::vector<char> v2 = { 'a', 'b', 'c', 'd' };
	quick_sort::sort(v1.begin(), v1.end());
	EXPECT_EQ(v1, v2);
	EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));
}

TEST(Vector, Int)
{
	std::vector<int> v1 = { 1, 2, 7, 3, 4 };
	std::vector<int> v2 = { 1, 2, 3, 4, 7 };
	quick_sort::sort(v1.begin(), v1.end());
	EXPECT_EQ(v1, v2);
}

TEST(Deque, Int) {
	std::deque<int> v1 = { 1, 2, 7, 3, 4 };
	std::deque<int> v2 = { 1, 2, 3, 4, 7 };
	quick_sort::sort(v1.begin(), v1.end(), compar_less<int>);
	EXPECT_EQ(v1, v2);
}

TEST(Deque, Double) {
	std::deque<double> v1 = { 1.0, 3.0, 4.0, 2.0 };
	std::deque<double> v2 = { 1.0, 2.0, 3.0, 4.0 };
	quick_sort::sort(v1.begin(), v1.end(), compar_less<double>);
	EXPECT_EQ(v1, v2);
}

TEST(Deque, Char) {
	std::deque<char> v1 = { 'a', 'c', 'd', 'b' };
	std::deque<char> v2 = { 'a', 'b', 'c', 'd' };
	quick_sort::sort(v1.begin(), v1.end());
	EXPECT_EQ(v1, v2);
}

TEST(StdArray, FloatLess)
{
	std::array<float, 5> v = { 1.0, 2.0, 7.0, 3.0, 4.0 };
	quick_sort::sort(v.begin(), v.end(), compar_less<float>);
	EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), compar_less<float>));
}

TEST(StdArray, FloatGreater)
{
	std::array<float, 5> v = { 1.0, 2.0, 7.0, 3.0, 4.0 };
	quick_sort::sort(v.begin(), v.end(), compar_greater<float>);
	EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), compar_greater<float>));
}
TEST(StdArray, Char)
{
	std::array<char, 5> v = { 'a', 'b', 'c', 'd' };
	quick_sort::sort(v.begin(), v.end(), std::greater<char>());
	EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), std::greater<char>()));
}

TEST(Policy, Auto)
{
	AutoPolicy p;
	std::cout << p.get_threads_number(100) << std::endl;
	EXPECT_EQ(p.get_threads_number(1100), 1);
	EXPECT_EQ(p.get_threads_number(1101), 2);
	EXPECT_EQ(p.get_threads_number(2103), 3);
	EXPECT_EQ(p.get_threads_number(3604), 4);
	EXPECT_EQ(p.get_threads_number(11053), 5);
	EXPECT_EQ(p.get_threads_number(37000), 6);
	EXPECT_EQ(p.get_threads_number(66200), 7);
	EXPECT_EQ(p.get_threads_number(88800), 8);
	EXPECT_EQ(p.get_threads_number(137000), 9);
	EXPECT_EQ(p.get_threads_number(1400000), 10);
	EXPECT_EQ(p.get_threads_number(5000000), 11);
}

TEST(Vector, IntBig)
{
	const int size = 200'000;
	std::random_device rnd_device;
	std::mt19937 mersenne_engine{ rnd_device() };
	std::uniform_int_distribution<int> dist{ 0, size };
	auto gen = [&dist, &mersenne_engine]() {
		return dist(mersenne_engine);
	};
	std::vector<int> vec(size);
	std::generate(begin(vec), end(vec), gen);
	quick_sort::sort(vec.begin(), vec.end());
	EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}