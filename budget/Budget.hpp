#pragma once
#include<map>
#include <string>
#include <unordered_map>
#include <set>
#include <list>
#include <ostream>

struct expectation {
	std::list<std::list<std::string>> paths;
	double value;
};

struct product {
	std::list<std::list<std::string>> paths;
	double expect_cost;
	double real_cost;
};

std::ostream& operator<<(std::ostream& str, const product& prod);


struct Date final {
	size_t year;
	size_t month;
	size_t day;

	bool operator <(const Date& a)const;
	static const int days_year = 365;
	static const int days_month = 30;

};


class Category final{
public:
	Category();
	~Category() = default;
	Category(const std::string& name);
	void add(const Date& date, std::list<std::string> path, double cost);
	void fill(const Date& date,double spend);
	std::map<Date, double> get_spending(std::list<std::string>)const;
private:
	std::string name;
	std::map<Date, double> spending;
	std::unordered_map<std::string,Category> subCategory;
};

class Budget final {
public:
	Budget();
	~Budget() = default;
	void add_spending(const Date& date, std::list<std::string> path, double spend);
	std::list<product> calculate(const Date& from,const Date& to,const std::list<expectation>& expect)const;
private:
	Category spendings;
	double total_sum;
};