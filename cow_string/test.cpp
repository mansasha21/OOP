#include "../cow_string/String.hpp"
#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
TEST(create_, empty) {
	String* s = new String();
	String* s1 = new String("");
	String * s2 = new String(*s);
	String s4(nullptr, 0);
	String s5(nullptr, s4.npos);
	EXPECT_EQ(s->size(), 0);
	EXPECT_EQ(s1->size(), 0);
	EXPECT_EQ(s2->size(), 0);
	EXPECT_EQ(s4.size(), 0);
	EXPECT_EQ(s5.size(), 0);
	EXPECT_EQ(s1->compare(*s2), 0);
	EXPECT_EQ(s1->compare(*s), 0);
	EXPECT_EQ(s2->countRef(), 2);
	EXPECT_EQ(s1->countRef(), 1);
	EXPECT_EQ(s->countRef(), 2);
	delete s1;
	delete s;
	delete s2;

}
TEST(create_, filled_same) {
	String* s = new String("213");
	String* s1 = new String("213");
	String * s2 = new String(*s);
	EXPECT_EQ(s->size(), 3);
	EXPECT_EQ(s1->size(), 3);
	EXPECT_EQ(s2->size(), 3);
	EXPECT_EQ(s1->compare(*s2), 0);
	EXPECT_EQ(s1->compare(*s), 0);
	EXPECT_EQ(s2->countRef(), 2);
	EXPECT_EQ(s1->countRef(), 1);
	EXPECT_EQ(s->countRef(), 2);
	delete s1;
	delete s;
	delete s2;
}
TEST(create_, filled_different) {
	String* s = new String("asdd");
	String* s1 = new String("Asdd");
	String * s2 = new String(*s);
	String str(nullptr, 2);
	String str1(nullptr, 0);
	String str2(*s,1,2);
	EXPECT_EQ(str.size(), 0);
	EXPECT_EQ(str1.size(), 0);
	EXPECT_EQ(str2.size(), 2);
	EXPECT_EQ(s->size(), 4);
	EXPECT_EQ(s1->size(), 4);
	EXPECT_EQ(s2->size(), 4);
	EXPECT_EQ(s1->compare(*s2), 1);
	EXPECT_EQ(s2->compare(*s), 0);
	EXPECT_EQ(s2->countRef(), 2);
	EXPECT_EQ(s1->countRef(), 1);
	EXPECT_EQ(s->countRef(), 2);
	delete s1;
	delete s;
	delete s2;
}
TEST(create_, filled_different1) {
	String* s = new String("asddf");
	String* s1 = new String("asdd");
	String * s2 = new String(*s);
	EXPECT_EQ(s->size(), 5);
	EXPECT_EQ(s1->size(), 4);
	EXPECT_EQ(s2->size(), 5);
	EXPECT_EQ(s1->compare(*s2), 1);
	EXPECT_EQ(s2->compare(*s), 0);
	delete s1;
	delete s;
	delete s2;
}
TEST(insert_, insert_chars) {
	String* s = new String("ruslan");
	String* s1 = new String("ruslan sobaka");
	String * s2 = new String(*s);
	s2->insert(6, " sobaka");
	EXPECT_EQ(s1->compare(*s2), 0);
	s->insert(0, "sobaka ");
	EXPECT_EQ(s->compare("sobaka ruslan"), 0);
	s->insert(0, "");
	s->insert(2, "");
	s->insert(12, "");
	EXPECT_EQ(s->compare("sobaka ruslan"), 0);
	s->insert(6,3,'\0');
	EXPECT_EQ(s->compare("sobaka"), -1);
	EXPECT_EQ(s->size(), 16);
	EXPECT_EQ(s2->countRef(), 1);
	EXPECT_EQ(s1->countRef(), 1);
	EXPECT_EQ(s->countRef(), 1);
	delete s1;
	delete s2;
	delete s;
}
TEST(insert_, insert_char) {
	String* s = new String("ruslan");
	String* s1 = new String("ruslan sobaka");
	String * s2 = new String(*s);
	String str;
	str.insert(0, 1, '\0');
	EXPECT_EQ(!str.empty(), true);
	s2->insert(0,1,'z');
	s1->insert(3, 2, 'd');
	EXPECT_EQ(s2->compare("zruslan"), 0);
	EXPECT_EQ(s1->compare("rusddlan sobaka"), 0);
	EXPECT_EQ(s2->countRef(), 1);
	EXPECT_EQ(s1->countRef(), 1);
	EXPECT_EQ(s->countRef(), 1);
	delete s1;
	delete s2;
	delete s;
}
TEST(plus, valid) {
	String* s = new String("ruslan");
	String* s1 = new String("sobaka");
	String * s2 = new String(*s);
	EXPECT_EQ(s->size(), 6);
	EXPECT_EQ(s2->size(), 6);
	*s += *s1;
	*s2 += "sobaka";
	EXPECT_EQ(s->size(), 12);
	EXPECT_EQ(s2->size(), 12);
	EXPECT_EQ(s2->compare(*s), 0);
	*s += *s2;
	*s2 += *s2;
	EXPECT_EQ(s->size(), 24);
	EXPECT_EQ(s2->size(), 24);
	EXPECT_EQ(s2->compare(*s), 0);
	EXPECT_EQ(s2->countRef(), 1);
	EXPECT_EQ(s1->countRef(), 1);
	EXPECT_EQ(s->countRef(), 1);
	delete s1;
	delete s2;
	delete s;
}
TEST(insert_erase, insert_erase1) {
	String* s = new String("ruslan");
	String * s2 = new String(*s);
	s->insert(0, "sobaka ");
	EXPECT_EQ(s->compare("sobaka ruslan"), 0);
	s->erase(0,7);
	EXPECT_EQ(s2->compare(*s), 0);
	EXPECT_EQ(s2->countRef(), 1);
	EXPECT_EQ(s->countRef(), 1);
	delete s2;
	delete s;
}
TEST(operator_sqs_at, eq) {
	String* s = new String("ruslan");
	String * s2 = new String(*s);
	char a = (*s)[1];
	char b = s2->at(1);
	EXPECT_EQ(a,b);
	EXPECT_EQ(s2->countRef(), 1);
	EXPECT_EQ(s->countRef(), 1);
	delete s;
	delete s2;
}
TEST(substr, sub) {
	String* s = new String("ruslan");
	String* s1 = new String("sobaka");
	String  s2 = s->substr(0, 3);
	String s3 = s1->substr(2, 3);
	EXPECT_EQ(s2.compare("rus"), 0);
	EXPECT_EQ(s3.compare("bak"), 0);
	EXPECT_EQ(s2.countRef(), 1);
	EXPECT_EQ(s3.countRef(), 1);
	EXPECT_EQ(s1->countRef(), 1);
	EXPECT_EQ(s->countRef(), 1);
	delete s1;
	delete s;
}
TEST(find, sub) {
	String* s = new String("ruslan");
	EXPECT_EQ(s->find('u'),1);
	EXPECT_EQ(s->find("rusl"), 0);
	EXPECT_EQ(s->find("rusl",1), s->npos);
	EXPECT_EQ(s->find("usl", 1), 1);
	EXPECT_EQ(s->countRef(), 1);
	delete s;
}
TEST(find_erase, fe) {
	String* s = new String("ruslan");
	*s += " ne lyubit kushat";
	s->erase(s->find("ne "), 3);
	EXPECT_EQ(s->compare("ruslan lyubit kushat"), 0);
	delete s;
}
TEST(find_erase3, fe3) {
	String* s = new String("ruslan");
	*s += " ne lyubit kushat";
	String s1(*s);
	String s2(s1);
	s->erase(s->find("ne "), 3);
	EXPECT_EQ(s->compare("ruslan lyubit kushat"), 0);
	EXPECT_EQ(s->countRef(), 1);
	EXPECT_EQ(s1.countRef(), 2);
	EXPECT_EQ(s2.countRef(), 2);
	s1.erase(s1.find("lyubit "), 7);
	EXPECT_EQ(s1.compare("ruslan ne kushat"), 0);
	EXPECT_EQ(s1.countRef(), 1);
	EXPECT_EQ(s2.countRef(), 1);
	s2.erase(s2.find("kushat", 6));
	s2 += "pisat testy";
	EXPECT_EQ(s2.compare("ruslan ne lyubit pisat testy"), 0);
	EXPECT_EQ(s2.size(), strlen("ruslan ne lyubit pisat testy"));
	delete s;
}
TEST(front_back, fb1) {
	String* s = new String("ruslan");
	EXPECT_EQ(s->front(), 'r');
	EXPECT_EQ(s->back(), 'n');
	char &a = s->front();
	a = 'b';
	char &b = s->back();
	b = 'a';
	EXPECT_EQ(s->back(), 'a');
	EXPECT_EQ(s->countRef(), 1);
	delete s;
}
TEST(replace, rep3) {
	String str;
	String str1;
	String* s = new String("ruslan");
	String * s2 = new String(*s);
	str.replace(0, 0, "ff");
	str1.replace(0, 1, "ff");
	EXPECT_EQ(str.compare("ff"), 0);
	EXPECT_EQ(str1.compare("ff"), 0);
	str.replace(0, str.npos, "a");
	EXPECT_EQ(str.compare("a"), 0);
	EXPECT_EQ(str.capacity(), 3);
	s->replace(0, 3, "bak");
	s2->replace(0, 4, "bak");
	EXPECT_EQ(s->compare("baklan"), 0);
	EXPECT_EQ(s2->compare("bakan"), 0);
	EXPECT_EQ(s->countRef(), 1);
	EXPECT_EQ(s2->countRef(), 1);
	s->replace(3, 2, 3, 'f');
	EXPECT_EQ(s->compare("bakfffn"), 0);
	s->reserve(100);
	s->replace(3, 4, 6, 'u');
	EXPECT_EQ(s->compare("bakuuuuuu"), 0);
	s->insert(s->size(), "lol");
	EXPECT_EQ(s->compare("bakuuuuuulol"), 0);
	delete s;
	delete s2;
}
TEST(reserve, 1) {
	String str;
	String* s = new String("ruslan");
	String * s2 = new String(*s);
	String * s3 = new String(*s);
	str.reserve(10);
	EXPECT_EQ(s->countRef(), 3);
	EXPECT_EQ(s3->countRef(), 3);
	EXPECT_EQ(s2->countRef(), 3);
	s->reserve(s->capacity()+10);
	EXPECT_EQ(s->countRef(), 1);
	EXPECT_EQ(s3->countRef(), 2);
	EXPECT_EQ(s2->countRef(), 2);
	EXPECT_EQ(s->capacity(), 17);
	EXPECT_EQ(str.capacity(), 10);
	EXPECT_EQ(str.empty(), true);
	EXPECT_EQ(s2->capacity(), 7);
	EXPECT_EQ(s3->capacity(), 7);
	s->insert(3, "chmo");
	EXPECT_EQ(s->compare("ruschmolan") , 0);
	delete s;
	delete s3;
	delete s2;

}
TEST(swap, swap3) {
	String str;
	String str1;
	String* s = new String("ruslan");
	String * s2 = new String("vova");
	String * s1 = new String(*s);
	str.swap(str1);
	EXPECT_EQ(str.empty(), true);
	EXPECT_EQ(str1.empty(), true);
	s->swap(*s2);
	EXPECT_EQ(s->countRef(), 1);
	EXPECT_EQ(s2->countRef(), 2);
	EXPECT_EQ(s1->countRef(), 2);
	EXPECT_EQ(s->capacity(), 5);
	EXPECT_EQ(s2->capacity(), 7);
	EXPECT_EQ(s1->capacity(), 7);
	delete s;
	delete s2;
	delete s1;
}
TEST(swap, swap3empty) {
	String str;
	String str1(str);
	String str2(str);
	str.swap(str1);
	str.swap(str2);
	EXPECT_EQ(str.empty(), true);
	EXPECT_EQ(str1.empty(), true);
	EXPECT_EQ(str2.empty(), true);
	EXPECT_EQ(str1.countRef(), 3);
	EXPECT_EQ(str.countRef(), 3);
	EXPECT_EQ(str2.countRef(), 3);
	str.reserve(10);
	EXPECT_EQ(str.capacity(), 10);
	EXPECT_EQ(str1.capacity(), 1);
	EXPECT_EQ(str2.capacity(), 1);
	EXPECT_EQ(str1.countRef(), 2);
	EXPECT_EQ(str.countRef(), 1);
	EXPECT_EQ(str2.countRef(), 2);
	str.swap(str1);
	EXPECT_EQ(str.capacity(), 1);
	EXPECT_EQ(str1.capacity(), 10);
	EXPECT_EQ(str2.capacity(), 1);
	EXPECT_EQ(str1.countRef(), 1);
	EXPECT_EQ(str.countRef(), 2);
	EXPECT_EQ(str2.countRef(), 2);
}
TEST(plus_eq, empty) {
	String s;
	String s1("");
	String s2("");
	s += '\0';
	s1 += '\0';
	s2 += "";
	EXPECT_EQ(!s.empty(), true);
	EXPECT_EQ(!s1.empty(), true);
	EXPECT_EQ(s2.empty(), true);
	s2 += nullptr;
	EXPECT_EQ(s.size(), 1);
	EXPECT_EQ(s1.size(), 1);
	EXPECT_EQ(s2.empty(), true);

}
TEST(erase, empty) {
	String s;
	String s1("");
	s.erase(0, 2);
	s1.erase(0, 5);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s1.size(), 0);
}
TEST(nullptrt, nt) {
	String s(nullptr);
	String s2(nullptr,0);
	String s1(s);
	EXPECT_EQ(s1.countRef(), 2);
	EXPECT_EQ(s.countRef(), 2);
	s2 += nullptr;
	s += "";
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s2.size(), 0);
	s1 +='\0';
	EXPECT_EQ(s1.size(), 1);
	EXPECT_EQ(s.countRef(), 1);
	EXPECT_EQ(s.countRef(), 1);
	s1.replace(0, 1, nullptr);
	EXPECT_EQ(s1.size(), 1);
	s1.replace(0, 4, "kot");
	EXPECT_EQ(s1.size(), 3);
}
TEST(clear_mptr, clear_nptr) {
	String s(nullptr);
	String s2(nullptr, 0);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s2.size(), 0);
	s.clear();
	s2.clear();
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s2.size(), 0);
}

