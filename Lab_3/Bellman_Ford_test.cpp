#include "pch.h"
#include "CppUnitTest.h"
#include "C:\\Users\raifg\source\repos\Bellman_Ford\Bellman_Ford\Bellman-Ford_algorithm.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Bellman_Ford
{
	TEST_CLASS(Bellman_Ford)
	{
	public:

		TEST_METHOD(test_set_data)
		{
			Bellman_Ford_algorithm path;
			try {
				path.set_data("wrong_test_file.txt");
			}
			catch (runtime_error e) {
				Assert::AreEqual(e.what(), "File is not found");
			}
			path.set_data("C:\\Users\raifg\source\repos\Bellman_Ford\Bellman_Ford_test\test.txt");
		}
		TEST_METHOD(test_find_path) {
			Bellman_Ford_algorithm path;
			try {
				path.find_path(0, 5);
			}
			catch (runtime_error e) {
				Assert::AreEqual(e.what(), "Data is not set");
			}
			path.set_data("C:\\Users\raifg\source\repos\Bellman_Ford\Bellman_Ford_test\test.txt");
			try {
				path.find_path(0, 5);
			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "Number of city is incorrect");
			}
			List<int> flight = path.return_path(0, 2);
			Assert::AreEqual(flight.at(0), 0);
			Assert::AreEqual(flight.at(1), 1);
			Assert::AreEqual(flight.at(2), 2);
		}
	};
}