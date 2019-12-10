#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
#include "Trie.hpp"
#include "SubTrie.hpp"


using namespace trie;
TEST(default_cnstr, empty_trie) {
	Trie<int> a;
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(copy_cnstr, empty_trie) {
	Trie<int> a;
	Trie<int> b(a);
	EXPECT_EQ(b.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(equality_oper, empty_trie) {
	Trie<int> a;
	Trie<int> b;
	b = a;
	EXPECT_EQ(b.size(), 0);
	EXPECT_TRUE(b.empty());
}
TEST(insert_element, one_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	EXPECT_EQ(a.size(), 1);
	EXPECT_FALSE(a.empty());
}
TEST(insert_element, two_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	my_str = "two";
	a.insert(my_str, 76);
	EXPECT_EQ(a.size(), 2);
	EXPECT_FALSE(a.empty());
}
TEST(find_element, one_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	EXPECT_EQ(a[my_str], 54);
}
TEST(find_element, two_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	std::string my_str_2 = "two";
	a.insert(my_str_2, 76);
	EXPECT_EQ(a[my_str], 54);
	EXPECT_EQ(a[my_str_2], 76);
}
TEST(find_element, one_element_trie_alien_elem) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	EXPECT_EQ(a[my_str], 54);
	std::string my_str_2 = "two";
	EXPECT_EQ(a[my_str_2], int());
	EXPECT_EQ(a.size(), 2);
}
TEST(find_element, two_element_trie_alien_elem) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	std::string my_str_2 = "two";
	a.insert(my_str_2, 76);
	EXPECT_EQ(a[my_str], 54);
	EXPECT_EQ(a[my_str_2], 76);
	std::string my_str_3 = "three";
	EXPECT_EQ(a[my_str_3], int());
	EXPECT_EQ(a.size(), 3);
}
TEST(copy_cnstr, one_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	Trie <int> b(a);
	EXPECT_EQ(b.size(), 1);
	EXPECT_FALSE(b.empty());
}
TEST(copy_cnstr, two_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	my_str = "two";
	a.insert(my_str, 76);
	Trie <int> b(a);
	EXPECT_EQ(b.size(), 2);
	EXPECT_FALSE(b.empty());
}
TEST(erase, one_element_trie, ) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	a.erase(my_str);
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(erase, one_element_trie_empty_str) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	a.erase(std::string());
	EXPECT_EQ(a.size(), 1);
	EXPECT_FALSE(a.empty());
}
TEST(insert_element, empty_trie_empty_str) {
	Trie <int> a;
	a.insert(std::string(), 54);
	EXPECT_EQ(a.size(), 1);
	EXPECT_FALSE(a.empty());
}
TEST(insert_element, one_element_trie_empty_str) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	a.insert(std::string(), 64);
	EXPECT_EQ(a.size(), 2);
	EXPECT_FALSE(a.empty());
}
TEST(find_element, empty_trie_empty_str) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	EXPECT_EQ(a[std::string()], int());
}
TEST(erase, two_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	std::string my_str_2 = "two";
	a.insert(my_str_2, 76);
	a.erase(my_str);
	a.erase(my_str_2);
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(erase, two_element_trie_alien_elem) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	std::string my_str_2 = "two";
	a.insert(my_str_2, 76);
	a.erase("three");
	EXPECT_EQ(a.size(), 2);
	EXPECT_FALSE(a.empty());
}
TEST(find_element, empty_trie) {
	Trie <int> a;
	std::string my_str("empty");
	EXPECT_EQ(a[my_str], int());
	EXPECT_EQ(a.size(), 1);
}
TEST(erase, empty_trie) {
	Trie <int> a;
	std::string my_str("empty");
	a.erase(my_str);
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(insert_element, one_element_trie_same_element) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	a.insert(my_str, 65);
	EXPECT_EQ(a.size(), 1);
	EXPECT_TRUE(a[my_str], 65);
}
TEST(equality_oper, one_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	Trie <int> b;
	b = a;
	EXPECT_EQ(b.size(), 1);
	EXPECT_FALSE(b.empty());
}
TEST(equality_oper, two_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	my_str = "two";
	a.insert(my_str, 76);
	Trie <int> b;
	b = a;
	EXPECT_EQ(b.size(), 2);
	EXPECT_FALSE(b.empty());
}
TEST(erase, empty_trie_empty_str)
{
	Trie <int> a;
	std::string my_str;
	a.erase(my_str);
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(swap, empty_trie)
{
	Trie <int> a, b;
	a.swap(b);
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(swap, one_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	Trie <int> b;
	b.swap(a);
	EXPECT_EQ(b.size(), 1);
	EXPECT_FALSE(b.empty());
	EXPECT_EQ(a.size(), 0);
	b.swap(a);
	EXPECT_EQ(b.size(), 0);
	EXPECT_EQ(a.size(), 1);
}
TEST(swap, two_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	my_str = "two";
	a.insert(my_str, 76);
	Trie <int> b;
	b.swap(a);
	EXPECT_EQ(b.size(), 2);
	EXPECT_EQ(a.size(), 0);
	my_str = "three";
	a.insert(my_str, 58);
	b.swap(a);
	EXPECT_EQ(b.size(), 1);
	EXPECT_EQ(a.size(), 2);
}
TEST(clear, empty_trie) {
	Trie <int> a;
	a.clear();
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(clear, one_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	a.clear();
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(clear, two_element_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	my_str = "two";
	a.insert(my_str, 76);
	a.clear();
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}

TEST(insert_element, ten_elements)
{
	std::string my_str = "hgoreihgrf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
}
TEST(erase, ten_elements)
{
	std::string my_str = "hgoreihgrf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.erase(my_str.substr(i));
	}
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(erase, alien_element)
{
	std::string my_str = "hgj";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	std::string error_my_str = "aaa";
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.erase(error_my_str.substr(i));
	}
	EXPECT_EQ(a.size(), my_str.size());
}
TEST(erase_insert, ten_elements)
{
	std::string my_str = "hgoreihgrf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.erase(my_str.substr(i));
	}
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
}

TEST(find_element, ten_elements) {
	std::string my_str = "hgoreihgrfd";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		if (i == a[my_str.substr(i)])
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(insert_element, ten_elements_str)
{
	std::string my_str = "hgoreihgrf";
	Trie <std::string> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), my_str.substr(i));
	}
	EXPECT_EQ(a.size(), my_str.size());
}
TEST(copy_cnstr, ten_elements_str)
{
	std::string my_str = "hgoreihgrf";
	Trie <std::string> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), my_str.substr(i));
	}
	EXPECT_EQ(a.size(), my_str.size());
	Trie <std::string>b(a);
	EXPECT_EQ(b.size(), my_str.size());
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		if (b[my_str.substr(i)] == a[my_str.substr(i)])
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(copy_cnstr, ten_elements)
{
	std::string my_str = "hgoreihgrf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	Trie <int>b(a);
	EXPECT_EQ(b.size(), my_str.size());
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		if (b[my_str.substr(i)] == a[my_str.substr(i)])
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(swap, ten_elements)
{
	std::string my_str = "hgoreihgrf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	Trie <int>b;
	b.swap(a);
	EXPECT_EQ(b.size(), my_str.size());
	EXPECT_EQ(a.size(), 0);
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		if (b[my_str.substr(i)] == i)
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(equality_oper, ten_elements)
{
	std::string my_str = "hgoreihgrf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	Trie <int>b;
	b = a;
	EXPECT_EQ(b.size(), my_str.size());
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		if (b[my_str.substr(i)] == a[my_str.substr(i)])
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(erase, ten_elements_str)
{
	std::string my_str = "hgoreihgrf";
	Trie <std::string > a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), my_str.substr(i));
	}
	EXPECT_EQ(a.size(), my_str.size());
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.erase(my_str.substr(i));
	}
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}

