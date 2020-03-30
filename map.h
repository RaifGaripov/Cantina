#pragma once
#include <iostream>
#include <exception>
#include <list>
#include <windows.h>
using namespace std;
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
		Node<Key, Value>* parent, * left, * right;
		NodeColor color;
		Key key;
		Value value;
	public:
		Node(const Key _key, const Value _value, Node<Key, Value>* _parent = nullptr, Node<Key, Value>* _left = NIL, Node<Key, Value>* _right = NIL, NodeColor _color = RED)
		{
			key = _key;
			value = _value;
			parent = _parent;
			left = _left;
			right = _right;
			color = _color;
		}

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
	Node<Key, Value> sentinel;
	Node<Key, Value>* root;
public:
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
	list<Key> get_keys()
	{
		list<Key> List;
		help_get_keys(List, root);
		return List;
	}

	void help_get_keys(list<Key> &List, Node<Key, Value>* node)
	{
		if (node == NIL || node == nullptr)
			return;

			help_get_keys(List, node->getLeft());
			List.push_back(node->getKey());
			help_get_keys(List, node->getRight());
			return;
	}

	//return list of value
	list<Value> get_values()
	{
		list<Value> List;
		help_get_values(List, root);
		return List;
	}

	void help_get_values(list<Value>& List, Node<Key, Value>* node)
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
				throw exception("Already have node with that key");
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
			if (current == NIL) throw exception("Node not in map");

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