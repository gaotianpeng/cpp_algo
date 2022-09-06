#include <iostream>
#include <vector>
#include "common.h"
#include "arr_tools.h"

#include "gtest/gtest.h"

using namespace std;
using namespace tools;

int process(const vector<int>& arr, int left, int right) {
	if (left == right) {
		return arr[left];
	}

	int mid = left + ((right - left) >> 1);
	int left_val = process(arr, left, mid);
	int right_val = process(arr, mid + 1, right);
	return max(left_val, right_val);
}

int GetMax(const vector<int>& arr) {
	return process(arr, 0, arr.size() - 1);
}

/*
 * for test
 */
// 请调用者确认参数的合法性 arr.size() > 0
static int test(const vector<int>& arr) {
	int max = arr[0];
	for (int i = 1; i < arr.size(); i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	return max;
}

//TEST(RecursiveTest, GetMaxTest) {
//    cout << "get max test start\n";
//	int test_times = 500000;
//	int min_val = -100;
//	int max_val = 200;
//	int max_n = 100;
//	for (int i = 0; i < test_times; ++i) {
//		vector<int> arr1;
//		RandomArr(arr1, max_n, min_val, max_val);
//		if (arr1.size() < 1) {
//			continue;
//		}
//		vector<int> arr2;
//		CopyArr(arr1, arr2);
//		if (test(arr1) != GetMax(arr2)) {
//			EXPECT_TRUE(false);
//			break;
//		}
//
//	}
//	cout << "test success\n";
//	cout << "get max test end\n";
//}