TEST(find_element, ten_elements_str) {
	std::string my_str = "hgoreihgrfd";
	Trie <std::string> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), my_str.substr(i));
	}
	EXPECT_EQ(a.size(), my_str.size());
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		if (my_str.substr(i) == a[my_str.substr(i)])
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(insert_element, many_elements)
{
	std::string my_str = "hgoreihgrfvfdbjkrfobjrtfbmrfbmpofk,vfo";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
}
TEST(erase, many_elements)
{
	std::string my_str = "hgoreihokflmnh";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.erase(my_str.substr(i));
	}
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}

TEST(find_element, many_elements) {
	std::string my_str = "hgoreihnufgir;szjf;f;gz";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		if (i == a[my_str.substr(i)])
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(insert_element, many_elements_str)
{
	std::string my_str = "hgoreihgro;gjdgcmnzmb'zn'";
	Trie <std::string> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), my_str.substr(i));
	}
	EXPECT_EQ(a.size(), my_str.size());
}
TEST(erase, many_elements_str)
{
	std::string my_str = "hgoreihbigfjogjfngf";
	Trie <std::string > a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), my_str.substr(i));
	}
	EXPECT_EQ(a.size(), my_str.size());
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.erase(my_str.substr(i));
	}
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}

TEST(find_element, many_elements_str) {
	std::string my_str = "hgoreihgrfddgnp/mf'xnomx'nmv";
	Trie <std::string> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), my_str.substr(i));
	}
	EXPECT_EQ(a.size(), my_str.size());
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		if (my_str.substr(i) == a[my_str.substr(i)])
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(iterator, one_el_trie) {
	Trie <int> a;
	std::string my_str("first");
	auto& [iterator, inserter] = a.insert(my_str, 54);
	auto [key, value] = *iterator;
	EXPECT_EQ(key, my_str);
	EXPECT_EQ(value, 54);
}
TEST(iterator, one_el_trie_str) {
	Trie <std::string> a;
	std::string my_str("first");
	std::pair<Trie<std::string>::iterator, bool> cur = a.insert(my_str, my_str);
	auto& [key, value] = *(cur.first);
	EXPECT_EQ(key, my_str);
	EXPECT_EQ(value, my_str);
}
TEST(begin, one_el_trie) {
	Trie <int> a;
	std::string my_str("first");
	a.insert(my_str, 54);
	auto& [key, value] = *a.begin();
	EXPECT_EQ(key, my_str);
	EXPECT_EQ(value, 54);
}
TEST(begin, one_el_trie_str) {
	Trie <std::string> a;
	std::string my_str("first");
	a.insert(my_str, my_str);
	auto& [key, value] = *a.begin();
	EXPECT_EQ(key, my_str);
	EXPECT_EQ(value, my_str);
}
TEST(iterator, two_elements_pref)
{
	std::string my_str = "hg";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	auto& [key, value] = *(++a.begin());
	EXPECT_EQ(key, "g");
	EXPECT_EQ(value, 1);
}
TEST(iterator, two_elements_post)
{
	std::string my_str = "hg";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	auto& [key1, value1] = *(a.begin()++);
	EXPECT_EQ(key1, my_str);
	EXPECT_EQ(value1, 0);
}
TEST(iterator, two_elements_no_equal)
{
	std::string my_str = "hg";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	size_t counter = 0;
	for (auto it = a.begin(); it != a.end(); ++it) {
		++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(iterator, ten_elements_pref)
{
	std::string my_str = "hgtyruejnf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	size_t counter = 0;
	for (auto it = a.begin(); it != a.end(); ++it) {
		++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(iterator, many_elements_pref)
{
	std::string my_str = "hgtyruejnffj";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	size_t counter = 0;
	for (auto it = a.begin(); it != a.end(); ++it) {
		++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(find_iterator, empty_trie) {
	Trie<int> a;
	auto it = (a.find("empty"));
	EXPECT_EQ(it, a.end());
}
TEST(find_iterator, one_element_trie) {
	Trie<int> a;
	std::string my_str = "first";
	a.insert(my_str, 1);
	auto it = a.find(my_str);
	EXPECT_EQ(it, a.begin());
}
TEST(find_iterator, ten_elements)
{
	std::string my_str = "hgtyruejnf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	size_t counter = 0;
	for (size_t i = 0; i < 10; ++i) {
		auto& [key, value] = *a.find(my_str.substr(i));
		if (key == my_str.substr(i) && value == i)
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(find_iterator, alien_elements)
{
	std::string my_str = "hgtyruejnf";
	std::string my_str_2 = "hiipliiijkk";
	Trie <int> a, b;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
		b.insert(my_str_2.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	size_t counter = 0;
	for (size_t i = 0; i < 10; ++i) {
		auto it = a.find(my_str_2.substr(i));
		if (it == a.end())
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(erase_iterator, empty_trie) {
	Trie<int> a;
	a.erase(a.begin());
	EXPECT_TRUE(a.empty());
}
TEST(erase_iterator, one_element_trie) {
	Trie<int> a;
	std::string my_str = "first";
	a.insert(my_str, 1);
	a.erase(a.begin());
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(erase_iterator, ten_elements)
{
	std::string my_str = "hgtyruejnf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), my_str.size());
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.erase(a.begin());
	}
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(begin, empty_trie) {
	Trie<int> a;
	EXPECT_EQ(a.begin(), a.end());
}
TEST(iterator, one_el_pref) {
	Trie<int> a;
	std::string my_str("first");
	a.insert(my_str, 51);
	EXPECT_EQ(++a.begin(), a.end());
}
TEST(iterator, empty_trie) {
	Trie<int> a;
	EXPECT_EQ(++a.begin(), a.end());
}
TEST(iterator, one_el_postf) {
	Trie<int> a;
	std::string my_str("first");
	a.insert(my_str, 51);
	EXPECT_EQ(a.begin()++, a.begin());
}
TEST(insert_element, 100_elements)
{
	std::string my_str = "node   ";
	Trie <int> a;
	for (size_t i = 0; i < 100; ++i) {
		a.insert(my_str.replace(5, 3, std::to_string(i)), i);
	}
	EXPECT_EQ(a.size(), 100);
}
TEST(erase, 100_elements)
{
	std::string my_str = "node   ";
	Trie <int> a;
	for (size_t i = 0; i < 100; ++i) {
		a.insert(my_str.replace(5, 3, std::to_string(i)), i);
	}
	EXPECT_EQ(a.size(), 100);
	for (size_t i = 0; i < 100; ++i) {
		a.erase(my_str.replace(5, 3, std::to_string(i)));
	}
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(erase, 40_elements_node)
{
	std::string my_str = "node   ";
	Trie <int> a;
	for (size_t i = 0; i < 40; ++i) {
		a.insert(my_str.replace(5, 3, std::to_string(i)), i);
	}
	EXPECT_EQ(a.size(), 40);
	for (size_t i = 0; i < 40; ++i) {
		a.erase(my_str.replace(5, 3, std::to_string(i)));
	}
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}

TEST(find_element, 100_elements) {
	std::string my_str = "node   ";
	Trie <int> a;
	for (size_t i = 0; i < 100; ++i) {
		a.insert(my_str.replace(5, 3, std::to_string(i)), i);
	}
	EXPECT_EQ(a.size(), 100);
	size_t counter = 0;
	for (size_t i = 0; i < 100; ++i) {
		if (i == a[my_str.replace(5, 3, std::to_string(i))])
			++counter;
	}
	EXPECT_EQ(counter, 100);
}

TEST(find_iterator, 100_elements)
{
	std::string my_str = "node  ";
	Trie <int> a;
	for (size_t i = 0; i < 100; ++i) {
		a.insert(my_str.replace(5, 3, std::to_string(i)), i);
	}
	EXPECT_EQ(a.size(), 100);
	size_t counter = 0;
	for (size_t i = 0; i < 100; ++i) {
		auto& [key, value] = *a.find(my_str.replace(5, 3, std::to_string(i)));
		if (key == my_str.replace(5, 3, std::to_string(i)) && value == i)
			++counter;
	}
	EXPECT_EQ(counter, 100);
}
TEST(insert_iterator, empty_vector) {
	Trie <int> a;
	std::vector<std::pair<std::string, int>> b;
	a.insert(b.begin(), b.end());
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(insert_iterator, vector) {
	Trie <int> a;
	std::string my_str = "dfkjohitj";
	std::vector<std::pair<std::string, int>> b;
	for (size_t i = 0; i < my_str.size(); ++i) {
		b.push_back(std::make_pair(my_str.substr(i), i));
	}
	a.insert(b.begin(), b.end());
	EXPECT_EQ(a.size(), b.size());
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		auto value = a[my_str.substr(i)];
		if (value == b[i].second)
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(cnstr_input_iter, empty_vector) {
	std::vector<std::pair<std::string, int>> b;
	Trie <int> a(b.begin(), b.end());
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}

TEST(cnstr_input_iter, vector) {
	std::string my_str = "dfkjohitj";
	std::vector<std::pair<std::string, int>> b;
	for (size_t i = 0; i < my_str.size(); ++i) {
		b.push_back(std::make_pair(my_str.substr(i), i));
	}
	Trie <int> a(b.begin(), b.end());
	EXPECT_EQ(a.size(), b.size());
	size_t counter = 0;
	for (size_t i = 0; i < my_str.size(); ++i) {
		auto value = a[my_str.substr(i)];
		if (value == b[i].second)
			++counter;
	}
	EXPECT_EQ(counter, my_str.size());
}
TEST(erase_two_iterator, empty_trie) {
	Trie<int> a;
	a.erase(a.begin(), a.end());
	EXPECT_TRUE(a.empty());
}
TEST(erase_two_iterator, 10_element_trie) {

	std::string my_str = "hgtyruejnf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), 10);
	a.erase(a.begin(), a.end());
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
}
TEST(erase_two_iterator, 10_element_trie_3_7) {

	std::string my_str = "hgtyruejnf";
	Trie <int> a;
	for (size_t i = 0; i < my_str.size(); ++i) {
		a.insert(my_str.substr(i), i);
	}
	EXPECT_EQ(a.size(), 10);
	auto first = a.begin(), last = a.begin();
	for (size_t i = 0; i < 3; ++i) {
		++first;
	}
	for (size_t i = 0; i < 7; ++i) {
		++last;
	}
	a.erase(first, last);
	EXPECT_EQ(a.size(), 6);
}
TEST(Trie, create) {
	Trie<int> k;
	EXPECT_EQ(k.size(), 0);
	EXPECT_TRUE(k.empty());
}

TEST(Trie, insert_one)
{
	Trie<int> k;
	k.insert("lol", 4);
	EXPECT_EQ(k.size(), 1);
}
TEST(Trie, insert_100)
{
	Trie<int> k;
	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	EXPECT_EQ(k.size(), 100);
}
TEST(erase, insert_10)
{
	Trie<int> k;
	std::string s("a");
	for (int i = 0; i < 10; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	EXPECT_EQ(k.size(), 10);
	for (size_t i = 0; i < 11; i++)
	{
		k.erase(s);
		--s[0];
	}
	EXPECT_EQ(k.size(), 0);
}
TEST(Trie, operator_sq_bracket_correct_one)
{
	Trie<int> k;
	k.insert("lol", 4);
	EXPECT_EQ(k["lol"], 4);
}
TEST(Trie, operator_sq_bracket_correct_100)
{
	Trie<int> k;
	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	s = "a";
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(k[s], i);
		s[0]++;
	}
	EXPECT_EQ(k.size(), 100);
}

TEST(Trie, operator_sq_bracket_ins_correct_100)
{
	Trie<int> k;
	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k[s] = i;
		s[0]++;
	}
	s = "a";
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(k[s], i);
		s[0]++;
	}
	EXPECT_EQ(k.size(), 100);
}

TEST(Trie, operator_sq_bracket_change_one)
{
	Trie<int> k;
	k.insert("lol", 4);
	k["lol"] = 13;
	EXPECT_EQ(k["lol"], 13);
	EXPECT_EQ(k.size(), 1);
}

TEST(Trie, find_one)
{
	Trie<int> k;
	k.insert("lol", 4);
	auto it = k.find("lol");
	EXPECT_EQ((*it).second, 4);
	EXPECT_EQ(k.size(), 1);
}

TEST(Trie, find_100)
{
	Trie<int> k;
	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	s = "a";
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ((*k.find(s)).second, i);
		s[0]++;
	}
	EXPECT_EQ(k.size(), 100);
}

TEST(Trie, insert_erase_1)
{
	Trie<int> k;
	k.insert("l", 4);
	k.erase("l");
	EXPECT_EQ(k.empty(), true);
}

TEST(Trie, insert_erase_erase)
{
	Trie<int> k;
	k.insert("l", 4);
	k.erase("l");
	EXPECT_EQ(k.erase("l"), 0);
}

TEST(Trie, insert_erase_100)
{
	Trie<int> k;
	std::string s("a");
	std::string s1("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	for (int i = 0; i < 100; ++i) {
		k.erase(s1);
		s1[0]++;
	}
	EXPECT_TRUE(k.empty());
}
TEST(Trie_iterator, begin_empty)
{
	Trie<int> k;
	k.begin();
	k.end();
	EXPECT_EQ(k.empty(), true);
}
TEST(Trie, begin_one)
{
	Trie<int> k;
	k.insert("dd", 4);
	k.insert("d", 4);
	auto d = k.begin();
	++d;
	k.end();
	EXPECT_EQ(!k.empty(), true);
}

TEST(Trie, insert_100_assign)
{
	Trie<int> k;

	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	s = "a";
	Trie<int> k1 = k;
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(k[s], k1[s]);
		s[0]++;
	}
	EXPECT_EQ(k.size(), k1.size());
}

TEST(Trie_iterator, insert_100_assign_iterate_check)
{
	Trie<int> k;

	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	EXPECT_EQ(100, k.size());
	Trie<int> k1 = k;
	auto it = k.begin();
	auto amount = 0;
	for (const auto& it1 : k1) {
		EXPECT_EQ(it1.first, (*it).first);
		++it;
		++amount;
	}
	EXPECT_EQ(k.size(), k1.size());
	EXPECT_EQ(k.size(), amount);
}
TEST(iterator, 10_assign_iterate_check)
{
	Trie<int> k;

	std::string s("avflb");
	for (int i = 0; i < 10; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	EXPECT_EQ(10, k.size());
	Trie<int> k1 = k;
	auto it = k.begin();
	auto amount = 0;
	for (const auto& it1 : k1) {
		EXPECT_EQ(it1.first, (*it).first);
		++it;
		++amount;
	}
	EXPECT_EQ(k.size(), k1.size());
	EXPECT_EQ(k.size(), amount);
}
TEST(Trie_iterator, insert_10_iterate)
{
	Trie<int> k;

	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 10; ++i) {
		k.insert(keys[i], i);
	}
	auto amount = 0;
	for (auto it : k)
	{
		++amount;
	}
	EXPECT_EQ(amount, 10);
}
TEST(Trie_const_iterator, insert_10_iterate)
{
	Trie<int> k;

	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 10; ++i) {
		k.insert(keys[i], i);
	}
	auto amount = 0;
	for (auto it = k.cbegin(); it!=k.cend();++it)
	{
		++amount;
	}
	EXPECT_EQ(amount, 10);
}

TEST(Trie_iterator, operator_ptr)
{
	Trie<int> k;

	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 10; ++i) {
		k.insert(keys[i], i);
	}
	auto amount = 9;
	for (auto& i = k.begin(); i != k.end(); ++i)
	{
		(*i).second = ++amount;
	}
	amount = 9;
	for (auto& i = k.begin(); i != k.end(); ++i)
	{
		EXPECT_EQ((*i).second, ++amount);
	}
}

TEST(Trie, insert_100_copy_constr)
{
	Trie<int> k;

	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	--s[0];
	Trie<int> k1(k);
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(k[s], k1[s]);
		--s[0];
	}
	EXPECT_EQ(k.size(), k1.size());

}
TEST(Trie, insert_5_copy_constr)
{
	Trie<int> k;

	std::string s("a");
	for (int i = 0; i < 5; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	Trie<int> k1(k);
	--s[0];
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(k[s], k1[s]);
		--s[0];
	}
	EXPECT_EQ(k.size(), k1.size());

}
TEST(find_element, 5_element_alien_find)
{
	Trie<int> k;

	std::string s("a");
	for (int i = 0; i < 5; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	EXPECT_EQ(k[s], int());


}
TEST(Trie, insert_100_string_assign)
{
	Trie<std::string> k;

	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, s);
		s[0]++;
	}
	Trie<std::string> k1 = k;
	--s[0];
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(k[s], k1[s]);
		--s[0];
	}
	EXPECT_EQ(k.size(), k1.size());
}

TEST(Trie, back_to_back_clear_one_)
{
	Trie<int> k;
	k.insert("lol", 4);
	k.clear();
	EXPECT_EQ(k.size(), 0);
	k.insert("lol", 4);
	EXPECT_EQ(k.size(), 1);
	EXPECT_TRUE(k.find("lol") != k.end());
	k.clear();
	EXPECT_EQ(k.size(), 0);
	EXPECT_EQ(k.find("lol"), k.end());
}

TEST(Trie, clear_100)
{
	Trie<int> k;

	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, i);
		s[0]++;
	}
	k.clear();
	for (int i = 0; i < 100; ++i) {
		EXPECT_TRUE(k.find(s) == k.end());
		s[0]++;
	}
	EXPECT_EQ(k.size(), 0);
}

TEST(Trie, insert_erase_it_one)
{
	Trie<int> k;
	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 1; ++i) {
		k.insert(keys[i], i);
	}
	for (auto it : k)
	{
		k.erase(k.begin());
	}
	EXPECT_EQ(k.empty(), true);
}

TEST(Trie, insert_erase_it_all)
{
	Trie<int> k;
	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 10; ++i) {
		k.insert(keys[i], i);
	}
	k.erase(k.begin(), k.end());
	EXPECT_EQ(k.empty(), true);
}

TEST(Trie, insert_assign_erase_correct_it)
{
	Trie<int> k;
	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 10; ++i) {
		k.insert(keys[i], i);
	}
	auto k1 = k;
	k.erase(k1.begin(), k1.end());
	EXPECT_EQ(k.empty(), true);
}

TEST(Trie_vector, create) {
	Trie < std::vector < int>> k;
	EXPECT_EQ(k.size(), 0);
	EXPECT_TRUE(k.empty());
}

TEST(Trie_vector, insert_one)
{
	Trie < std::vector < int>> k;
	k.insert("lol", std::vector<int>(4, 4));
	EXPECT_EQ(k.size(), 1);
}
TEST(Trie_vector, insert_100)
{
	Trie < std::vector < int>> k;
	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, std::vector<int>(i + 1, i + 1));
		s[0]++;
	}
	EXPECT_EQ(k.size(), 100);
}

