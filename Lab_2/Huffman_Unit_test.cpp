#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "..\Haffman_Lab_2\Huffman.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HuffmanUnittest
{
	TEST_CLASS(HuffmanUnittest)
	{
	public:
		map<int, string*> tree;
		List<Node_tree*> list;
		TEST_METHOD_INITIALIZE(init)
		{
		
			Node_tree* a = new Node_tree;
			a->code = 'a';
			a->frequency = 19;
			Node_tree* b = new Node_tree;
			b->code = 'b';
			b->frequency = 7;
			Node_tree* c = new Node_tree;
			c->code = 'c';
			c->frequency = 24;
			list.push_back(c);
			list.push_back(b);
			list.push_back(a);
		}
		
		TEST_METHOD(sort_list)
		{
			sortList(list);
			Assert::AreEqual(list.get_pointer(0)->data->code, 'b');
			Assert::AreEqual(list.get_pointer(1)->data->code, 'a');
			Assert::AreEqual(list.get_pointer(2)->data->code, 'c');
		}
		TEST_METHOD(test_Huffman_tree)
		{
			Huffman_tree(list);
			Assert::AreEqual(list.head->data->left->code, 'c');
			Assert::AreEqual(list.head->data->right->left->code, 'b');
			Assert::AreEqual(list.head->data->right->right->code, 'a');
		}
		TEST_METHOD(test_makeTable)
		{
			Huffman_tree(list);
			Node_tree* root = list.head->data;
			List<bool> listCode;
			map<char, bool*> table;
			table.InsertNode('a', nullptr);
			table.InsertNode('b', nullptr);
			table.InsertNode('c', nullptr);
			makeTable(root, table, listCode);
			Assert::AreEqual(table.FindNode('c')->value[0], false);
			Assert::AreEqual(table.FindNode('b')->value[0], true);
			Assert::AreEqual(table.FindNode('b')->value[1], false);
			Assert::AreEqual(table.FindNode('a')->value[0], true);
			Assert::AreEqual(table.FindNode('a')->value[1], true);
		}	
	};
}