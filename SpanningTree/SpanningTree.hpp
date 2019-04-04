#pragma once
#include <vector>
#include <iostream>
namespace SpanningTree {
	using point_t = std::pair<int, int>;
	//typedef std::pair<int, int> point_t;
	typedef std::pair <std::pair<size_t, size_t>, float> edge_t;

	std::vector<edge_t> build(const std::vector<point_t>& points);
	std::vector<point_t> getPoints(std::istream& stream);
	std::vector<edge_t> makeEdges(const std::vector<point_t>& points);
}