TEST(Trie_vector, operator_sq_bracket_correct_one)
{
	Trie < std::vector < int>> k;
	k.insert("lol", std::vector<int>(1, 1));
	EXPECT_EQ(k["lol"].size(), 1);
}

TEST(Trie_vector, operator_const_sq_bracket_correct_one)
{
	Trie < std::vector < int>> k;
	k.insert("lol", std::vector<int>(1, 1));
	const auto k1(k);
	EXPECT_ANY_THROW(k1["f"] == k["f"]);
	EXPECT_TRUE(k1["lol"] == k["lol"]);
	EXPECT_TRUE(k1.size()+1 == k.size());
}

TEST(Trie_vector, operator_sq_bracket_correct_100)
{
	Trie < std::vector < int>> k;
	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, std::vector<int>(i + 1, i + 1));
		s[0]++;
	}
	s = "a";
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(k[s].size(), std::vector<int>(i + 1, i + 1).size());
		s[0]++;
	}
	EXPECT_EQ(k.size(), 100);
}
TEST(Trie_vector, operator_const_sq_bracket_correct_100)
{
	Trie < std::vector < int>> k;
	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, std::vector<int>(i + 1, i + 1));
		s[0]++;
	}
	s = "a";
	const auto k1(k);
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(k1[s].size(), std::vector<int>(i + 1, i + 1).size());
		s[0]++;
	}
	EXPECT_EQ(k1.size(), 100);
}

