#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_1_4_sem_A'n'S_Garipov/map.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace map_test
{
	TEST_CLASS(map_test)
	{
		map<int, char> Map;
	public:

		TEST_METHOD_INITIALIZE(test_init)
		{
			Map.InsertNode(1, 'm');
			Map.InsertNode(2, 'a');
			Map.InsertNode(3, 'p');
		}
		
		TEST_METHOD(test_InsertNode)
		{
			Map.InsertNode(4, 's');
			Assert::AreEqual(4, Map.FindNode(4)->getKey());
			try
			{
				Map.InsertNode(1, 'm');
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual("Already have node with that key", ex.what());
			}
		}

		TEST_METHOD(test_DeleteNode)
		{
			Map.DeleteNode(1);
			try
			{
				Map.FindNode(1);
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual("Node not in map", ex.what());
			}
			Map.~map();
			try
			{
				Map.DeleteNode(2);
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual("Node not in map", ex.what());
			}
		}

		TEST_METHOD(test_FindNode)
		{
			Assert::AreEqual(3, Map.FindNode(3)->getKey());

			Map.DeleteNode(1);
			try
			{
				Map.FindNode(1);
			}
			catch (const std::exception & ex)
			{
				Assert::AreEqual("Node not in map", ex.what());
			}

		}

		TEST_METHOD(test_clear)
		{
			Assert::AreEqual(Map.FindNode(3)->getValue(), 'p');
			Map.~map();
			try
			{
				Map.FindNode(3);
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual("Node not in map", ex.what());
			}
		}

		TEST_METHOD(get_keys)
		{
			list<int> List_test = Map.get_keys();
			auto iter = List_test.begin();
			Assert::AreEqual(*iter, 1);
			iter.operator++();
			Assert::AreEqual(*iter, 2);
			iter.operator++();
			Assert::AreEqual(*iter, 3);
		}

		TEST_METHOD(get_values)
		{
			list<char> List_test = Map.get_values();
			auto iter = List_test.begin();
			Assert::AreEqual(*iter, 'm');
			iter.operator++();
			Assert::AreEqual(*iter, 'a');
			iter.operator++();
			Assert::AreEqual(*iter, 'p');
		}

		TEST_METHOD(test_print)
		{
			Map.~map();
			try
			{
				Map.print();
			}
			catch (const std::exception& ex)
			{
				Assert::AreEqual(ex.what(), "Map is empty");
			}
		}
	};
}
