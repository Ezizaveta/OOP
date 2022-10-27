#include "gtest/gtest.h"
#include "../ObjectPool/ObjectPool.h"
#include "DataStructs.h"

TEST(Int, AllocFree) {
	ObjectPool<int> p(10);
	std::vector<int*> vec;
	for (size_t i = 0; i < 10; ++i)
		vec.push_back(p.alloc());
	for (auto& it : vec)
		p.free(it);
	vec.clear();
	for (int i = 0; i < 10; ++i)
		EXPECT_NO_THROW(vec.push_back(p.alloc(5)));
	for (auto& it : vec) {
		EXPECT_EQ(*it, 5);
	}
}

TEST(Double, AllocFree) {
	ObjectPool<double> p(10);
	std::vector<double*> vec;
	for (size_t i = 0; i < 10; ++i)
		vec.push_back(p.alloc());
	for (auto& it : vec)
		p.free(it);
	vec.clear();
	for (int i = 0; i < 10; ++i)
		EXPECT_NO_THROW(vec.push_back(p.alloc(12.0)));
	for (auto& it : vec) {
		EXPECT_EQ(*it, 12.0);
	}
}
//Point Tests
TEST(PointTest, Default)
{
	ObjectPool<Point> p(10);
	auto p1 = p.alloc();
	EXPECT_EQ(p1->X(), 0);
	EXPECT_EQ(p1->Y(), 0);
}

TEST(PointTest, Initializer) {
	ObjectPool<Point> p(10);
	auto p1 = p.alloc(1, 1);
	EXPECT_EQ(p1->X(), 1);
	EXPECT_EQ(p1->Y(), 1);
}
TEST(PointTest, EmptyPool) {
	ObjectPool<Point> p(0);
	EXPECT_ANY_THROW(p.alloc());
}
/*
TEST(PointTest, FewElements) {
	ObjectPool<Point> p(2);
	Point* p0 = p.alloc();
	EXPECT_EQ(p0->X(), 0);
	EXPECT_EQ(p0->Y(), 0);

	auto p1 = p.alloc(1, 2);
	EXPECT_ANY_THROW(p.alloc(3, 2));
	EXPECT_EQ(p1->X(), 1);
	EXPECT_EQ(p1->Y(), 1);
	p.free(p1); //not delete object
	EXPECT_NO_THROW(p.alloc(3, 2));
	EXPECT_EQ(p1->X(), 3);
	EXPECT_EQ(p1->Y(), 2);
}*/
TEST(PointTest, FreeDefault) {
	ObjectPool<Point> p(10);
	auto p1 = p.alloc();
	p.free(p1);
	p.alloc(11, 11);
	EXPECT_EQ(p1->X(), 11);
	EXPECT_EQ(p1->Y(), 11);
}

TEST(VectorOfPoints, AllocFree) {
	ObjectPool<Point> p(10);
	std::vector<Point*> vec;
	for (int i = 0; i < 10; ++i)
		vec.push_back(p.alloc());
	for (auto& it : vec)
		p.free(it);
	vec.clear();
	for (int i = 0; i < 10; ++i)
		EXPECT_NO_THROW(vec.push_back(p.alloc(1, 1)));
	for (auto& it : vec) {
		EXPECT_EQ(it->X(), 1);
		EXPECT_EQ(it->Y(), 1);
	}
}
//Board Tests

TEST(BoardTest, Default)
{
	ObjectPool<Board> p(10);
	auto p1 = p.alloc();
	EXPECT_EQ(p1->Cols(), 0);
	EXPECT_EQ(p1->Rows(), 0);
}

TEST(BoardTest, Initializer) {
	ObjectPool<Board> p(10);
	auto p1 = p.alloc(1, 1);
	EXPECT_EQ(p1->Cols(), 1);
	EXPECT_EQ(p1->Rows(), 1);
}
TEST(BoardTest, EmptyPool) {
	ObjectPool<Board> p(0);
	EXPECT_ANY_THROW(p.alloc());
}
/*
TEST(BoardTest, FewElements) {
	ObjectPool<Board> p(2);
	Board* p0 = p.alloc();
	EXPECT_EQ(p0->Cols(), 0);
	EXPECT_EQ(p0->Rows(), 0);

	auto p1 = p.alloc(1, 2);
	EXPECT_ANY_THROW(p.alloc(3, 2));
	EXPECT_EQ(p1->Cols(), 1);
	EXPECT_EQ(p1->Rows(), 1);
	p.free(p1); //not delete object
	EXPECT_NO_THROW(p.alloc(3, 2));
	EXPECT_EQ(p1->Cols(), 3);
	EXPECT_EQ(p1->Rows(), 2);
}*/
TEST(BoardTest, FreeDefault) {
	ObjectPool<Board> p(10);
	auto p1 = p.alloc();
	p.free(p1);
	p.alloc(11, 11);
	EXPECT_EQ(p1->Cols(), 11);
	EXPECT_EQ(p1->Rows(), 11);
}
TEST(BoardTest, AllocFree) {
	ObjectPool<Board> p(10);
	std::vector<Board*> vec;
	for (int i = 0; i < 10; ++i)
		vec.push_back(p.alloc());
	for (auto& it : vec)
		p.free(it);
	vec.clear();
	for (int i = 0; i < 10; ++i)
		EXPECT_NO_THROW(vec.push_back(p.alloc(10, 5)));
	for (auto& it : vec) {
		EXPECT_EQ(it->Cols(), 10);
		EXPECT_EQ(it->Rows(), 5);
	}	
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}