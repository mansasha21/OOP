#include "gtest/gtest.h"
#include "../WordFind/WordFinder.hpp"
#include "gtest/gtest-memleak.h"
#include <fstream>
TEST(Simple, 2word) {
	WordFind::Trie tr;
 	tr.add("sweet");
	tr.add("girl");
	tr.add("love");
	tr.add("boy");
	tr.add("Bot");
	tr.add("book");
	std::set<std::string> foundwords=tr.findWords("hutiobolweBegr");
	std::stringstream k;
	copy(foundwords.begin(), foundwords.end(), std::ostream_iterator<std::string>(k , "\n"));
	EXPECT_EQ(2, 2);
}
TEST(Simple, file) {
	WordFind::Trie tr;
	std::ifstream inf("input.txt");
	std::ofstream outf("output.txt");
	tr.add(inf);
	std::set<std::string> foundwords = tr.findWords("lollriasme");
	copy(foundwords.begin(), foundwords.end(), std::ostream_iterator<std::string>(outf, "\n"));
	ASSERT_NO_THROW();
}
TEST(Simple, 1word) {
	WordFind::Trie tr;
	tr.add("");
	tr.add("book");
	tr.add("boook");
	tr.add("booz");
	std::stringstream k;
	std::set<std::string> foundwords = tr.findWords("hutioboklweBegr");
	copy(foundwords.begin(), foundwords.end(), std::ostream_iterator<std::string>(k, "\n"));
	EXPECT_EQ(1, 1);
}
TEST(Simple, 0word) {
	WordFind::Trie tr;
	tr.add("");
	tr.add("book");
	tr.add("boook");
	tr.add("booz");
	std::set<std::string> foundwords = tr.findWords("");
	std::stringstream k;
	copy(foundwords.begin(), foundwords.end(), std::ostream_iterator<std::string>(k, "\n"));
	EXPECT_EQ(0, 0);
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