TEST(Trie_vector, operator_sq_bracket_change_one)
{
	Trie < std::vector < int>> k;
	k.insert("lol", std::vector<int>(1, 1));
	k["lol"] = std::vector<int>(2, 2);
	EXPECT_EQ(k["lol"].size(), std::vector<int>(2, 2).size());
	EXPECT_EQ(k.size(), 1);
}

TEST(Trie_vector, find_one)
{
	Trie < std::vector < int>> k;
	k.insert("lol", std::vector<int>(1, 1));
	auto it = k.find("lol");
	EXPECT_EQ((*it).second.size(), 1);
	EXPECT_EQ(k.size(), 1);
}

TEST(Trie_vector, const_find_one)
{
	Trie < std::vector < int>> k;
	k.insert("lol", std::vector<int>(1, 1));
	const auto k1(k);
	auto it = k1.find("lol");
 	EXPECT_EQ((*it).second.size(), 1);
	EXPECT_EQ(k1.size(), 1);
}


TEST(Trie_vector, find_100)
{
	Trie < std::vector < int>> k;
	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, std::vector<int>(i + 1, i + 1));
		s[0]++;
	}
	s = "a";
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ((*k.find(s)).second.size(), std::vector<int>(i + 1, i + 1).size());
		s[0]++;
	}
	EXPECT_EQ(k.size(), 100);
}