TEST(clear_copy_mptr, clear_nptr) {
	String str;
	String s(nullptr);
	String s2(s);
	str.clear();
	EXPECT_EQ(s.countRef(), 2);
	EXPECT_EQ(s2.countRef(), 2);
	s.clear();
	EXPECT_EQ(s.countRef(), 2);
	EXPECT_EQ(s2.countRef(), 2);
	s2.clear();
	EXPECT_EQ(s.countRef(), 2);
	EXPECT_EQ(s2.countRef(), 2);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s2.size(), 0);
}
TEST(clear_valid, clear_valid) {
	String s("koko");
	String s2("lol",6);
	EXPECT_EQ(s.size(), 4);
	EXPECT_EQ(s2.size(), 3);
	s.clear();
	s2.clear();
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s2.size(), 0);
}

TEST(clear_copy_valid, clear_valid) {
	String s("koko");
	String s2(s);
	String s3(s);
	EXPECT_EQ(s.countRef(), 3);
	EXPECT_EQ(s2.countRef(), 3);
	EXPECT_EQ(s2.countRef(), 3);
	s.clear();
	EXPECT_EQ(s.countRef(), 1);
	EXPECT_EQ(s2.countRef(), 2);
	EXPECT_EQ(s3.countRef(), 2);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s.capacity(), 1);
	EXPECT_EQ(s2.capacity(), 5);
	EXPECT_EQ(s3.size(), 4);
	EXPECT_EQ(s3.size(), s2.size());
	s2.clear();
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s2.size(), 0);
}
TEST(at_empty, at_empty) {
	String s(nullptr);
	String s2(nullptr, 0);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s2.size(), 0);
	EXPECT_ANY_THROW(s.at(0););
	EXPECT_ANY_THROW(s2.at(0););
}

