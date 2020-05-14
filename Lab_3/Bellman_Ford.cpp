#include "Bellman-Ford_algorithm.h"
Bellman_Ford_algorithm::Bellman_Ford_algorithm()
{
	amount_of_cities = 0;
	amount_of_edges = 0;
}

Bellman_Ford_algorithm::~Bellman_Ford_algorithm()
{
}

// Sets data from "in.txt" file
void Bellman_Ford_algorithm::set_data()
{
	if (!city.isEmpty()) {
		city.clear();
		edges.clear();
	}
	ifstream file("in.txt");
	if (!file.is_open())
		throw runtime_error("File is not found");
	List<char> temp_city;
	edge temp_edge;
	char symbol;
	bool second_city = false;
	while (!file.eof()) {
		file >> noskipws >> symbol;
		if (file.eof())
			break;
		if (symbol == ';')
		{
			file >> symbol;
			if (!city.contains(temp_city))
			{
				amount_of_cities++;
				city.push_back(temp_city);
				if (!second_city)
					temp_edge.vertex1 = city.get_number(temp_city);
				else
					temp_edge.vertex2 = city.get_number(temp_city);
				temp_city.reset();
			}
			else {
				if (!second_city)
					temp_edge.vertex1 = city.get_number(temp_city);
				else
					temp_edge.vertex2 = city.get_number(temp_city);
				temp_city.clear();
			}
			if (!second_city) {
				second_city = true;
			}
			else {
				if (symbol == 'N') {
					temp_edge.cost = INF;
					while (symbol != '\n' && !file.eof() && symbol != ';')
						file >> symbol;
				}
				else {
					file.unget();
					file >> temp_edge.cost;
					file >> symbol;
				}
				edges.push_back(temp_edge);
				swap(temp_edge.vertex1, temp_edge.vertex2);
				file >> symbol;
				if (symbol == 'N') {
					temp_edge.cost = INF;
					while (symbol != '\n' && !file.eof() && symbol != ';')
						file >> symbol;
				}
				else {
					file.unget();
					file >> temp_edge.cost;
				}
				edges.push_back(temp_edge);
				while (symbol != '\n' && !file.eof())
					file >> symbol;
				second_city = false;
				continue;
			}
		}
		temp_city.push_back(symbol);
	}
	amount_of_edges = edges.get_size();
	file.close();
}

// Prints the shortest path from one city to another
void Bellman_Ford_algorithm::find_path(size_t start, size_t destination) {
	if (city.isEmpty())
		throw runtime_error("Data is not set");
	if (start < 0 || destination < 0 || start > amount_of_cities - 1 || destination > amount_of_cities - 1)
		throw invalid_argument("Number of city is incorrect");
	List<int> distance(amount_of_cities, INF);
	List<int> predecessor(amount_of_cities, -1);
	distance.set(start, 0);
	bool any;
	for (;;) {
		any = false;
		for (size_t j = 0; j < amount_of_edges; ++j) {
			if (distance.at(edges.at(j).vertex1) < INF) {
				if (distance.at(edges.at(j).vertex2) > distance.at(edges.at(j).vertex1) + edges.at(j).cost)
				{
					distance.set(edges.at(j).vertex2, distance.at(edges.at(j).vertex1) + edges.at(j).cost);
					predecessor.set(edges.at(j).vertex2, edges.at(j).vertex1);
					any = true;
				}
			}
		}
		if (!any)  break;
	}
	if (distance.at(destination) == INF) {
		cout << "No flights from ";
		city.at(start).print_to_console();
		cout << " to ";
		city.at(destination).print_to_console();
		cout << '.' << endl;
		return;
	}
	List<int> path;
	int price = 0;
	for (int cur = destination; cur != -1; cur = predecessor.at(cur))
	{
		path.push_back(cur);
	}
	path.reverse();
	for (size_t i = 1; i < path.get_size(); i++) {
		price += edges.get_price(path.at(i - 1), path.at(i));
	}
	cout << "Flight from ";
	city.at(start).print_to_console();
	cout << " to ";
	city.at(destination).print_to_console();
	cout << ":\n";
	for (size_t i = 0; i < path.get_size(); ++i)
	{
		city.at(path.at(i)).print_to_console();
		if (i + 1 != path.get_size())
			cout << " -> ";
	}
	cout << endl << "Cost: " << price << endl;
}

