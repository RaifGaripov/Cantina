#include <iostream>
#include <fstream>
#include <exception>
#include <windows.h>

using namespace std;

//// Class of Node Haffman tree

class Node_tree
{
public:
	int frequency;
	char code;
	Node_tree* left, * right;

	Node_tree() { left = right = NULL; }

	Node_tree(Node_tree* Left, Node_tree* Right)
	{
		left = Left;
		right = Right;
		frequency = Left->frequency + Right->frequency;
	}
};

////list
template<typename T>
class NodeOfList
{
public:
	T data;
	NodeOfList* next, * prev;
	NodeOfList() : next(NULL), prev(NULL) {};
	NodeOfList(T data)
	{
		this->data = data;
		next = NULL;
		prev = NULL;
	}

	~NodeOfList()
	{
		next = NULL;
		prev = NULL;
	}

	void set_data(T data)
	{
		this->data = data;
	}

	T get_data()
	{
		return data;
	}

	NodeOfList* get_next()
	{
		return next;
	}

	NodeOfList* get_prev()
	{
		return prev;
	}

	void set_next(NodeOfList* pointer)
	{
		next = pointer;
	}

	void set_prev(NodeOfList* pointer)
	{
		prev = pointer;
	}
};

template<typename T>
class List
{
private:
public:

	
	NodeOfList<T>* head, * tail;
	NodeOfList<T>* get_pointer(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Invalid argument");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			NodeOfList<T>* temp = head;
			while ((temp) && (index--))
			{
				temp = temp->get_next();
			}
			return temp;
		}
	}
	List() : head(nullptr), tail(nullptr) {}
	List(const List<T>& list) {
		clear();
		NodeOfList<T>* temp = list.head;
		while (temp) {
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}
	~List()
	{
		if (head == NULL)
		{
			head = NULL;
		}
		else
		{
			while (head)
			{
				tail = head->get_next();
				delete head;
				head = tail;
			}
		}
	}
	void push_back(T data)
	{
		NodeOfList<T>* temp = new NodeOfList<T>;
		temp->set_data(data);
		if (head)
		{
			temp->set_prev(tail);
			tail->set_next(temp);
			tail = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}
	void push_front(T data)
	{
		NodeOfList<T>* temp = new NodeOfList<T>;
		temp->set_data(data);
		if (head)
		{
			temp->set_next(head);
			head->set_prev(temp);
			head = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}
	void push_front(List& ls2)
	{
		NodeOfList<T>* temp = ls2.tail;
		size_t n = ls2.get_size();
		while ((temp) && (n--))
		{
			push_front(temp->get_data());
			temp = temp->get_prev();
		}
	}
	void pop_back()
	{
		if (head != tail)
		{
			NodeOfList<T>* temp = tail;
			tail = tail->get_prev();
			tail->set_next(NULL);
			delete temp;
		}
		else if (!isEmpty())
		{
			NodeOfList<T>* temp = tail;
			tail = head = NULL;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	void pop_front()
	{
		if (head)
		{
			NodeOfList<T>* temp = head;
			head = head->get_next();
			delete temp;
		}
		else if (head == tail && get_size() == 1)
		{
			NodeOfList<T>* temp = head;
			head = tail = NULL;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	void insert(size_t index, T data)
	{
		NodeOfList<T>* temp;
		temp = get_pointer(index);
		if (temp == head)	push_front(data);
		else
		{
			NodeOfList<T>* newElem = new NodeOfList;
			newElem->set_data(data);
			temp->get_prev()->set_next(newElem);
			newElem->set_prev(temp->get_prev());
			newElem->set_next(temp);
			temp->set_prev(newElem);
		}
	}
	T at(size_t index)
	{
		NodeOfList<T>* temp;
		temp = get_pointer(index);
		return temp->get_data();
	}
	void remove(size_t index)
	{
		NodeOfList<T>* temp;
		temp = get_pointer(index);
		if (temp == head)	pop_front();
		else if (temp == tail)	pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}
	void remove(T data) {
		NodeOfList<T>* temp = head;
		while (temp && temp->get_data() != data)
			temp = temp->get_next();
		if (!temp)
			throw out_of_range("Invalid argument");
		if (temp == head)	pop_front();
		else if (temp == tail)	pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}
	size_t get_size()
	{
		NodeOfList<T>* temp = head;
		size_t length = 0;
		while (temp)
		{
			length++;
			temp = temp->get_next();
		}
		return length;
	}
	void print_to_console()
	{
		NodeOfList<T>* temp = head;
		while (temp)
		{
			cout << temp->get_data() << ' ';
			temp = temp->get_next();
		}
		cout << endl;
	}
	void clear()
	{
		if (this->isEmpty())
			return;
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
	}
	void set(size_t index, T data)
	{
		NodeOfList<T>* temp;
		temp = get_pointer(index);
		temp->set_data(data);
	}
	bool isEmpty()
	{
		if (!head)
			return true;
		else
			return false;
	}
};


////map

template <typename Key, typename Value>
class map
{
public:
	typedef enum { BLACK, RED } NodeColor;
#define NIL &sentinel
	template <typename Key, typename Value>
	class Node
	{
	private:
	

	public:
		Node<Key, Value>* parent, * left, * right;
		NodeColor color;
		Node(const Key _key, const Value _value, Node<Key, Value>* _parent = nullptr, Node<Key, Value>* _left = NIL, Node<Key, Value>* _right = NIL, NodeColor _color = RED)
		{
			key = _key;
			value = _value;
			parent = _parent;
			left = _left;
			right = _right;
			color = _color;
		}
		Key key;
		Value value;
		void setLeft(Node* temp)
		{
			left = temp;
		}

		Node<Key, Value>* getLeft()
		{
			return left;
		}



		void setRight(Node* temp)
		{
			right = temp;
		}

		Node<Key, Value>* getRight()
		{
			return right;
		}

		void setParent(Node* temp)
		{
			parent = temp;
		}

		Node<Key, Value>* getParent()
		{
			return parent;
		}

		void setColor(NodeColor colour)
		{
			color = colour;
		}

		NodeColor getColor()
		{
			return color;
		}

		Key getKey()
		{
			return key;
		}

		Value getValue()
		{
			return value;
		}

		void setValue(Value _value)
		{
			value = _value;
		}

		void setKey(Key _key)
		{
			key = _key;
		}
	};
private:

public:
	
	Node<Key, Value> sentinel;
	Node<Key, Value>* root;
	Node<Key, Value>* getRoot() { return root; }

	map() : sentinel(0, 0, nullptr, NIL, NIL, BLACK)
	{
		root = NIL;
	}

	//clear tree
	void clear(Node<Key, Value>* node)
	{
		if (node == NIL || node == nullptr)
			return;

		clear(node->getLeft());
		clear(node->getRight());

		delete node;

	}

	~map()
	{
		clear(root);
		root = nullptr;
	}

	//return list of keys
	List<Key> get_keys()
	{
		List<Key> list;
		help_get_keys(list, root);
		return list;
	}

	void help_get_keys(List<Key>& List, Node<Key, Value>* node)
	{
		if (node == NIL || node == nullptr)
			return;

		help_get_keys(List, node->getLeft());
		List.push_back(node->getKey());
		help_get_keys(List, node->getRight());
		return;
	}

	//return list of value
	List<Value> get_values()
	{
		List<Value> list;
		help_get_values(list, root);
		return list;
	}

	void help_get_values(List<Value>& List, Node<Key, Value>* node)
	{
		if (node == NIL || node == nullptr)
			return;
		help_get_values(List, node->getLeft());
		List.push_back(node->getValue());
		help_get_values(List, node->getRight());
		return;
	}

	//print tree to console
	void print()
	{
		int length = 0;
		if (root == nullptr) throw exception("Map is empty");
		help_print(root, length, false);
	}

	void help_print(Node<Key, Value>* node, int length, bool side)
	{
		for (int i = 0; i < length; i++)
			cout << ' ';
		if (length != 0 && node != NIL)
		{
			cout << '|';
			cout << "->";
			if (side == false)
				cout << "L: ";
			else
				cout << "R: ";
		}
		else
			cout << ' ';
		if (node != NIL)
		{
			if (node->getColor() == BLACK)
				outColor(7, 0);
			else
				outColor(12, 0);
			cout << node->getKey() << '(' << node->getValue() << ')' << endl;
			outColor(7, 0);
		}

		if (node != NIL)
		{
			if (length > 0)
			{
				if (node->getLeft() || node->getRight())
				{
					help_print(node->getLeft(), length + 3, false);
					help_print(node->getRight(), length + 3, true);
				}
			}
			else
			{
				if (node->getLeft() || node->getRight())
				{
					help_print(node->getLeft(), length + 1, false);
					help_print(node->getRight(), length + 1, true);
				}
			}
		}
	}

	void outColor(int textColor, int backColor)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, (WORD)((backColor << 4) | textColor));
	}

	void getListTree(Node<Key, Value>* root, List<Node_tree*>& A)

	{

		if (root == NIL || root == nullptr) { return; }
		else
		{

			getListTree(root->left, A);

			getListTree(root->right, A);

			Node_tree* p = new Node_tree;

			p->code = root->key;

			p->frequency = root->value;

			A.push_back(p);

		}

	}

	//insert Node
	void InsertNode(const Key key, const Value value)
	{
		Node<Key, Value>* newNode, * current, * parent;
		current = root;
		parent = nullptr;
		while (current != NIL)
		{
			if (key == current->getKey())
			{
				current->value += 1;
				return;
			}
			parent = current;
			if (key < current->getKey())
			{
				current = current->getLeft();
			}
			else
			{
				current = current->getRight();
			}
		}
		newNode = new Node<Key, Value>(key, value, parent, NIL, NIL, RED);	// create new Node
		if (parent == nullptr)
		{
			root = newNode;    //empty tree
		}
		else
		{
			if (newNode->getKey() < parent->getKey())
			{
				parent->setLeft(newNode);
			}
			else
			{
				parent->setRight(newNode);
			}
		}
		//check if RBT still RBT and change it
		InsertFixup(newNode);
	}

	//search Node
	Node<Key, Value>* FindNode(const Key key)
	{
		Node<Key, Value>* current = root;
		while (root)
		{
			if (current == NIL) return current;

			if (current->getKey() == key) return current;

			if (key < current->getKey())
			{
				current = current->getLeft();
			}
			else
			{
				current = current->getRight();
			}
		}
	}

	//delete a Node by key
	void DeleteNode(const Key key)
	{
		Node<Key, Value>* current = FindNode(key), * lefted, * righted;  //supporting ptr
		if (current == nullptr || current == NIL) return;

		if (current->getLeft() == NIL || current->getRight() == NIL) //one kid doesn't exist
		{
			righted = current;
		}
		else //both kids absent
		{
			righted = current->getRight();
			while (righted->getLeft() != NIL)
			{
				righted = righted->getLeft();
			}
		}
		// only one kid
		if (righted->getLeft() != NIL)
		{
			lefted = righted->getLeft();
		}
		else
		{
			lefted = righted->getRight();
		}
		//delete righted 
		lefted->setParent(righted->getParent());
		if (righted->getParent() != nullptr)
		{
			if (righted == righted->getParent()->getLeft())
			{
				righted->getParent()->setLeft(lefted);
			}
			else
			{
				righted->getParent()->setRight(lefted);
			}
		}
		else
		{
			root = lefted;
		}

		if (righted != current)
		{
			current->setKey(righted->getKey());
			current->setKey(righted->getKey());
		}

		if (righted->getColor() == BLACK)
		{
			DeleteFixup(lefted);
		}
		delete righted;
	}

	void PrintTable(Node<char, bool*>* root)
	{
		int arrSize;
		if (root == NULL || root == NIL) return;
		else
		{
			PrintTable(root->right);
			cout << root->key << " - simbol | code: ";
			arrSize = _msize(root->value) / sizeof(root->value[0]);
			for (int i = 0; i < arrSize; i++)
			{
				cout << root->value[i];
			}
			cout << endl;
			PrintTable(root->left);
		}
	}

private:
	//rotate tree with root to right
	void RotateRight(Node<Key, Value>* node)
	{
		Node<Key, Value>* leftKid = node->getLeft();

		node->setLeft(leftKid->getRight());

		if (leftKid->getRight() != NIL)
		{
			leftKid->getRight()->setParent(node);
		}

		if (leftKid != NIL)
		{
			leftKid->setParent(node->getParent());
		}

		if (node->getParent() != nullptr)
		{
			if (node == node->getParent()->getRight())
			{
				node->getParent()->setRight(leftKid);
			}
			else
			{
				node->getParent()->setLeft(leftKid);
			}
		}
		else root = leftKid;

		leftKid->setRight(node);
		if (node != NIL)
		{
			node->setParent(leftKid);
		}
	}

	//rotate tree with root to left
	void RotateLeft(Node<Key, Value>* node)
	{
		Node<Key, Value>* temp = node->getRight();

		//making right undertree for node
		node->setRight(temp->getLeft());
		if (temp->getLeft() != NIL)
		{
			temp->getLeft()->setParent(node);
		}

		if (temp != NIL)
		{
			temp->setParent(node->getParent());
		}

		if (node->getParent() != nullptr)
		{
			if (node == node->getParent()->getLeft())
			{
				node->getParent()->setLeft(temp);
			}
			else
			{
				node->getParent()->setRight(temp);
			}
		}
		else
		{
			root = temp;
		}

		//link node and temp
		temp->setLeft(node);
		if (node != NIL)
		{
			node->setParent(temp);
		}
	}

	//balance tree after insert
	void InsertFixup(Node<Key, Value>* node)
	{
		//moving until root
		while (node != root && node->getParent()->getColor() == RED)
		{
			if (node->getParent() == node->getParent()->getParent()->getLeft())
			{
				//parent in left tree 
				//relative grandparent
				Node<Key, Value>* uncle = node->getParent()->getParent()->getRight();
				//if uncle is RED
				if (uncle->getColor() == RED)
				{
					//repaint parent and uncle in BLACK
					node->getParent()->setColor(BLACK);
					uncle->setColor(BLACK);
					//paint grandparent in RED
					node->getParent()->getParent()->setColor(RED);
					//grandparent now is node
					node = node->getParent()->getParent();
				}
				else //uncle BLACK
				{
					if (node == node->getParent()->getRight())
					{
						node->setParent(node);
						RotateLeft(node);
					}
					node->getParent()->setColor(BLACK);
					node->getParent()->getParent()->setColor(RED);
					RotateRight(node->getParent()->getParent());
				}
			}
			else
			{
				//parent in right tree
				//relative grandparent
				Node<Key, Value>* uncle = node->getParent()->getParent()->getLeft();
				if (uncle->getColor() == RED)
				{
					node->getParent()->setColor(BLACK);
					uncle->setColor(BLACK);
					node = node->getParent()->getParent();
				}
				else
				{
					if (node == node->getParent()->getLeft())
					{
						node = node->getParent();
						RotateRight(node);
					}
					node->getParent()->setColor(BLACK);
					node->getParent()->getParent()->setColor(RED);
					RotateLeft(node->getParent()->getParent());
				}
			}
		}
		root->setColor(BLACK);
	}

	//balance tree after delete
	void DeleteFixup(Node<Key, Value>* node)
	{
		while (node != root && node->getColor() == BLACK)
		{
			if (node == node->getParent()->getLeft())
			{
				//node which need to delete - parent of left tree
				Node<Key, Value>* brother = node->getParent()->getRight();
				if (brother->getColor() == RED)
				{
					brother->setColor(BLACK);
					node->getParent()->setColor(RED);
					RotateLeft(node->getParent());
					brother = node->getParent()->getRight();
				}

				if (brother->getLeft()->getColor() == BLACK && brother->getRight()->getColor() == BLACK)
				{
					brother->setColor(RED);
					node = node->getParent();
				}
				else
				{
					if (brother->getRight()->getColor() == BLACK)
					{
						brother->getLeft()->setColor(BLACK);
						brother->setColor(RED);
						RotateRight(brother);
						brother = node->getParent()->getRight();
					}
					brother->setColor(node->getParent()->getColor());
					node->getParent()->setColor(BLACK);
					brother->getRight()->setColor(BLACK);
					RotateLeft(node->getParent());
					node = root;
				}
			}
			else
			{
				//node which need to delete - parent of right tree
				Node<Key, Value>* brother = node->getParent()->getLeft();
				if (brother->getColor() == RED)
				{
					brother->setColor(BLACK);
					node->getParent()->setColor(RED);
					RotateRight(node->getParent());
					brother = node->getParent()->getLeft();
				}
				if (brother->getRight()->getColor() == BLACK && brother->getLeft()->getColor() == BLACK)
				{
					brother->setColor(RED);
					node = node->getParent();
				}
				else
				{
					if (brother->getLeft()->getColor() == BLACK)
					{
						brother->getRight()->setColor(BLACK);
						brother->setColor(RED);
						RotateLeft(brother);
						brother = node->getParent()->getLeft();
					}
					brother->setColor(node->getParent()->getColor());
					node->getParent()->setColor(BLACK);
					brother->getLeft()->setColor(BLACK);
					RotateRight(node->getParent());
					node = root;
				}
			}
		}
		node->setColor(BLACK);
	}

	//delete node
	void DeleteNode(Node<Key, Value>* node)
	{
		Node<Key, Value>* lefted, righted;
		if (node == nullptr || node == NIL)
		{
			throw exception("Error, nothing to delete");
		}

		if (node->getLeft() == NIL || node->getRight() == NIL)
		{
			//one of kids is NIL
			righted = node;
		}
		else
		{
			//have both kids
			righted = node->getRight();
			while (righted.getLeft() != NIL)
			{
				righted = righted.getLeft();
			}
		}

		//if righted gave only one kid
		if (righted.getLeft() != NIL)
		{
			lefted = righted.getLeft();
		}
		else
		{
			lefted = righted.getRight();
		}

		//delete righted from parents
		lefted->getParent() = righted.getParent();
		if (righted.getParent() != nullptr)
		{
			if (righted == righted.getParent()->getLeft())
			{
				righted.getParent()->setLeft(lefted);
			}
			else
			{
				righted.getParent()->setRight(lefted);
			}
		}
		else
		{
			root = node;
		}
		if (righted != node)
		{
			node->setValue(righted.getValue());
		}
		delete righted;
		righted = nullptr;
	}

};



void FrontBackSplit(NodeOfList<Node_tree*>* source,
	NodeOfList<Node_tree*>** frontRef, NodeOfList<Node_tree*>** backRef)
{
	NodeOfList<Node_tree*>* fast;
	NodeOfList<Node_tree*>* slow;
	slow = source;
	fast = source->next;

	while (fast != nullptr) {
		fast = fast->next;
		if (fast != nullptr) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = nullptr;
}

NodeOfList<Node_tree*>* SortedMerge(NodeOfList<Node_tree*>* a, NodeOfList<Node_tree*>* b)
{
	NodeOfList<Node_tree*>* result = nullptr;

	if (a == nullptr)
		return (b);
	else if (b == nullptr)
		return (a);

	if (a->data->frequency <= b->data->frequency) {
		result = a;
		result->set_data(a->data);
		result->next = SortedMerge(a->next, b);
	}
	else {
		result = b;
		result->set_data(b->data);
		result->next = SortedMerge(a, b->next);
	}
	return (result);
}

void helpMergSort(NodeOfList<Node_tree*>** headRef)
{
	NodeOfList<Node_tree*>* head = *headRef;
	NodeOfList<Node_tree*>* a;
	NodeOfList<Node_tree*>* b;

	if ((head == nullptr) || (head->next == nullptr)) {
		return;
	}

	FrontBackSplit(head, &a, &b);

	helpMergSort(&a);
	helpMergSort(&b);

	*headRef = SortedMerge(a, b);
}

void MergeSort(List<Node_tree*>& headRef)
{
	helpMergSort(&headRef.head);
}

////make a Huffman tree
void Huffman_tree(List<Node_tree*>& List)
{
	while (List.get_size()!= 1)

	{

		MergeSort(List);

		Node_tree* Left = List.head->data;

		List.pop_front();

		Node_tree* Right = List.head->data;

		List.pop_front();

		Node_tree* parent = new Node_tree(Left, Right);

		List.push_front(parent);

	}
}

////making table of coding
void makeTable(Node_tree* root, map<char, bool*>& table, List<bool>& listCode)
{
	if (root->left != nullptr)
	{
		listCode.push_back(false);
		makeTable(root->left, table, listCode);
	}

	if (root->right != nullptr)
	{
		listCode.push_back(true);
		makeTable(root->right, table, listCode);
	}

	if (root->left == nullptr && root->right == nullptr)
	{
		table.FindNode(root->code)->value = new bool[listCode.get_size()];
		for (size_t i = 0; i < listCode.get_size(); i++)
		{
			table.FindNode(root->code)->value[i] = listCode.get_pointer(i)->data;
		}
	}

	////when table is done

	if (listCode.isEmpty())	return;

	listCode.pop_back();
};


int main()
{
	setlocale(LC_ALL, "russian");
	map<char, int> Map;
	map<char, bool*> table;
	fstream f; char symbol; int memory = 0; double compression_coef;


/////reading the string in map

	cout << "Input string: ";

		f.open("in.txt", ios::in);
		while (f.get(symbol))
		{
			cout << symbol;
			Map.InsertNode(symbol, 1);
			memory++;
			table.InsertNode(symbol, nullptr);
		}
		cout << endl << "Before compression memory: " << memory * 8 << endl;
		compression_coef = memory * 8;
/////making list of nodes  

	List<Node_tree*> list_tree;
	Map.getListTree(Map.getRoot(), list_tree);

/////making a huffman tree

	Huffman_tree(list_tree);
	
	Node_tree* root = list_tree.head->data; 

/////making table of coding
	List<bool> listCode;
	makeTable(root, table, listCode);
/////decoding huffman
	f.clear(); f.seekg(0);
	int length; memory = 0;
	cout << "Output string:" << endl;
	while (f.get(symbol))
	{
		length = _msize(table.FindNode(symbol)->value) / sizeof(table.FindNode(symbol)->value[0]);
		memory = memory + length;
		for (int i = 0; i < length; i++)
			cout << table.FindNode(symbol)->value[i];
		cout << " ";
	}
	cout << endl;

	cout << "After compression memory: " << memory << endl;
	compression_coef = (float) compression_coef / memory;
	cout << "Compression coefficient = " << compression_coef << endl;
	table.PrintTable(table.getRoot());
	f.close();

	system("pause");
	return 0;
}
