#include <iostream>
#include <vector>
#include "arr_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

// 在一个有序数组中，找>=某个数最左侧的位置
static int BSLeftestExist(vector<int>& arr, int val) {
	if (arr.size() == 0) {
		return -1;
	}

	int left = 0;
	int right = arr.size() - 1;
	int index = -1;
	while (left <= right) {
		int mid = left + ((right - left) >> 1);
		if (arr[mid] >= val) {
			index = mid;
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}

	return index;
}

/*
 * for test
 */
static int test(vector<int>& arr, int val) {
	if (arr.size() == 0) {
		return -1;
	}

	for (size_t i = 0; i < arr.size(); i++) {
		if (arr[i] >= val) {
			return i;
		}
	}

	return -1;
}

//TEST(SearchTest, BSLeftestExistTest) {
//	cout << " bs leftest exist test start\n";
//	int test_times = 500000;
//	int max_n = 10;
//	int min_val = -20;
//	int max_val = 30;
//	for (int i = 0; i < test_times; i++) {
//		vector<int> arr1;
//		RandomSortedArr(arr1, max_n, min_val, max_val);
//		vector<int> arr2;
//		CopyArr(arr1, arr2);
//
//		int val = RandomVal(min_val, max_val);
//		if (BSLeftestExist(arr1, val) != test(arr2, val)) {
//			EXPECT_TRUE(false);
//			cout << "find target val is " << val << endl;
//			Print(arr1);
//			break;
//		}
//	}
//	cout << " bs leftest exist test end\n";
//}
