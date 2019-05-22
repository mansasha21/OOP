#pragma once
#include <istream>
#include "Budget.hpp"

class spending_parser final{
public:
	spending_parser(std::istream &str);
	~spending_parser() = default;
	std::tuple<Date, std::list<std::string>, double> parse();

private:
	std::istream &str;
};
class expectation_parser final {
public:
	expectation_parser(std::istream &str);
	~expectation_parser() = default;
	std::list<expectation> parse();

private:
	std::istream &str;
};