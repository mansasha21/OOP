#include "SpanningTree.hpp"
#include <math.h>
#include <algorithm>
using namespace std ;
namespace {
	using SpanningTree::point_t;
	using SpanningTree::edge_t;
	float length(const point_t& a, const point_t& b) {
		return sqrt(fabs(pow(a.first - b.first, 2) + pow(a.second - b.second, 2)));
	}

	void make_set(vector<size_t>&parent, vector<size_t>&rank) {
		for (size_t i = 1; i < parent.size() + 1; i++) {
			parent[i - 1] = i;
		}
		fill(rank.begin(), rank.end(), 0);
	}

	size_t find(vector<size_t>& parent, size_t i) {
		if (parent[i - 1] != i)
			parent[i - 1] = find(parent, parent[i - 1]);
		return parent[i - 1];
	}

	bool union_sets(vector<size_t>& parent, vector<size_t>& rank, size_t i, size_t j) {
		size_t i_id = find(parent, i);
		size_t j_id = find(parent, j);
		if (i_id == j_id)
			return false;
		if (rank[i_id - 1] > rank[j_id - 1])
			parent[j_id - 1] = i_id;
		else {
			parent[i_id - 1] = parent[j_id - 1];
			if (rank[j_id - 1] == rank[i_id - 1])
				rank[j_id - 1]++;
		}
		return true;

	}

	bool cmp(const edge_t& a, const edge_t& b) {
		return a.second < b.second;
	}

}
namespace SpanningTree {

	vector<edge_t> build(const vector<point_t> & points) {
		vector<size_t> parent(points.size());
		vector<size_t> rank(points.size());
		make_set(parent, rank);
		vector<edge_t> edges = makeEdges(points);
		vector<edge_t> tree;
		sort(edges.begin(), edges.end(),cmp);
		for (const auto& i : edges) {
			if (tree.size() == points.size() - 1)
				break;
			if (union_sets(parent, rank, i.first.first, i.first.second))
				tree.push_back(i);
		}
		return tree;
	}

	vector<point_t> getPoints(istream& stream) {
		vector<point_t> points;
		point_t point;
		int id;
		while (stream >>id>> point.first >> point.second) {
			points.push_back(point);
		}
		return points;
	}

	vector<edge_t> makeEdges(const vector<point_t>& points) {
		vector<edge_t> edges;
		edge_t edge;
		for (size_t i = 0; i < points.size(); i++) {
			for (size_t j = i; j < points.size() ; j++) {
				if (i == j)
					continue;
				edge.first.first = i+1;
				edge.first.second = j+1;
				edge.second = length(points[i], points[j]);
				edges.push_back(edge);
			}
		}
		return edges;
	}
}