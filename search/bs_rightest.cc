#include <iostream>
#include <vector>
#include "arr_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

// 在一个有序数组中，找<=某个数最右侧的位置
static int BSRightestExist(vector<int>& arr, int val) {
	if (arr.size() == 0) {
		return -1;
	}

	int index = -1;
	int left = 0;
	int right = arr.size() - 1;
	while (left <= right) {
		int mid = left + ((right - left)>>1);
		if (arr[mid] <= val) {
			index = mid;
			left = mid + 1;
		} else {
			right = mid - 1;
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

	for (int i = arr.size() - 1; i >= 0; --i) {
		if (arr[i] <= val) {
			return i;
		}
	}

	return -1;
}

//TEST(SearchTest, BSRightestExistTest) {
//	cout << " bs rightest exist test start\n";
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
//		if (BSRightestExist(arr1, val) != test(arr2, val)) {
//			Print(arr1);
//			cout << "find target val is " << val << endl;
//			cout << BSRightestExist(arr1, val) << endl;
//			cout << test(arr2, val) << endl;
//			EXPECT_TRUE(false);
//			break;
//		}
//	}
//	cout << " bs rightest exist test end\n";
//}
