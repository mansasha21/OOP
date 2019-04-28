#include "Graph.hpp"
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

void FriendsGraph::fillGraphData(istream& src) {
	string id1, id2;
	while (src >> id1 >> id2) {
		if (id1.empty() || id2.empty())
			break;
		add(id1, id2);
	}
}

 map<string, double>  FriendsGraph::possibleFriends(const std::string& id) const {
	map<string, double> posFriends;
	auto user = adjList.find(id);
	if (adjList.empty() || user == adjList.end())
		return posFriends;
	set <string> sameFriends;
	auto uFriendlistBegin = (*user).second.begin();
	auto uFriendlistEnd = (*user).second.end();
	for (const auto &i : (*user).second) {
		vector<string> difference;
		difference.reserve(adjList.size());
		auto friendListBegin = (*(adjList.find(i))).second.begin();
		auto friendListEnd = (*(adjList.find(i))).second.end();
		set_difference(friendListBegin, friendListEnd, uFriendlistBegin, uFriendlistEnd, back_inserter(difference));
		copy_n(difference.begin(), difference.size(), inserter(sameFriends, sameFriends.begin()));
	}
	for (auto& uid : sameFriends) {
		vector<string> intersec;
		size_t userFriendsSz = (*user).second.size();
		intersec.reserve(userFriendsSz);
		auto friendListBegin = (*(adjList.find(uid))).second.begin();
		auto friendListEnd = (*(adjList.find(uid))).second.end();
		set_intersection(friendListBegin, friendListEnd, uFriendlistBegin, uFriendlistEnd, back_inserter(intersec));
		double chance = static_cast<double>(intersec.size()) / static_cast<double>(userFriendsSz);
		posFriends[uid] = chance;
	}
	posFriends.erase(id);
	return  posFriends;
}

void FriendsGraph::add(const string& id1, const string& id2) {
	if (id1.empty() || id2.empty())
		return;
	adjList[id1].insert(id2);
	adjList[id2].insert(id1);
}

void FriendsGraph::add(const string& id, const set<string>& friends) {
	if (id.empty() || friends.empty())
		return;
	for (const auto& i : friends)
		add(id, i);
}

void FriendsGraph::erase(const string& id) {
	for (auto& [uid,friends] : adjList)
		friends.erase(id);
	adjList.erase(id);
}

 set<string> FriendsGraph::getfriends(const string& id)const {
	set<string> friends;
	auto i = adjList.find(id);
	if (i == adjList.end())
		return friends;
	return (*i).second;
}

bool FriendsGraph::empty()const {
	return adjList.empty();
}
