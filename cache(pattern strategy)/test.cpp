#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
#include "ÑacheApplier.h"
#include "FileCache.hpp"
#include "PoorManMemoryCache.hpp"
#include "MemoryCache.hpp"
#include "NullCache.hpp"

TEST(NullCache_, write_has_read_erase) {
	CacheApplier applier;
	NullCache nc;
	applier.set_strategy(std::make_shared<NullCache>(nc));
	nc.write("fds", "fds");
	EXPECT_FALSE(nc.has("fds"));
	EXPECT_EQ(nc.read("fds"), "");
	EXPECT_NO_THROW(nc.erase("fds"));
}

TEST(MemoryCache_, write_has_100)
{
	CacheApplier applier;
	MemoryCache mc;
	applier.set_strategy(std::make_shared<MemoryCache>(mc));
	std::string s("a");
	std::string s1("a");
	for (int i = 0; i < 100; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 100; ++i)
	{
		EXPECT_TRUE(applier.has_in_cache(s1));
		++s1[0];
	}
}

TEST(MemoryCache_, write_dont_has_50)
{
	CacheApplier applier;
	MemoryCache mc;
	applier.set_strategy(std::make_shared<MemoryCache>(mc));
	std::string s("a");
	for (int i = 0; i < 100; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 50; ++i)
	{
		EXPECT_FALSE(applier.has_in_cache(s));
		++s[0];
	}
}

TEST(MemoryCache_, write_has_erase_hasnt_100)
{
	CacheApplier applier;
	MemoryCache mc;
	applier.set_strategy(std::make_shared<MemoryCache>(mc));
	std::string s("a");
	std::string s1("a");
	for (int i = 0; i < 100; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 100; ++i)
	{
		applier.delete_from_cache(s1);
		++s1[0];
	}
	s[0] = 'a';
	for (int i = 0; i < 100; ++i)
	{
		EXPECT_FALSE(applier.has_in_cache(s));
		++s[0];
	}
}

TEST(MemoryCache_, write_read_100)
{
	CacheApplier applier;
	MemoryCache mc;
	applier.set_strategy(std::make_shared<MemoryCache>(mc));
	std::string s("a");
	for (int i = 0; i < 100; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	s[0] = 'a';
	for (int i = 0; i < 100; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s)==s);
		++s[0];
	}
}

TEST(PoorMemoryCache_, write_has_32)
{
	CacheApplier applier;
	PoorManMemoryCache mc;
	applier.set_strategy(std::make_shared<PoorManMemoryCache>(mc));
	std::string s("a");
	std::string s1("a");
	for (int i = 0; i < 32; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 32; ++i)
	{
		EXPECT_TRUE(applier.has_in_cache(s1));
		++s1[0];
	}
}

TEST(PoorMemoryCache_, write_has_64)
{
	CacheApplier applier;
	PoorManMemoryCache mc;
	applier.set_strategy(std::make_shared<PoorManMemoryCache>(mc));
	std::string s("a");
	std::string s1("a");
	for (int i = 0; i < 64; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 32; ++i)
	{
		EXPECT_TRUE(!applier.has_in_cache(s1));
		++s1[0];
	}
	for (int i = 0; i < 32; ++i)
	{
		EXPECT_TRUE(applier.has_in_cache(s1));
		++s1[0];
	}
}

TEST(PoorMemoryCache_, write_read_64)
{
	CacheApplier applier;
	PoorManMemoryCache mc;
	applier.set_strategy(std::make_shared<PoorManMemoryCache>(mc));
	std::string s("a");
	std::string s1("a");
	for (int i = 0; i < 64; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 32; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s1) == "");
		++s1[0];
	}
	for (int i = 0; i < 32; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s1) == s1);
		++s1[0];
	}
}

TEST(PoorMemoryCache_, write_erase_32)
{
	CacheApplier applier;
	PoorManMemoryCache mc;
	applier.set_strategy(std::make_shared<PoorManMemoryCache>(mc));
	std::string s("a");
	std::string s1("a");
	for (int i = 0; i < 32; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 32; ++i)
	{
		applier.delete_from_cache(s1);
		EXPECT_TRUE(!applier.has_in_cache(s1));
		++s1[0];
	}
}

TEST(FileCache_, write_has_erase_hasnt_100)
{
	CacheApplier applier;
	FileCache mc;
	applier.set_strategy(std::make_shared<FileCache>(mc));
	std::string s("a");
	std::string s1("a");
	for (int i = 0; i < 100; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 100; ++i)
	{
		applier.delete_from_cache(s1);
		++s1[0];
	}
	s[0] = 'a';
	for (int i = 0; i < 100; ++i)
	{
		EXPECT_FALSE(applier.has_in_cache(s));
		++s[0];
	}
}
TEST(FileCache_, write_has_100)
{
	CacheApplier applier;
	FileCache mc;
	applier.set_strategy(std::make_shared<FileCache>(mc));
	std::string s("a");
	std::string s1("a");
	for (int i = 0; i < 100; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 100; ++i)
	{
		EXPECT_TRUE(applier.has_in_cache(s1));
		++s1[0];
	}
}
TEST(FileCache_, write_dont_has_50)
{
	CacheApplier applier;
	FileCache mc;
	applier.set_strategy(std::make_shared<FileCache>(mc));
	std::string s("a");
	for (int i = 0; i < 100; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	for (int i = 0; i < 50; ++i)
	{
		EXPECT_FALSE(applier.has_in_cache(s));
		++s[0];
	}
}

TEST(FileCache_, write_read_100)
{
	CacheApplier applier;
	FileCache mc;
	applier.set_strategy(std::make_shared<FileCache>(mc));
	std::string s("a");
	for (int i = 0; i < 100; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	s[0] = 'a';
	for (int i = 0; i < 100; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s) == s);
		++s[0];
	}
}
TEST(FileCache_woApp, write_50_read_100)
{
	CacheApplier applier;
	FileCache mc;
	applier.set_strategy(std::make_shared<FileCache>(mc));
	std::string s("a");
	for (int i = 0; i < 50; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	s[0] = 'a';
	for (int i = 0; i < 50; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s) == s);
		++s[0];
	}
	for (int i = 50; i < 100; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s) == "");
		++s[0];
	}
}
TEST(MemoryCache_woApp, write_50_read_100)
{
	CacheApplier applier;
	MemoryCache mc;
	applier.set_strategy(std::make_shared<MemoryCache>(mc));
	std::string s("a");
	for (int i = 0; i < 50; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	s[0] = 'a';
	for (int i = 0; i < 50; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s) == s);
		++s[0];
	}
	for (int i = 50; i < 100; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s) == "");
		++s[0];
	}
}
TEST(PoorMemoryCache_woApp, write_50_read_100)
{
	CacheApplier applier;
	PoorManMemoryCache mc;
	applier.set_strategy(std::make_shared<PoorManMemoryCache>(mc));
	std::string s("a");
	for (int i = 0; i < 50; ++i)
	{
		applier.write_from_cache(s, s);
		++s[0];
	}
	s[0] = 'a';
	for (int i = 0; i < 18; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s) == "");
		++s[0];
	}
	for (int i = 18; i < 50; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s) == s);
		++s[0];
	}
	for (int i = 50; i < 100; ++i)
	{
		EXPECT_TRUE(applier.read_from_cache(s) == "");
		++s[0];
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