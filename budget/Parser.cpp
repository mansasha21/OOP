#include "Parser.hpp"
#include <sstream>
#include <iterator>
using namespace std;

namespace {
	list<string> partition(string s) {
		list<string> path;
		do {
			size_t ind = s.find(':');
			path.push_back(s.substr(0, ind));
			if (ind == s.npos)
				break;
			s = s.substr(ind + 1);
		} while (true);
		return path;
	}
}
spending_parser::spending_parser(istream& str):str(str){}
expectation_parser::expectation_parser(istream& str):str(str){}

tuple<Date, list<string>, double> spending_parser::parse() {
	Date date;
	string s;
	double d;
	char ch;
	str >> date.day >> ch >> date.month >> ch >> date.year>>s>>d;
	list<string> path=partition(s);
	return { date,path,d };
}

list<expectation> expectation_parser::parse() {
	list<expectation> expects;
	while (true) {
		expectation expect;
		string s;
		double value;
		while (true) {
			str >> s;
			if (s.empty())
				break;
			if (s.find(':') != s.npos) {
				expect.paths.push_back(partition(s));
			}
			else if (s.find('+') != s.npos) {
				str >> s;
				expect.paths.push_back(partition(s));
			}
			else if (!(stringstream(s) >> value)) {
				expect.paths.push_back(partition(s));
			}
			else {
				expect.value = value;
				break;
			}
		}
		if (expect.paths.empty()) {
			break;
		}
		expects.push_back(expect);
	}
	return expects;
}