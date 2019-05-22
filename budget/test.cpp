#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
#include "../Budget/Budget.hpp"
#include "../Budget/Parser.hpp"
#include <iostream>
using namespace std;
//TEST(TestCaseName, TestName) {
//	Budget budg;
//	list<expectation> exp;
//	string s("20.5.2019 alco:beer:bud 49\n");
//	string s1("21.5.2019 food:junk:cheaps 50\n ");
//	string s5("21.5.2019 food:junk:fish 1150\n");
//	string s2("22.5.2019 taxi 100\n");
//	string s3("23.5.2019 alco:vine:white 1000\n");
//	string es("alco:beer:bud 49\n");
//	string es1("food:junk:cheaps + food:junk:fish 1000\n");
//	string es2("alco:vine:white 2000\n");
//	stringstream ss1(s+s1+s2+s3+s5);
//	stringstream ss2(es2+es1+es);
//	spending_parser oop(ss1);
//	expectation_parser oop1(ss2);
//	Date a = { 2019, 5, 20 };
//	Date a1 = { 2019, 5, 24 };
//	auto expec = oop1.parse();
//	for (int i = 0; i < 5; i++) {
//		auto sp1 = oop.parse();
//		budg.add_spending(get<0>(sp1), get<1>(sp1), get<2>(sp1));
//	}
//	auto res =budg.calculate(a, a1, expec);
//	for (auto j : res)
//		cout << j;
//	
//}

TEST(expect_parser, parse_1_1) {
	string s2("taxi 100\n");
	stringstream ss2(s2);
	expectation_parser oop1(ss2);
	auto res = oop1.parse();
	string s("taxi");
	EXPECT_EQ(res.size(), 1);
	EXPECT_EQ(res.front().value, 100);
	EXPECT_EQ(res.front().paths.front().front(),s);
	EXPECT_EQ(res.front().paths.front().size(), 1);
	EXPECT_EQ(res.front().paths.size(), 1);
}
TEST(expect_parser, parse_1_2) {
	string s2("taxi + orbit:buble 100\n");
	stringstream ss2(s2);
	expectation_parser oop1(ss2);
	auto res = oop1.parse();
	string s("taxi");
	EXPECT_EQ(res.size(), 1);
	EXPECT_EQ(res.front().value, 100);
	EXPECT_EQ(res.front().paths.front().front(),s);
	EXPECT_EQ(res.front().paths.front().size(), 1);
	EXPECT_EQ(res.front().paths.back().size(), 2);
	EXPECT_EQ(res.front().paths.back().front(), "orbit");
	EXPECT_EQ(res.front().paths.back().back(), "buble");
	EXPECT_EQ(res.front().paths.size(), 2);
}
TEST(expect_parser, parse_2_2) {
	string s2("taxi + orbit:buble 100\n");
	string s1("exam + kitkat 250\n");
	stringstream ss2(s2+s1);
	expectation_parser oop1(ss2);
	auto res = oop1.parse();
	EXPECT_EQ(res.size(), 2);
	EXPECT_EQ(res.front().value, 100);
	EXPECT_EQ(res.back().value, 250);
	EXPECT_EQ(res.back().paths.size(), 2);
	EXPECT_EQ(res.back().paths.front().front(), "exam");
	EXPECT_EQ(res.front().paths.front().front(),"taxi");
	EXPECT_EQ(res.front().paths.front().size(), 1);
	EXPECT_EQ(res.front().paths.back().size(), 2);
	EXPECT_EQ(res.front().paths.back().front(), "orbit");
	EXPECT_EQ(res.front().paths.back().back(), "buble");
	EXPECT_EQ(res.front().paths.size(), 2);
}

