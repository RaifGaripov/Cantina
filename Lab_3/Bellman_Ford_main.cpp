#include "Bellman-Ford_algorithm.h"
int main() {
	setlocale(LC_ALL, "rus");
	Bellman_Ford_algorithm solver;
	try {
		solver.set_data();
	}
	catch (runtime_error e) {
		cout << e.what() << endl;
	}
	try {
		solver.find_path(3, 0);
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
	}
	system("pause");
	return 0;
}