TEST(Trie_vector, insert_erase_1)
{
	Trie < std::vector < int>> k;
	k.insert("l", std::vector<int>(1, 1));
	k.erase("l");
	EXPECT_EQ(k.empty(), true);
}

TEST(Trie_vector, insert_erase_erase)
{
	Trie < std::vector < int>> k;
	std::string str = "l";
	k.insert(str, std::vector<int>(1, 1));
	k.erase(str);
	EXPECT_EQ(k.erase(str), 0);
}

TEST(Trie_vector, insert_erase_100)
{
	Trie < std::vector < int>> k;
	std::string s("a");
	std::string s1("a");
	for (int

		i = 0; i < 100; ++i) {
		k.insert(s, std::vector<int>(i + 1, i + 1));
		s[0]++;
	}
	for (int i = 0; i < 100; ++i) {
		k.erase(s1);
		s1[0]++;
	}
	EXPECT_TRUE(k.empty());
}
TEST(Trie_vector, begin_empty)
{
	Trie < std::vector < int>> k;
	k.begin();
	k.end();
	EXPECT_EQ(k.empty(), true);
}
TEST(Trie_vector, begin_one)
{
	Trie < std::vector < int>> k;
	k.insert("dd", std::vector<int>(2, 2));
	k.insert("d", std::vector<int>(1, 1));
	auto d = k.begin();
	++d;
	k.end();
	EXPECT_EQ(!k.empty(), true);
}

