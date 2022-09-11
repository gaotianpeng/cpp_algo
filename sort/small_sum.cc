#include <array>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;
/*
	在一个数组中，一个数左边比它小的数的总和，叫数的小和，所有数的小和累加起来，叫数组小和。求数组小和。
	例子： [1,3,4,2,5]
	1左边比1小的数：没有
	3左边比3小的数：1
	4左边比4小的数：1、3
	2左边比2小的数：1
	5左边比5小的数：1、3、4、 2
	所以数组的小和为1+1+3+1+1+3+4+2=16
 */

static int merge(vector<int>& arr, size_t left, size_t mid, size_t right) {
	size_t n = right - left + 1;
	int* helper = new int[n];
	size_t i = 0;
	size_t p1 = left;
	size_t p2 = mid + 1;
	int res = 0;

	while (p1 <= mid && p2 <= right) {
		res += arr[p1] < arr[p2] ? (right - p2 + 1)*arr[p1]: 0;
		helper[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
	}

	while (p1 <= mid) {
		helper[i++] = arr[p1++];
	}

	while (p2 <= right) {
		helper[i++] = arr[p2++];
	}

	for (size_t i = 0; i < n; i++) {
		arr[left + i] = helper[i];
	}

	delete [] helper;

	return res;
}

static int process(vector<int>& arr, int left, int right) {
	if (left == right) {
		return 0;
	}

	int mid = left + ((right - left) >> 1);
	return process(arr, left, mid)
		+ process(arr, mid + 1, right)
		+ merge(arr, left, mid, right);
}


static int SmallSum(vector<int>& arr) {
	if (arr.size() < 2) {
		return 0;
	}

	return process(arr, 0, arr.size() - 1);
}

static int test(vector<int>& arr) {
	if (arr.size() < 2) {
		return 0;
	}
	int ans = 0;
	int n = arr.size();
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (arr[j] < arr[i]) {
				ans += arr[j];
			}
		}
	}

	return ans;
}

//TEST(SortTest, SmallSumTest) {
//	cout << "small sum test start\n";
//	int max_n = 100;
//	int min_val = 20;
//	int max_val = 50;
//	int test_times = 500000;
//	for (int i = 0; i < test_times; i++) {
//		vector<int> arr1;
//		vector<int> arr2;
//		RandomArr(arr1, max_n, min_val, max_val);
//		CopyArr(arr1, arr2);
//		if (test(arr1) != SmallSum(arr2)) {
//			Print(arr1);
//			Print(arr2);
//			ASSERT_TRUE(false);
//		}
//	}
//	cout << "test success\n";
//	cout << "small sum test end\n\n";
//}