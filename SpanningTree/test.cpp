#include "gtest/gtest.h"
#include "../Spanning tree/SpanningTree.hpp"
#include "gtest/gtest-memleak.h"
using namespace::std;
#include <fstream>
#include <random> // для std::random_device и std::mt19937

TEST(SimpleTest, stringstream_) {
	ifstream input("input.txt");
	ostringstream output;
	vector <SpanningTree::point_t> points;
	points = SpanningTree::getPoints(input);
	vector<SpanningTree::edge_t> res;
	res = SpanningTree::build(points);
	for (auto i : res) {
		output << i.first.first << "->" << i.first.second << endl;
	}
	EXPECT_EQ(res[0].first.first, 3);
	EXPECT_EQ(res[0].first.second, 4);
	EXPECT_EQ(res[1].first.second, 3);
	EXPECT_EQ(res[1].first.first, 2);
	EXPECT_EQ(res[2].first.second, 2);
	EXPECT_EQ(res[2].first.first, 1);
}
TEST(thousandPoints, thousand) {
	random_device rd;
	mt19937 mersenne(rd());
	vector <SpanningTree::point_t> points;
	SpanningTree::point_t point;
	for (int i = 0; i < 1000; i++) {
		point.first = mersenne() % 1000;
		point.second = mersenne() % 1000;
		points.push_back(point);
	}
	vector<SpanningTree::edge_t> res;
	res = SpanningTree::build(points);
	EXPECT_TRUE(res.size()==999);
}
TEST(fiveThousandPoints, five) {
	random_device rd;
	mt19937 mersenne(rd());
	vector <SpanningTree::point_t> points;
	SpanningTree::point_t point;
	for (int i = 0; i < 5000; i++) {
		point.first = mersenne() % 5;
		point.second = mersenne() % 5;
		points.push_back(point);
	}
	vector<SpanningTree::edge_t> res;
	res = SpanningTree::build(points);
	EXPECT_TRUE(res.size() == 4999);
}
TEST(eightThousandPoints, eight) {
	random_device rd;
	mt19937 mersenne(rd());
	vector <SpanningTree::point_t> points;
	SpanningTree::point_t point;
	for (int i = 0; i < 8000; i++) {
		point.first = mersenne() % 8;
		point.second = mersenne() % 8;
		points.push_back(point);
	}
	vector<SpanningTree::edge_t> res;
	res = SpanningTree::build(points);
	ofstream output("output.txt");
	EXPECT_TRUE(res.size() == 7999);
}
TEST(SimpleTest, empty) {
	ifstream input("input.txt");
	vector <SpanningTree::point_t> points;
	vector<SpanningTree::edge_t> res;
	res = SpanningTree::build(points);
	EXPECT_TRUE(res.size()==0);
}
TEST(Point, one) {
	random_device rd;
	mt19937 mersenne(rd());
	vector <SpanningTree::point_t> points;
	SpanningTree::point_t point;
	point.first = mersenne()%100;
	point.second = mersenne()%100;
	points.push_back(point);
	vector<SpanningTree::edge_t> res;
	res = SpanningTree::build(points);
	EXPECT_TRUE(res.size() == 0);
}
