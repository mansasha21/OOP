#pragma once
#include <string>
#include <vector>
#include <set>
namespace WordFind  {
	typedef struct {
		char sym;
		bool end;
		int next[256];
	}node;
	class Trie final {
	public:
		Trie();
		void add(const std::string& s);
		std::set<std::string> findWords(const std::string& word)const;
		void add(std::istream& stream);
	private:
		void findWords(const std::string& word, bool used[], std::set<std::string>& words,
					   const std::string& subword = "", size_t num = 0) const;
		node make_node(char c) const;
	private:
		std::vector <node> trie;
	};
}