TEST(Trie_vector, insert_100_assign)
{
	Trie < std::vector < int>> k;

	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, std::vector<int>(i + 1, i + 1));
		s[0]++;
	}
	s = "a";
	Trie < std::vector < int>> k1 = k;
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(k[s].size(), k1[s].size());
		s[0]++;
	}
	EXPECT_EQ(k.size(), k1.size());
}

TEST(Trie_vector, insert_100_assign_iterate_check)
{
	Trie < std::vector < int>> k;

	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, std::vector<int>(i + 1, i + 1));
		s[0]++;
	}
	Trie < std::vector < int>> k1 = k;
	auto it = k.begin();
	auto amount = 0;
	for (const auto& it1 : k1) {
		EXPECT_EQ(it1.first, (*it).first);
		++it;
		++amount;
	}
	EXPECT_EQ(k.size(), k1.size());
	EXPECT_EQ(k.size(), amount);
}

TEST(Trie_vector, insert_10_iterate)
{
	Trie < std::vector < int>> k;

	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 10; ++i) {
		k.insert(keys[i], std::vector<int>(i + 1, i + 1));
	}
	auto amount = 0;
	for (auto it : k)
	{
		++amount;
	}
	EXPECT_EQ(amount, 10);
}

TEST(Trie_vector, insert_10_ierase_const_sq_bracket)
{
	Trie < std::vector < int>> k;

	std::vector<std::string> keys{ "key1","key2","key3","key4" };
	for (int i = 0; i < 4; ++i) {
		k.insert(keys[i], std::vector<int>(i + 1, i + 1));
	}
	for (auto it : keys)
	{
		k.erase(it);
		const auto k1(k);
		EXPECT_ANY_THROW(k1[it]);
	}
}