TEST(at_valid, at_valid) {
	String s("koko");
	String s2("lol", 6);
	EXPECT_EQ(s.size(), 4);
	EXPECT_EQ(s2.size(), 3);
	EXPECT_ANY_THROW(s.at(s.size()));
	EXPECT_ANY_THROW(s2.at(s2.size()));
}
TEST(plus, empty) {
	String str;
	str += nullptr;
	ASSERT_TRUE(str.empty());
	str += "";
	ASSERT_TRUE(str.empty());
	str += "\0";
	ASSERT_TRUE(str.empty());
	str += "lol";
	ASSERT_TRUE(!str.empty());
	EXPECT_EQ(str.size(), 3);
	str += str;
	EXPECT_EQ(str.size(), 6);
}
TEST(substr, nsubs) {
	String s("on english");
	String s1=s.substr(3);
	String s2(s1);
	String s3(s2);
	EXPECT_EQ(s.countRef(), 1);
	EXPECT_EQ(s1.countRef(), 3);
	EXPECT_EQ(s2.countRef(), 3);
	EXPECT_EQ(s3.countRef(), 3);
	EXPECT_EQ(s1.size(), 7);
	EXPECT_EQ(s3.size(), 7);
	EXPECT_EQ(s2.size(), 7);
	s2.clear();
	EXPECT_EQ(s2.countRef(), 1);
	EXPECT_EQ(s3.countRef(), 2);
	EXPECT_EQ(s1.countRef(), 2);
	EXPECT_EQ(s1.size(),s3.size());
	EXPECT_EQ(s2.size(),0);
}
TEST(def, self_other) {
	String s;
	String s1("fsd");
	String s2(s1);
	s = s;
	s1 = s1;
	EXPECT_EQ(s2.size(), s1.size());
	EXPECT_EQ(s2.size(), 3);
	EXPECT_EQ(s2.countRef(), 2);
	EXPECT_EQ(s1.countRef(), 2);
	s = s2;
	EXPECT_EQ(s2.countRef(), 3);
	EXPECT_EQ(s1.countRef(), 3);
	EXPECT_EQ(s.countRef(), 3);
	s1 = "sad";
	EXPECT_EQ(s2.countRef(), 2);
	EXPECT_EQ(s1.countRef(), 1);
	EXPECT_EQ(s.countRef(), 2);
	s2 = nullptr;
	s = "";
	EXPECT_EQ(s2.countRef(), 1);
	EXPECT_EQ(s1.countRef(), 1);
	EXPECT_EQ(s.countRef(), 1);
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