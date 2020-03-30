#include "map.h"
using namespace std;
void main()
{
	
	map<int, int> Tree;
	Tree.InsertNode(10, 10);
	Tree.InsertNode(7, 15);
	Tree.InsertNode(15, 16);

	Tree.print();

	Tree.DeleteNode(10);

	Tree.~map();
}