TEST(Trie_vector, operator_ptr)
{
	Trie < std::vector < int>> k;

	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 10; ++i) {
		k.insert(keys[i], std::vector<int>(i + 1, i + 1));
	}
	for (auto& i = k.begin(); i != k.end(); ++i)
	{
		(*i).second = std::vector<int>(5, 5);
	}
	for (auto& i = k.begin(); i != k.end(); ++i)
	{
		EXPECT_EQ((*i).second.size(), 5);
	}
}

TEST(Trie_vector, insert_100_copy_constr)
{
	Trie < std::vector < int>> k;

	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, std::vector<int>(i + 1, i + 1));
		s[0]++;
	}
	Trie < std::vector < int>> k1(k);
	--s[0];
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(k[s].size(), k1[s].size());
		--s[0];
	}
	EXPECT_EQ(k.size(), k1.size());
}

TEST(Trie_vector, back_to_back_clear_one_)
{
	Trie < std::vector < int>> k;
	k.insert("lol", std::vector<int>(1, 1));
	k.clear();
	EXPECT_EQ(k.size(), 0);
	k.insert("lol", std::vector<int>(1, 1));
	EXPECT_EQ(k.size(), 1);
	EXPECT_TRUE(k.find("lol") != k.end());
	k.clear();
	EXPECT_EQ(k.size(), 0);
	EXPECT_EQ(k.find("lol"), k.end());
}