// Returns the shortest path as list of indices
List<int> Bellman_Ford_algorithm::return_path(size_t start, size_t destination) {
	if (city.isEmpty())
		throw runtime_error("Data is not set");
	if (start < 0 || destination < 0 || start > amount_of_cities - 1 || destination > amount_of_cities - 1)
		throw invalid_argument("Number of city is incorrect");
	List<int> distance(amount_of_cities, INF);
	List<int> predecessor(amount_of_cities, -1);
	distance.set(start, 0);
	bool any;
	for (;;) {
		any = false;
		for (size_t j = 0; j < amount_of_edges; ++j) {
			if (distance.at(edges.at(j).vertex1) < INF) {
				if (distance.at(edges.at(j).vertex2) > distance.at(edges.at(j).vertex1) + edges.at(j).cost)
				{
					distance.set(edges.at(j).vertex2, distance.at(edges.at(j).vertex1) + edges.at(j).cost);
					predecessor.set(edges.at(j).vertex2, edges.at(j).vertex1);
					any = true;
				}
			}
		}
		if (!any)  break;
	}
	List<int> path;
	if (distance.at(destination) == INF) {
		cout << "No flights from ";
		city.at(start).print_to_console();
		cout << " to ";
		city.at(destination).print_to_console();
		cout << '.' << endl;
		return path;
	}
	for (int cur = destination; cur != -1; cur = predecessor.at(cur))
	{
		path.push_back(cur);
	}
	path.reverse();
	return path;
}

// Swaps values of arguments
void Bellman_Ford_algorithm::swap(int& value1, int& value2) {
	int temp = value1;
	value1 = value2;
	value2 = temp;
}

// Sets info from file with path specified as argument 
void Bellman_Ford_algorithm::set_data(string path)
{
	if (!city.isEmpty()) {
		city.clear();
		edges.clear();
	}
	ifstream file(path);
	if (!file.is_open())
		throw runtime_error("File is not found");
	List<char> temp_city;
	edge temp_edge;
	char symbol;
	bool second_city = false;
	while (!file.eof()) {
		file >> noskipws >> symbol;
		if (file.eof())
			break;
		if (symbol == ';')
		{
			file >> symbol;
			if (!city.contains(temp_city))
			{
				amount_of_cities++;
				city.push_back(temp_city);
				if (!second_city)
					temp_edge.vertex1 = city.get_number(temp_city);
				else
					temp_edge.vertex2 = city.get_number(temp_city);
				temp_city.reset();
			}
			else {
				if (!second_city)
					temp_edge.vertex1 = city.get_number(temp_city);
				else
					temp_edge.vertex2 = city.get_number(temp_city);
				temp_city.clear();
			}
			if (!second_city) {
				second_city = true;
			}
			else {
				if (symbol == 'N') {
					temp_edge.cost = INF;
					while (symbol != '\n' && !file.eof() && symbol != ';')
						file >> symbol;
				}
				else {
					file.unget();
					file >> temp_edge.cost;
					file >> symbol;
				}
				edges.push_back(temp_edge);
				swap(temp_edge.vertex1, temp_edge.vertex2);
				file >> symbol;
				if (symbol == 'N') {
					temp_edge.cost = INF;
					while (symbol != '\n' && !file.eof() && symbol != ';')
						file >> symbol;
				}
				else {
					file.unget();
					file >> temp_edge.cost;
				}
				edges.push_back(temp_edge);
				while (symbol != '\n' && !file.eof())
					file >> symbol;
				second_city = false;
				continue;
			}
		}
		temp_city.push_back(symbol);
	}
	amount_of_edges = edges.get_size();
	file.close();
}