TEST(spend_parser, parse_1_1) {
	string s2("20.5.2019 taxi 100\n");
	stringstream ss2(s2);
	spending_parser oop1(ss2);
	auto res = oop1.parse();
	EXPECT_EQ(get<0>(res).day, 20);
	EXPECT_EQ(get<0>(res).month, 5);
	EXPECT_EQ(get<0>(res).year, 2019);
	EXPECT_EQ(get<1>(res).front(),"taxi");
	EXPECT_EQ(get<1>(res).size(),1);
	EXPECT_EQ(get<2>(res),100.0);
}
TEST(spend_parser, parse_1_2) {
	string s2("20.5.2019 taxi:yandex 100\n");
	stringstream ss2(s2);
	spending_parser oop1(ss2);
	auto res = oop1.parse();
	EXPECT_EQ(get<0>(res).day, 20);
	EXPECT_EQ(get<0>(res).month, 5);
	EXPECT_EQ(get<0>(res).year, 2019);
	EXPECT_EQ(get<1>(res).front(),"taxi");
	EXPECT_EQ(get<1>(res).back(),"yandex");
	EXPECT_EQ(get<1>(res).size(),2);
	EXPECT_EQ(get<2>(res),100.0);
}
TEST(spend_parser, parse_1_3) {
	string s2("20.5.2019 taxi:yandex:free 100\n");
	stringstream ss2(s2);
	spending_parser oop1(ss2);
	auto res = oop1.parse();
	EXPECT_EQ(get<0>(res).day, 20);
	EXPECT_EQ(get<0>(res).month, 5);
	EXPECT_EQ(get<0>(res).year, 2019);
	EXPECT_EQ(get<1>(res).front(), "taxi");
	EXPECT_EQ(get<1>(res).back(), "free");
	EXPECT_EQ(get<1>(res).size(), 3);
	EXPECT_EQ(get<2>(res), 100.0);
}

TEST(budget, res_1) {
	string s2("20.5.2019 taxi:yandex:free 100\n");
	string es2(" taxi:yandex:free 100\n");
	Date a = { 2019, 5, 20 };
	Date a1 = { 2019, 5, 24 };
	stringstream ss2(s2);
	spending_parser oop1(ss2);
	stringstream ss3(es2);
	expectation_parser oop2(ss3);
	auto res = oop1.parse();
	auto exps = oop2.parse();
	Budget budg;
	budg.add_spending(get<0>(res), get<1>(res), get<2>(res));
	auto results = budg.calculate(a, a1, { exps });
	EXPECT_EQ(results.size(), 2);
	EXPECT_EQ(results.front().expect_cost, 100);
	EXPECT_EQ(results.front().real_cost, 100);
	EXPECT_EQ(results.front().paths.size(), 1);
	EXPECT_EQ(results.front().paths.front().size(),3);
}
TEST(budget, res_2) {
	Budget budg;
	string s2("20.5.2019 taxi:yandex:free 100\n");
	string s1("21.5.2019 smth:free 1020\n");
	string es1("smth:free 1020\n");
	string es2("taxi:yandex:free 100\n");
	Date a = { 2019, 5, 20 };
	Date a1 = { 2019, 5, 24 };
	stringstream ss2(s2+s1);
	spending_parser oop1(ss2);
	stringstream ss3(es2+es1);
	expectation_parser oop2(ss3);
	for (int i = 0; i < 2; i++) {
		auto res = oop1.parse();
		budg.add_spending(get<0>(res), get<1>(res), get<2>(res));
	}
	auto exps = oop2.parse();
	auto results = budg.calculate(a, a1,  exps );
	EXPECT_EQ(results.size(), 3);
	EXPECT_EQ(results.front().expect_cost, 100);
	EXPECT_EQ(results.front().real_cost, 100);
	EXPECT_EQ(results.front().paths.size(), 1);
	EXPECT_EQ(results.front().paths.front().size(), 3);
}
TEST(budget, res_2_1) {
	Budget budg;
	string s2("20.5.2019 taxi:yandex:free 100\n");
	string s1("21.5.2019 smth:free 1020\n");
	string es1("smth:free + taxi:yandex:free 1020\n");
	Date a = { 2019, 5, 20 };
	Date a1 = { 2019, 5, 24 };
	stringstream ss2(s2+s1);
	spending_parser oop1(ss2);
	stringstream ss3(es1);
	expectation_parser oop2(ss3);
	for (int i = 0; i < 2; i++) {
		auto res = oop1.parse();
		budg.add_spending(get<0>(res), get<1>(res), get<2>(res));
	}
	auto exps = oop2.parse();
	auto results = budg.calculate(a, a1,  exps );
	EXPECT_EQ(results.size(), 2);
	EXPECT_EQ(results.front().expect_cost, 1020);
	EXPECT_EQ(results.front().real_cost, 1120);
	EXPECT_EQ(results.front().paths.size(), 2);
	EXPECT_EQ(results.front().paths.front().size(), 2);
}

GTEST_API_ int main(int argc, char * argv[])
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