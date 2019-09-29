#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
#include <vector>
#include "radix.hpp"
template<typename T>
struct customLess {
	bool operator()(T a, T b) const
	{
		return a < b;
	}
};

template<typename T>
struct customLess1 {
	bool operator()(T a, T b) const
	{
		return a > b;
	}
};

TEST(sort,empty)
{
	customLess<int> less;
	std::vector<int> vec = {};
	radix::sort(vec.begin(), vec.end(), less);
	EXPECT_EQ(std::is_sorted(vec.begin(), vec.end()), true);
}

TEST(sort, Integer) {
	customLess<int> less;
	std::vector<int> vec = { 3,1,6,12,44,0,2323,4 };
	radix::sort(vec.begin(), vec.end(), less);
	EXPECT_EQ(std::is_sorted(vec.begin(), vec.end()), true);
}
TEST(sort, negInteger) {
	customLess<int> less;
	std::vector<int> vec = { -3,-1,-6,-12,-44, 0,-2323,-4 };
	radix::sort(vec.begin(), vec.end(), less);
	EXPECT_EQ(std::is_sorted(vec.begin(), vec.end()), true);
}
TEST(sort, reverse) {
	customLess1<int> less;
	std::vector<int> vec = { 3,-1,6,-12,44, 0,-2323,4 };
	radix::sort(vec.begin(), vec.end(), [](int a, int b)->bool {return a > b; });
	EXPECT_EQ(std::is_sorted(vec.begin(), vec.end(), less), true);
}
TEST(sort, Longlong) {
	customLess<long long> less;
	std::vector<long long> vec = { 311111111,4111111111,5111111111,461111211,449992321,0213,2123123123132323,-2131234,-1111111111111111111,111111111111 };
	radix::sort(vec.begin(), vec.end(), less);
	EXPECT_EQ(std::is_sorted(vec.begin(), vec.end()), true);
}
TEST(sort,Character ) {
	customLess<char> less;
	std::vector<char> vec = { 3,1,6,12,44,0,123,4 };
	radix::sort(vec.begin(), vec.end(), less);
	EXPECT_EQ(std::is_sorted(vec.begin(), vec.end()), true);
}
TEST(amount,Character ) {
	customLess<char> less;
	std::vector<char> vec = { 3,1,6,12,44,0,123,4 };
	radix::sort(vec.begin(), vec.end(), less);
	EXPECT_EQ(vec.size(), 8);
}
TEST(value, Character) {
	customLess<char> less;
	std::vector<char> vec =  { 3,1,6,12,44,0,123,4 };
	std::vector<char> vec1 = { 3,1,6,12,44,0,123,4 };
	radix::sort(vec.begin(), vec.end(), less);
	std::sort(vec1.begin(), vec1.end()); 
	std::vector<char> vec2;
	std::set_intersection(vec.begin(), vec.end(), vec1.begin(), vec1.end(), std::back_inserter(vec2));
	EXPECT_EQ(vec.size(), vec2.size());
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