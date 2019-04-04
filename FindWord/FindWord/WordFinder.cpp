#include "WordFinder.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace {
	set <string> foundwords;
}
namespace WordFind {
	Trie::Trie() {
		trie.push_back(make_node('$'));
	}
	void Trie::add(const string& s) {
		if (s.empty()) return;
		int num = 0;
		for (size_t i = 0; i < s.size(); i++) {
			size_t ch = static_cast<size_t>(s[i]);
			if (trie[num].next[ch] == -1) {
				trie.push_back(make_node(s[i]));
				trie[num].next[ch] = trie.size() - 1;
			}
			num = trie[num].next[ch];
		}
		trie[num].end = true;
	}
	node Trie::make_node(char ch)const {
		node nd;
		nd.end = false;
		nd.sym = ch;
		memset(nd.next, -1, sizeof(nd.next));
		return nd;
	}
	set<string> Trie::findWords(const string& word)const {
		set<string> words;
		findWords(word, nullptr, words);
		return words;
	}
	void Trie::findWords(const string& word, bool used[], set<string>&words, const string& subword, size_t num)const {
		bool *_used;
		if (!used) {
			_used = new bool[word.size()];
			memset(_used, 0, word.size());
		}
		else {
			_used = used;
		}
		for (size_t i = 0; i < word.size(); i++) {
			if (!_used[i]) {
				size_t _num = num;
				size_t ch = static_cast<size_t>(word[i]);
				if (trie[_num].next[ch] != -1) {
					_num = trie[_num].next[ch];
					_used[i] = true;
					findWords(word, _used, words, subword + word[i], _num);
					_used[i] = false;
				}
			}
		}
		if (trie[num].end == true) {
			words.insert(subword);
		}
		if (num == 0)
			delete[] _used;
	}
	void Trie::add(istream& stream) {
		if (!stream) {
			return;
		}
		string s;
		for (; getline(stream, s);) {
			add(s);
		}
	}
}

