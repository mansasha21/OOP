#pragma once
#include <string>
#include <map>
#include <istream>
#include <set>
class FriendsGraph final {
public:
	FriendsGraph() = default;
	~FriendsGraph() = default;
	std::map<std::string, double> possibleFriends(const std::string& id)const;
	void fillGraphData(std::istream& src);
	void add(const std::string& id1, const std::string& id2);
	void add(const std::string& id, const std::set<std::string>& friends);
	void erase(const std::string& id);
	std::set<std::string> getfriends(const std::string& id)const;
	bool empty() const;

private:
	std::map<std::string, std::set<std::string>> adjList;
};