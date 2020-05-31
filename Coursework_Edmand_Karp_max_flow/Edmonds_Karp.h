#pragma once
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include "C:\Users\raifg\source\repos\Bellman_Ford\Bellman_Ford\List.h"
#include "C:\Users\raifg\source\repos\Bellman_Ford\Bellman_Ford\List_template_class.h"
#include "Queue.h"
using namespace std;

class Network
{
private:
	List<char> vertexes;
	List_template_class<List<int>> capacity;
	List_template_class<List<int>> adjacency;
	long long INF;
	
	struct pair {
		int first_vertex;
		long long second_vertex;
	};
public:
	Network();
	~Network();
	void read_file(string);
	int bfs(int, int, List<int>&);
	int max_flow();
};

	Network::Network() {
		INF = 100000;
	}

	Network::~Network() {
		capacity.clear();
		adjacency.clear();
		vertexes.clear();
	}

	// Sets graph from text file
	void Network::read_file(string name_of_file)
	{
		
		//opening file, check if it's was open
		ifstream file(name_of_file);
		
		if (!file.is_open())
		{
			throw exception("Error, file is not open!");
		}


		//variable declarations
		int index_symbol = 0; char symbol;

		//reading vertexes of graph
		do {
			index_symbol = 0;
			do {
				file >> noskipws >> symbol;
				if ((index_symbol == 0 || index_symbol == 2) && !vertexes.contains(symbol))
					vertexes.push_back(symbol);
				index_symbol++;
			} while (symbol != '\n' && !file.eof());
		} while (!file.eof());

		file.clear();

		//correct input check
		if (vertexes.at(0) != 'S' || vertexes.at(vertexes.get_size() - 1) != 'T') {
			throw invalid_argument("Error, graph must begin with “S” and end with “T”!");
		}

		file.seekg(0);

		//creating matrix of capacity with 0
		List<int> temp;
		for (size_t i = 0; i < vertexes.get_size(); i++) {
			for (size_t j = 0; j < vertexes.get_size(); j++)
				temp.push_back(0);
			capacity.push_back(temp);
			temp.nullify();
		}

		int potential_capacity = 0;
		char first_vertex_capacity, second_vertex_capacity;

		//filling matrix of capacity
		while (!file.eof())
		{
			index_symbol = 0;
			do {

				if (index_symbol != 4)
					file >> noskipws >> symbol;
				else
					file >> potential_capacity;

				if (index_symbol == 0)
					first_vertex_capacity = symbol;

				else if (index_symbol == 2)
					second_vertex_capacity = symbol;

				else if (index_symbol == 4) {
					capacity.at(vertexes.get_index((char)first_vertex_capacity)).set(vertexes.get_index((char)second_vertex_capacity), potential_capacity);
				}

				index_symbol++;
			} while (symbol != '\n' && !file.eof());
		}

		for (int i = 0; i < capacity.get_size(); i++) {
			temp.nullify();
			for (int j = 0; j < capacity.at(i).get_size(); j++) {
				temp.push_back(capacity.at(i).at(j));
			}
			adjacency.push_back(temp);
		}


		for (int i = 0; i < adjacency.get_size(); i++) {
			for (int j = i; j < adjacency.at(i).get_size(); j++) {
				adjacency.at(j).set(i, adjacency.at(i).at(j));
			}
		}

		temp.nullify();
		file.close();
	}

	//finding augmenting paths using bfs
	int Network::bfs(int source, int sink, List<int>& parent) {

		//assigns value = -1 to elements< and last to value = -2
		for (int i = 0; i < parent.get_size(); i++) {
			parent.set(i, -1);
		}
		parent.set(source, -2);

		Queue<pair> queue;
		queue.enqueue({ source, INF });

		while (!queue.is_empty()) {

			int cur = queue.get_first().first_vertex;
			int flow = queue.get_first().second_vertex;
			queue.dequeue();

			for (int i = 0; i < adjacency.at(cur).get_size(); i++) {
				if (parent.at(i) == -1 && capacity.at(cur).at(i)) {
					parent.set(i, cur);
					int new_flow;
					if (capacity.at(cur).at(i) < flow)
						new_flow = capacity.at(cur).at(i);
					else
						new_flow = flow;
					if (i == sink)
						return new_flow;
					queue.enqueue({ i, new_flow });
				}
			}
		}
		return 0;
	}

	//return max flow in graph
	int Network::max_flow() {
		
		if (vertexes.isEmpty())	throw runtime_error("Error, graph is empty");
		int flow = 0;
		List<int> parent(capacity.get_size(), 0);
		int new_flow;

		while (new_flow = bfs(0, vertexes.get_size() - 1, parent)) {
			flow += new_flow;
			int cur = vertexes.get_size() - 1;
			while (cur != 0) {
				int prev = parent.at(cur);
				capacity.at(prev).set(cur, capacity.at(prev).at(cur) - new_flow);
				capacity.at(cur).set(prev, capacity.at(cur).at(prev) + new_flow);
				cur = prev;
			}
		}
		return flow;
	}
