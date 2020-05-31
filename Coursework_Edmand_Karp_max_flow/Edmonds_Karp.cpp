#include "Edmonds_Karp.h"

using namespace std;

int main()
{
	Network road;
	road.read_file("input.txt");
	cout << "Maximal flow is " << road.max_flow() << endl;
	system("pause");
	return 0;
}
