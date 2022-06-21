#include <iostream>
#include "sorting.hpp"
#include "unit_testing.hpp"

namespace sorting_testing {
	using namespace std;
	using namespace sorting;
	using namespace unit_testing;

	//random value generator seed (for consistantcy between tests)
	const int RAND_SEED = 1231548125718923;

	//get an array of size x with random values betwen a specified min and max
	inline int* get_dataset(int size, int min = 1, int max = 100000) {
		int* dataset = new int[size];

		for (int i = 0; i < size; i++) {
			dataset[i] = rand() % (max - min + 1) + min;
		}

		return dataset;
	}

	inline void test_functionality() {
		UnitTest test = UnitTest(L"Sorting Functionality Test");

		//initalize random value seed
		srand(RAND_SEED);

		//unsorted array
		int values[5] = { 3, 1, 4, 5, 2 };

		test.assert<bool>(L"Verify selection sort works correclty.", [&values]() {
			//run sort
			selection_sort(values, 5);

			//verify correct order
			return values[0] = 1 && values[1] == 2 && values[2] == 3 && values[3] == 4 && values[4] == 5;
		}, true);

		//reset array
		values[0] = 3;
		values[1] = 1;
		values[2] = 4;
		values[3] = 5;
		values[4] = 2;

		test.assert<bool>(L"Verify quick sort works correclty.", [&values]() {
			//run sort
			quick_sort(values, 5);

			//verify correct order
			return values[0] = 1 && values[1] == 2 && values[2] == 3 && values[3] == 4 && values[4] == 5;
		}, true);

		//print results
		test.log_results();
	}

	inline void test_performance() {
		UnitTest test = UnitTest(L"Sorting Performance Test");

		//initalize random value seed
		srand(RAND_SEED);

		//sizes to test
		vector<int> sizes = { 100, 1000, 10000, 100000 };

		for (auto size : sizes) {
			int* arr = get_dataset(size);
			
			test.assert<bool>(L"Selection Sort " + to_wstring(size) + L" items.", [&arr, &size]() {
				selection_sort(arr, size);
				return true;
			}, true);

			delete [] arr;
		}

		sizes.push_back(1000000);
		sizes.push_back(10000000);

		for (auto size : sizes) {
			int* arr = get_dataset(size);

			test.assert<bool>(L"Quick Sort " + to_wstring(size) + L" items.", [&arr, &size]() {
				quick_sort(arr, size);
				return true;
				}, true);

			delete[] arr;
		}

		//print results
		test.log_results();
	}
}