#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
#include "BloomFilter.hpp"
#include "BloomFilterAdapter.hpp"

unsigned int hashf(void* data)
{
    return std::hash<void*>()(data);
}

class BloomFilterTest : public ::testing::Test
{
protected:
    baseFilter<void*>* bf1;
    baseFilter<void*>* bf2;
    baseFilter<void*>* bf3;
    baseFilter<void*>* bf4;
    baseFilter<void*>* bf5;
	
    virtual void SetUp()
    {
      /*  bf1 = new BloomFilterAdapter(4, hashf, 4);
        bf2 = new BloomFilterAdapter(4, hashf, 4);
        bf3 = new BloomFilterAdapter(15, hashf, 6);*/
        bf1 = new bloomFilter<std::hash<void*>, void*>(4, std::hash<void*>(), 4);
        bf2 = new bloomFilter<std::hash<void*>, void*>(4, std::hash<void*>(), 4);
        bf3 = new bloomFilter<std::hash<void*>, void*>(15, std::hash<void*>(), 6);
    }

    virtual void TearDown()
    {
        delete bf1;
        delete bf2;
        delete bf3;
    }
};

TEST_F(BloomFilterTest, bfLoadRead)
{
    std::vector<unsigned char> arr{ 5 };
     std::vector<unsigned char> arr1(1);
     std::vector<unsigned char> arr2(1);
     bf1->load(arr);
     bf2->load(arr);
     bf1->read(arr1);
     bf2->read(arr2);
     EXPECT_EQ(arr[0], arr1[0]);
     EXPECT_EQ(arr1[0], arr2[0]);
}

TEST_F(BloomFilterTest, bfLoadReadNull)
{
    std::vector<unsigned char> arr{ 5 };
    std::vector<unsigned char> arr1(1);
    bf4 = bf1->intersection(bf3);
    bf4->load(arr);
    bf4->read(arr1);
    EXPECT_FALSE(arr[0] == arr1[0]);
    delete bf4;
}

TEST_F(BloomFilterTest, bfLoadRead16)
{
    std::vector<unsigned char> arr{5,6};
    std::vector<unsigned char> arr1(2);
    bf3->load(arr); 
    bf3->read(arr1);
    EXPECT_EQ(arr[0], arr1[0]);
    EXPECT_EQ(arr[1], arr1[1]);
}

TEST_F(BloomFilterTest, bfInsertQuery)
{
    int a = 5;
    bf1->insert(&a);
    EXPECT_EQ(bf1->query(&a),1);
}

TEST_F(BloomFilterTest, bfIntersection)
{
    int a = 5;
    bf1->insert(&a);
    bf2->insert(&a);
    bf4 = bf2->intersection(bf1);
    EXPECT_EQ(bf4->query(&a), 1);
    delete bf4;
}

TEST_F(BloomFilterTest, bfIntersectionWithNull)
{
    int a = 5;
    bf1->insert(&a);
    bf3->insert(&a);
    bf4 = bf3->intersection(bf1);
    bf5 = bf4->intersection(bf1);
    EXPECT_EQ(bf4->query(&a), 0);
    EXPECT_EQ(bf5->query(&a), 0);
    delete bf4;
    delete bf5;
}


TEST_F(BloomFilterTest, bfIntersectionItself)
{
    int a = 5;
    bf1->insert(&a);
    bf4 = bf1->intersection(bf1);
    EXPECT_EQ(bf4->query(&a), 1);
    delete bf4;
}

TEST_F(BloomFilterTest, bfIntersectionItself2)
{
    int a = 5;
    int b = 6;
    bf1->insert(&a);
    bf1->insert(&b);
    bf4 = bf1->intersection(bf1);
    EXPECT_EQ(bf4->query(&a), 1);
    EXPECT_EQ(bf4->query(&b), 1);
    delete bf4;
}

TEST_F(BloomFilterTest, bfIntersection2)
{
    int a = 5;
    int b = 6;
    bf1->insert(&a);
    bf1->insert(&b);
    bf2->insert(&a);
    bf2->insert(&b);
    bf4 = bf2->intersection(bf1);
    EXPECT_EQ(bf4->query(&a), 1);
    EXPECT_EQ(bf4->query(&b), 1);
    delete bf4;
}

TEST_F(BloomFilterTest, bfNULLIntersection)
{
    int a = 5;
    bf1->insert(&a);
    bf3->insert(&a);
    bf4 = bf3->intersection(bf1);
    EXPECT_EQ(bf4->query(&a), 0);
    delete bf4;
}

TEST_F(BloomFilterTest, bfNULLIntersection2)
{
    int a = 5;
    bf1->insert(&a);
    bf2->insert(&a);
    bf3->insert(&a);
    bf4 = bf2->intersection(bf1);
    bf5 = bf3->intersection(bf4);
    EXPECT_EQ(bf4->query(&a), 1);
    EXPECT_EQ(bf5->query(&a), 0);
    delete bf4;
    delete bf5;
}

TEST_F(BloomFilterTest, bfUnion)
{
    int a = 5;
    int b = 6;
    bf1->insert(&a);
    bf2->insert(&b);
    bf4 = bf2->unionBF(bf1);
    EXPECT_EQ(bf4->query(&a), 1);
    EXPECT_EQ(bf4->query(&b), 1);
    delete bf4;
}

TEST_F(BloomFilterTest, bfUnionWithNull)
{
    int a = 5;
    int b = 6;
    bf1->insert(&a);
    bf3->insert(&b);
    bf4 = bf3->unionBF(bf1);
    bf5 = bf4->unionBF(bf1);
    EXPECT_EQ(bf4->query(&a), 0);
    EXPECT_EQ(bf5->query(&a), 0);
    EXPECT_EQ(bf4->query(&b), 0);
    EXPECT_EQ(bf5->query(&b), 0);
    delete bf4;
    delete bf5;
}

TEST_F(BloomFilterTest, bfUnion3)
{
    int a = 5;
    int b = 6;
    int c = 7;
    bf1->insert(&a);
    bf1->insert(&c);
    bf2->insert(&b);
    bf4 = bf2->unionBF(bf1);
    EXPECT_EQ(bf4->query(&a), 1);
    EXPECT_EQ(bf4->query(&b), 1);
    EXPECT_EQ(bf4->query(&c), 1);
    delete bf4;
}

TEST_F(BloomFilterTest, bfNULLUnion)
{
    int a = 5;
    int b = 6;
    bf1->insert(&a);
    bf3->insert(&b);
    bf4 = bf3->unionBF(bf1);
    EXPECT_EQ(bf4->query(&a), 0);
    EXPECT_EQ(bf4->query(&b), 0);
    delete bf4;
}


TEST_F(BloomFilterTest, bfNULLUnion2)
{
    int a = 5;
    int b = 6;
    bf1->insert(&a);
    bf2->insert(&b);
    bf3->insert(&b);
    bf4 = bf2->unionBF(bf1);
    bf5 = bf3->unionBF(bf4);
    EXPECT_EQ(bf4->query(&a), 1);
    EXPECT_EQ(bf4->query(&b), 1);
    EXPECT_EQ(bf5->query(&b), 0);
    EXPECT_EQ(bf5->query(&a), 0);
    delete bf4;
    delete bf5;
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