TEST(Trie_vector, clear_100)
{
	Trie < std::vector < int>> k;

	std::string s("a");
	for (int i = 0; i < 100; ++i) {
		k.insert(s, std::vector<int>(i + 1, i + 1));
		s[0]++;
	}
	k.clear();
	for (int i = 0; i < 100; ++i) {
		EXPECT_TRUE(k.find(s) == k.end());
		s[0]++;
	}
	EXPECT_EQ(k.size(), 0);
}

TEST(Trie_vector, insert_erase_it_one)
{
	Trie < std::vector < int>> k;
	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 1; ++i) {
		k.insert(keys[i], std::vector<int>(i + 1, i + 1));
	}
	for (auto it : k)
	{
		k.erase(k.begin());
	}
	EXPECT_EQ(k.empty(), true);
}

TEST(Trie_vector, insert_erase_it_all)
{
	Trie < std::vector < int>> k;
	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 10; ++i) {
		k.insert(keys[i], std::vector<int>(i + 1, i + 1));
	}
	k.erase(k.begin(), k.end());
	EXPECT_EQ(k.empty(), true);
}

TEST(Trie_vector, insert_sqIns_erase)
{
	Trie < std::vector < int>> k;
	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 5; ++i) {
		k.insert(keys[i], std::vector<int>(i + 1, i + 1));
	}
	for (int i = 5; i < 10; ++i) {
		k[keys[i]] = std::vector<int>(i + 1, i + 1);
	}
	EXPECT_EQ(k.size(), keys.size());
	k.erase(k.begin(), k.end());
	EXPECT_EQ(k.empty(), true);
}

TEST(Trie_vector, insert_sqIns_check)
{
	Trie < std::vector < int>> k;
	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 5; ++i) {
		k.insert(keys[i], std::vector<int>(i + 1, i + 1));
	}
	for (int i = 5; i < 10; ++i) {
		k[keys[i]] = std::vector<int>(i + 1, i + 1);
	}
	for(int i = 0; i < 10; ++i)
	{
		EXPECT_EQ(k[keys[i]].size(), i + 1);
	}
}

TEST(Trie_vector, insert_assign_erase_correct_it)
{
	Trie < std::vector < int>> k;
	std::vector<std::string> keys{

	"key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 10; ++i) {
		k.insert(keys[i], std::vector<int>(i + 1, i + 1));
	}
	auto k1 = k;
	k.erase(k1.begin(), k1.end());
	EXPECT_EQ(k.empty(), true);
}

TEST(Trie, swap_5)
{
	Trie<int> k;
	Trie<int> k1;

	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 4; ++i) {
		k.insert(keys[i], i);
	}
	for (int i = 0; i < 5; ++i) {
		k1.insert(keys[i + 5], i + 5);
	}
	auto amount = 0;
	auto amount1 = 0;
	k1.swap(k);
	for (auto it : k)
	{
		++amount;
	}
	for (auto it : k1)
	{
		++amount1;
	}
	EXPECT_EQ(amount, 5);
	EXPECT_EQ(amount1, 4);
}

TEST(Trie_vector, swap_5)
{
	Trie < std::vector < int>> k;
	Trie < std::vector < int>> k1;

	std::vector<std::string> keys{ "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
	for (int i = 0; i < 4; ++i) {
		k.insert(keys[i], std::vector<int>(i + 1, i + 1));
	}
	for (int i = 0; i < 5; ++i) {
		k1.insert(keys[i + 5], std::vector<int>(5 + i, i + 5));
	}
	auto amount = 0;
	auto amount1 = 0;
	k1.swap(k);
	for (auto it : k)
	{
		amount += it.second.size();
	}
	for (auto it : k1)
	{
		amount1 += it.second.size();
	}
	EXPECT_EQ(amount, 35);
	EXPECT_EQ(amount1, 10);
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