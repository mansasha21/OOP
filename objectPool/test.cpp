#include <gtest/gtest.h>
#include "gtest/gtest-memleak.h"
#include "ObjectPool.hpp"

class Point final {
	int m_x, m_y;
public:
	Point()           
		: m_x(0), m_y(0) {}
	Point(int x, int y)    
		: m_x(x), m_y(y) {}
	~Point() = default;
	int x()
	{
		return m_x;
	}
	int y()
	{
		return m_y;
	}
};

class Matrix final {
private:
	double* matrix;
	size_t Cols;
	size_t Rows;
public:
	Matrix()
	{
		Cols = 0;
		Rows = 0;
		matrix = nullptr;
	};
	Matrix(size_t rows, size_t cols) {
		Rows = rows;
		Cols = cols;
		matrix = new double[Cols * Rows];

	};
	size_t cols()const
	{
		return Cols;
	}
	~Matrix() {
		if(matrix!=nullptr)
			delete matrix;
	};

};

class PointX final {
	int m_x, m_y;
public:
	PointX() = delete;
	PointX(const int x, int y)
		: m_x(x), m_y(y) {}
	~PointX() = default;
	int x()
	{
		return m_x;
	}
	int y()
	{
		return m_y;
	}
};
class C_Point final {
	int m_x, m_y;
public:
	C_Point():m_x(1),m_y(1){}
	C_Point(const C_Point& a)
	{
		m_x = a.m_x + 2;
		m_y = a.m_y + 2;
	}
	C_Point(C_Point&& a) noexcept
	{
		m_x = a.m_x + 1;
		m_y = a.m_y + 1;
	}
	
	~C_Point() = default;
	
	int x() const 
	{
		return m_x;
	}
	int y() const 
	{
		return m_y;
	}
};

TEST(point_alloc,default_create) {
	
	
	ObjectPool<Point> pp(10);
	Point* p1 = pp.alloc();
	EXPECT_EQ(p1->x(), 0);
	EXPECT_EQ(p1->y(), 0);
}

TEST(point_alloc, not_default_create) {
	ObjectPool<Point> pp(10);
	Point* p1 = pp.alloc(1,1);
	EXPECT_EQ(p1->x(), 1);
	EXPECT_EQ(p1->y(), 1);
}
TEST(point_alloc, zero_pool) {
	ObjectPool<Point> pp(0);
	EXPECT_ANY_THROW(pp.alloc());
}
TEST(point_alloc, default_create_ten) {
	ObjectPool<Point> pp(10);
	std::vector<Point*> vec;
	for (int i = 0; i < 10; ++i)
		EXPECT_NO_THROW(vec.push_back(pp.alloc()));
	EXPECT_ANY_THROW(pp.alloc());
	for (auto i : vec) {
		EXPECT_EQ((*i).x(), 0);
		EXPECT_EQ((*i).y(), 0);
	}
}
TEST(point_destroy, default_create_destroy) {
	ObjectPool<Point> pp(10);
	Point* p1 = pp.alloc();
	pp.delete_obj(p1);
	pp.alloc(22, 22);
	EXPECT_EQ(p1->x(), 22);
	EXPECT_EQ(p1->y(), 22);
}

TEST(point_alloc, default_create_destroy_create) {
	ObjectPool<Point> pp(10);
	std::vector<Point*> vec;
	for (int i = 0; i < 10; ++i)
		vec.push_back(pp.alloc());
	for (auto i : vec)
		pp.delete_obj(i);
	vec.clear();
	for (int i = 0; i < 10; ++i)
		EXPECT_NO_THROW(vec.push_back(pp.alloc(1,1)));
	for (auto i : vec) {
		EXPECT_EQ((*i).x(), 1);
		EXPECT_EQ((*i).y(), 1);
	}
}

TEST(point_destroy, empty_pool)
{
	ObjectPool<Point> pp(0);
}
TEST(point_destroy, ten_pool)
{
	ObjectPool<Point> pp(10);
}

TEST(pointx,non_default_const)
{
	ObjectPool<PointX> pp(10);
	PointX* a = pp.alloc(10, 10);
	//PointX* a1 = pp.alloc();                            OK   doesn`t work cause pointx hasn`t default constructor
	EXPECT_EQ(a->x(), 10);
	EXPECT_EQ(a->y(), 10);
}

TEST(cpoint,move_check)
{
	ObjectPool<C_Point> pp(10);
	const C_Point b;
	C_Point* a = pp.alloc(C_Point());
	EXPECT_EQ(a->x(), 2);
	EXPECT_EQ(a->y(), 2);
	EXPECT_EQ(b.x(), 1);
	EXPECT_EQ(b.y(), 1);
}

TEST(cpoint, copy_check)
{
	ObjectPool<C_Point> pp(10);
	const C_Point b;
	C_Point* a = pp.alloc(b);
	EXPECT_EQ(a->x(), 3);
	EXPECT_EQ(a->y(), 3);
	EXPECT_EQ(b.x(), 1);
	EXPECT_EQ(b.y(), 1);
}


TEST(matrix, alloc_free_alloc) {
	int size = 10;
	ObjectPool<Matrix> pp(size);
	Matrix* my_matrix[10];
	for (size_t i = 0; i < size; i++) {
		my_matrix[i] = pp.alloc(2, 5);
	}
	for (size_t i = 0; i < size; i++) {
		pp.delete_obj(my_matrix[i]);
	}
	for (size_t i = 0; i < size; i++) {
		my_matrix[i] = pp.alloc(2, 5);
		EXPECT_EQ(my_matrix[i]->cols(), 5);
	}

}



GTEST_API_ int main(int argc, char* argv[])
{
	if (argc > 0)
	{
		testing::internal::FilePath arg(argv[0]);
		const auto name = arg.RemoveDirectoryName().RemoveExtension("exe").string();
		testing::GTEST_FLAG(output) = std::string("xml:") + name + ".xml";
	}
	testing::InitGoogleTest(&argc, argv);
#if defined(_MSC_VER)
	testing::UnitTest::GetInstance()->listeners().Append(new testing::MSVCMemoryLeakListener());
#endif // defined(_MSC_VER)
	return RUN_ALL_TESTS();
}