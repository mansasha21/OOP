#include "Budget.hpp"
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

namespace {
	const string OTHER("Other");
	const string HEAD("category root");
}

bool Date::operator<(const Date& a)const {
	return year * days_year + month * days_month + day < a.year*days_year + a.month * days_month + a.day;
}

ostream& operator<<(ostream& str, const product& prod) {
	int ind = 1;
	for (const auto& i : prod.paths) {
		string back = i.back();
		for (const auto& j : i) {
			str << j;
			if (j != back)
				str << ':';
		}
		if (ind < prod.paths.size())
			str << '\t' << '+' << '\t';
		ind++;
	}
	str << '\t' << prod.expect_cost << '\t' << prod.real_cost << '\t';
	if (prod.expect_cost != 0)
		str << prod.real_cost * 100 / prod.expect_cost << '%';
	str << endl;
	return str;
}

Category::Category(const string& name) :name(name){}
Category::Category():name(""){}

void Category::add(const Date& date, list<string> path, double cost) {
	string product = path.front();
	if(subCategory.find(product)==subCategory.end()){
		subCategory[product]=Category(product);
	}
	subCategory[product].fill(date,cost);
	path.pop_front();
	if(!path.empty())
		subCategory[product].add(date, std::move(path), cost);
}

void Category::fill(const Date& date, double spend){
	auto it = spending.find(date);
	if (it == spending.end())
		spending.insert({ date,spend });
	else
		(*it).second += spend;
}
map<Date, double> Category::get_spending(list<string> path)const {
	if (path.empty())
		return spending;
	map<Date, double> empty;
	string first = path.front();
	auto subcat = subCategory.find(first);
	if (subcat == subCategory.end()) {
		return empty;
	}
	path.pop_front();
   return (*subcat).second.get_spending(path);
}
Budget::Budget():spendings(HEAD),total_sum(0.0){}


void Budget::add_spending(const Date& date, std::list<string> path, double spend) {
	spendings.add(date, path, spend);
	spendings.fill(date, spend);
	total_sum += spend;
}


list<product>Budget::calculate(const Date& from, const Date& to, const list<expectation>& expect)const {
	using namespace std::rel_ops;
	list<product> res;
	double total_expected = 0.0;
	for (const auto& i : expect) {
		double sum = 0;
		product prod;
		for (const auto& j : i.paths) {
			auto spends = spendings.get_spending(j);
			for (const auto&[date,cost] :spends) {
				if (date >= from && date <= to)
					sum += cost;
			}
			prod.paths.push_back(j);
		}
		total_expected += sum;
		prod.expect_cost = i.value;
		prod.real_cost = sum;
		res.push_back(prod);
	}
	product prod;
	list<string> k = { OTHER };
	prod.paths.push_back(k);
	prod.expect_cost = 0.0;
	prod.real_cost = total_sum - total_expected;
	res.push_back(prod);
	return res;
}


