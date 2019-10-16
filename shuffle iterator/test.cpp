#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
#include "shuffle_range.hpp"
#include <unordered_map>

TEST(vec, empty) {
	std::vector<int> vec =  {};
	auto sh = make_shuffle(vec.begin(), vec.end());

	int amount = 0;
	for (auto i : sh) {
		amount++;
	}
	std::cout<<std::endl;
	EXPECT_EQ(amount, vec.size());
}

TEST(containers, amount_check) {
	std::vector<int> vec = { 1,2,3,11,5,0 };
	int ar[] = { 1,2,3,11,5,0 };
	std::vector<char> v1 = { 'a','b','c','d' };
	std::unordered_map< int, int > c = {
	{ 0, 0 }, { 4, 0 }, { 5, 0 }, { 2, 0 }, { 8, 0 }, { 1, 0 }
	};
	auto sh = make_shuffle(vec.begin(), vec.end());
	auto sh1 = make_shuffle(v1.begin(), v1.end());
	auto sh2 = make_shuffle(c.begin(), c.end());
	auto sh3 = make_shuffle(ar, ar + 6);
	int amount = 0;
	for (auto i : sh3) {
		amount++;
	}
	EXPECT_EQ(amount, 6);
	amount = 0;
	for (auto i : sh) {
		amount++;
	}
	EXPECT_EQ(amount, vec.size());
	amount = 0;
	for (auto i : sh1)
		amount++;
	EXPECT_EQ(amount, v1.size());
	amount = 0;
	for (auto i : sh2)
		amount++;
	EXPECT_EQ(amount, c.size());
	
}

TEST(vec,algs)
{
	std::vector<int> vec = { 1,2,3,11,5,0 };
	auto sh = make_shuffle(vec.begin(), vec.end());
	std::random_device rd;
	std::mt19937 alg(rd());
	shuffle(vec.begin(), vec.end(), alg);
	int amount = 0;
	for (auto i : sh)
		amount++;
	EXPECT_EQ(amount, vec.size());
}
TEST(vec_const, algs)
{
	std::vector< int> vec = { 1,2,3,11,5,0 };
	const auto sh = make_shuffle(vec.begin(), vec.end());
	std::random_device rd;
	std::mt19937 alg(rd());
	shuffle(vec.begin(), vec.end(), alg);
	int amount = 0;
	for (auto i : sh)
		amount++;
	EXPECT_EQ(amount, vec.size());
}



TEST(vec_vec, algs)
{
	std::vector<std::vector<int>> vec = { { 1, 2, 3, 11, 5, 0 },{ 1,2,3,11,5,0 },{ 1,2,3,11,5,0 } };
	auto sh = make_shuffle(vec.begin(), vec.end());
	int amount = 0;
	for (auto i : sh)
		amount++;
	EXPECT_EQ(amount, vec.size());
}
TEST(vec,value)
{
	std::vector<int> vec = { 1,2,3,11,5,0 };
	auto sh = make_shuffle(vec.begin(), vec.end());
	std::set<int> s;
	for(auto i:sh)
	{
		s.insert(i);
	}
	EXPECT_EQ(s.size(), vec.size());
	for(auto i:vec)
	{
		s.insert(i);
	}
	EXPECT_EQ(s.size(), vec.size());
}

TEST(eq_operator,dflt)
{
	std::vector<int> v{1};
	auto sh = make_shuffle(v.begin(), v.end());
	auto sh1 = make_shuffle(v.begin(), v.end());
	EXPECT_FALSE(sh.begin() == sh1.begin());
}

TEST(eq_operator, cnst)
{
	std::vector<int> v{ 1 };
	const auto sh = make_shuffle(v.begin(), v.end());
	const auto sh1 = make_shuffle(v.begin(), v.end());
	EXPECT_FALSE(sh.begin() == sh1.begin());
}
TEST(eq_operator, cnst1)
{
	std::vector<int> v{ 1 };
	const auto sh = make_shuffle(v.cbegin(), v.cend());
	const auto sh1 = make_shuffle(v.cbegin(), v.cend());
	EXPECT_FALSE(sh.begin() == sh1.begin());
}
TEST(cnst_cbegin, operator_star)
{
	std::vector<int> v{ 1 };
	const auto sh = make_shuffle(v.begin(), v.end());
	EXPECT_TRUE((*sh.begin())==1);
}
TEST(begin, oper_star)
{
	std::vector<int> v{ 1 };
	auto sh = make_shuffle(v.begin(), v.end());
	*(sh.begin()) = 6; 
	EXPECT_TRUE(*sh.begin() == 6);
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