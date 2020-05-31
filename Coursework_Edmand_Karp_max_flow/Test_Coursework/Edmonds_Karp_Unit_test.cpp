#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\raifg\source\repos\Coursework_Emdomds_Carp_max_flow\Coursework_Emdomds_Carp_max_flow\Edmonds_Karp.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EdmondsKarpUnittest
{
	TEST_CLASS(EdmondsKarpUnittest)
	{
	private:
		Network network;
	public:

		TEST_METHOD(test_read_file_wrong_file)
		{
			try {
				network.read_file("lajshfbjla.txt");
			}
			catch (exception exception) {
				Assert::AreEqual("Error, file is not open!", exception.what());
			}			
		}

		TEST_METHOD(test_read_file_wrong_input)
		{
			try {
				network.read_file("C:\\Users\\raifg\\source\\repos\\Coursework_Emdomds_Carp_max_flow\\Edmonds_Karp_Unit_test\\test_incorrect_input.txt");
			}
			catch (exception exception) {
				Assert::AreEqual("Error, graph must begin with “S” and end with “T”!", exception.what());
			}
		}

		TEST_METHOD(test_max_flow_empty_graph) 
		{
			try {
				network.max_flow();
			}
			catch (runtime_error exception) {
				Assert::AreEqual("Error, graph is empty", exception.what());
			}
			
		}
		TEST_METHOD(test_max_flow_correct)
		{
			network.read_file("C:\\Users\\raifg\\source\\repos\\Coursework_Emdomds_Carp_max_flow\\Edmonds_Karp_Unit_test\\test_correct.txt");
			Assert::AreEqual(5, network.max_flow());
		}
	};
}
