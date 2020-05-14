#pragma once
#include <fstream>
#include "List_template_class.h"
class Bellman_Ford_algorithm
{
private:
	int amount_of_cities, amount_of_edges;
	List_template_class<List<char>> city;
	struct edge {
		int vertex1, vertex2, cost;
	};
	List<edge> edges;
	void swap(int&, int&);
	const int INF = 1000000000;
public:
	Bellman_Ford_algorithm();
	~Bellman_Ford_algorithm();
	void set_data();
	void set_data(string);
	void find_path(size_t, size_t);
	List<int> return_path(size_t, size_t);
};