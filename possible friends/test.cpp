#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
#include "../PossibleFriends/Graph.hpp"
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
TEST(FillFindTest, three) {
  FriendsGraph g;
  stringstream ss("a b\na i\nb c\nb o\ni c\ni v\no p\n");
  g.fillGraphData(ss);
  map<string,double> pos1=g.possibleFriends("z");
  map<string,double> pos=g.possibleFriends("a");

  EXPECT_EQ(pos.size(),3);
  EXPECT_TRUE(pos["c"]-0.001<1 && pos["c"] + 0.001 > 1);
  EXPECT_TRUE(pos["o"] - 0.001 < 0.5 && pos["o"] + 0.001 > 0.5);
  EXPECT_TRUE(pos["v"] - 0.001 < 0.5 && pos["v"] + 0.001 > 0.5);
}
TEST(FillFindTest, zero) {
	FriendsGraph g;
	stringstream ss;
	g.fillGraphData(ss);
	map<string, double> pos = g.possibleFriends("a");
	EXPECT_EQ(pos.size(), 0);
}
TEST(FillFindTest, one) {
	FriendsGraph g;
	stringstream ss("aa bb\nbb oo\naa pp\nrr tt\n");
	g.fillGraphData(ss);
	map<string, double> pos = g.possibleFriends("aa");
	EXPECT_EQ(pos.size(), 1);
	EXPECT_TRUE(pos["oo"] - 0.001 < 0.5 && pos["oo"] + 0.001 > 0.5);
}

TEST(FillFindTest, p15pf9) {
	FriendsGraph g;
	ifstream in("input.txt");
	ofstream out("output.txt");
	g.fillGraphData(in);
	map<string, double> pos = g.possibleFriends("a");
	for (const auto& i : pos)
		out << i.first << " chance = " << i.second << endl;
	size_t size = pos.size();
	EXPECT_EQ(size, 9);
}

TEST(AddFindTest, three) {
	FriendsGraph g;
	g.add("a", "b");
	g.add("a", "i");
	g.add("b", "c");
	g.add("b", "o");
	g.add("i", "c");
	g.add("i", "v");
	g.add("o", "p");
	map<string, double> pos = g.possibleFriends("a");
	EXPECT_EQ(pos.size(), 3);
	EXPECT_TRUE(pos["c"] - 0.001 < 1 && pos["c"] + 0.001 > 1);
	EXPECT_TRUE(pos["o"] - 0.001 < 0.5 && pos["o"] + 0.001 > 0.5);
	EXPECT_TRUE(pos["v"] - 0.001 < 0.5 && pos["v"] + 0.001 > 0.5);
}

TEST(AddFindTest, one) {
	FriendsGraph g;
	g.add("a", "b");
	g.add("a", "i");
	g.add("b", "h");
	g.add("o", "k");
	g.add("i", "h");
	g.add("o", "p");
	map<string, double> pos = g.possibleFriends("a");
	EXPECT_EQ(pos.size(), 1);
	EXPECT_TRUE(pos["h"] - 0.001 < 1 && pos["h"] + 0.001 > 1);
}

TEST(AddExist, add) {
	FriendsGraph g;
	g.add("a", "b");
	g.add("a", "i");
	g.add("b", "h");
	g.add("o", "k");
	g.add("i", "h");
	g.add("o", "p");
	size_t before = g.getfriends("a").size();
	g.add("a", "b");
	size_t after = g.getfriends("a").size();
	EXPECT_EQ(after, before);
}

TEST(FindNexist, one) {
	FriendsGraph g;
	g.add("a", "b");
	g.add("a", "i");
	g.add("b", "h");
	g.add("o", "k");
	g.add("i", "h");
	g.add("o", "p");
	EXPECT_EQ(g.possibleFriends("z").size(), 0);
}

TEST(AddFindTest, set_three) {
	FriendsGraph g;
	set<string> friendsA = { "b","i" };
	set<string> friendsB = { "c","o" };
	set<string> friendsI = { "c","v" };
	g.add("a", friendsA);
	g.add("b", friendsB);
	g.add("i", friendsI);
	map<string, double> pos = g.possibleFriends("a");
	EXPECT_EQ(pos.size(), 3);
	EXPECT_TRUE(pos["c"] - 0.001 < 1 && pos["c"] + 0.001 > 1);
	EXPECT_TRUE(pos["o"] - 0.001 < 0.5 && pos["o"] + 0.001 > 0.5);
	EXPECT_TRUE(pos["v"] - 0.001 < 0.5 && pos["v"] + 0.001 > 0.5);
}

TEST(Addcheck, set) {
	FriendsGraph g;
	set<string> friendsA = { "b","i" };
	set<string> friendsB = { "c","o" };
	set<string> friendsI = { "c","v" };
	g.add("a", friendsA);
	g.add("b", friendsB);
	g.add("i", friendsI);
	set<string> pos = g.getfriends("b");
	EXPECT_EQ(pos.size(), 3);
	EXPECT_TRUE(pos.find("o")!=pos.end());
	EXPECT_TRUE(pos.find("c")!=pos.end());
}

TEST(Addcheck, pair) {
	FriendsGraph g;
	g.add("a", "b");
	g.add("a", "i");
	g.add("b", "c");
	g.add("b", "o");
	g.add("i", "c");
	g.add("i", "v");
	g.add("o", "p");
	set<string> pos = g.getfriends("b");
	EXPECT_EQ(pos.size(), 3);
	EXPECT_TRUE(pos.find("o") != pos.end());
	EXPECT_TRUE(pos.find("c") != pos.end());
}

TEST(Erasecheck, one) {
	FriendsGraph g;
	set<string> friendsA = { "b","i" };
	set<string> friendsB = { "c","o" };
	set<string> friendsI = { "c","v" };
	g.add("a", friendsA);
	g.add("b", friendsB);
	g.add("i", friendsI);
	g.erase("a");
	set<string> pos = g.getfriends("b");
	set<string> posi = g.getfriends("i");
	EXPECT_EQ(pos.size(), 2);
	EXPECT_EQ(posi.size(), 2);
	EXPECT_TRUE(pos.find("o") != pos.end());
	EXPECT_TRUE(pos.find("c") != pos.end());
}

TEST(Erasecheck, all) {
	FriendsGraph g;
	set<string> friendsA = { "b","i" };
	set<string> friendsB = { "c","o" };
	set<string> friendsI = { "c","v" };
	g.add("a", friendsA);
	g.add("b", friendsB);
	g.add("i", friendsI);
	g.erase("a");
	g.erase("b");
	g.erase("c");
	g.erase("v");
	g.erase("o");
	g.erase("i");
	EXPECT_TRUE(g.empty());
}

TEST(Erasecheck, nexist) {
	FriendsGraph g;
	set<string> friendsA = { "b","i" };
	set<string> friendsB = { "c","o" };
	set<string> friendsI = { "c","v" };
	g.add("a", friendsA);
	g.add("b", friendsB);
	g.add("i", friendsI);
	g.erase("k");
	set<string> pos = g.getfriends("b");
	set<string> posi = g.getfriends("i");
	EXPECT_EQ(pos.size(), 3);
	EXPECT_EQ(posi.size(), 3);
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