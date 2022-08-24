#include <iostream>
#include <vector>
#include "arr_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

bool BSExist(vector<int>& arr, int val) {
	if (arr.size() == 0) {
		return false;
	}

	int left = 0;
	int right = arr.size() - 1;
	while (left < right) {
		int mid = left + ((right - left)>>1);
		if (val > arr[mid]) {
			left = mid + 1;
		} else if (val < arr[mid]) {
			right = mid - 1;
		} else {
			return true;
		}
	}

	return arr[left] == val;
}

/*
 * for test
 */
bool test(vector<int>& arr, int val) {
	if (arr.size() == 0) {
		return false;
	}

	for (auto& elem: arr) {
		if (elem == val) {
			return true;
		}
	}

	return false;
}

TEST(SearchTest, BSExistTest) {
	cout << " bs exist test start\n";
	int test_times = 500000;
	int max_n = 10;
	int min_val = -20;
	int max_val = 30;
	for (int i = 0; i < test_times; i++) {
		vector<int> arr1;
		RandomSortedArr(arr1, max_n, min_val, max_val);
		vector<int> arr2;
		CopyArr(arr1, arr2);

		int val = RandomVal(min_val, max_val);
		if (BSExist(arr1, val) != test(arr2, val)) {
			EXPECT_TRUE(false);
			cout << "find target val is " << val;
			Print(arr1);
			break;
		}
	}
	cout << " bs exist test end\n";
}
