#include <array>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

static int merge(vector<int>& arr, int left, int mid, int right) {
	int n = right - left + 1;
	int* helper = new int[n];
	int ans = 0;
	int p1 = mid;
	int p2 = right;
	int i = n-1;

	while (p1 >= left && p2 > mid) {
		ans += arr[p1] > arr[p2] ? (p2 - mid) : 0;
		helper[i--] = arr[p1] > arr[p2] ? arr[p1--] : arr[p2--];
	}

	while (p1 >= left) {
		helper[i--] = arr[p1--];
	}

	while (p2 > mid) {
		helper[i--] = arr[p2--];
	}

	for (size_t i = 0; i < n; ++i) {
		arr[left + i] = helper[i];
	}

	delete[] helper;

	return ans;
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

static int ReversePair(vector<int> arr) {
	if (arr.size() < 2) {
		return 0;
	}

	return process(arr, 0, arr.size() - 1);
}

static int test(vector<int> arr) {
	if (arr.size() < 2) {
		return 0;
	}

	int ans = 0;
	int n = arr.size();
	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (arr[i] > arr[j]) {
				ans += 1;
			}
		}
	}

	return ans;
}

//TEST(SortTest, ReversePairTest) {
//	cout << "reverse pair test start\n";
//	int max_n = 100;
//	int min_val = 20;
//	int max_val = 50;
//	int test_times = 500000;
//	for (int i = 0; i < test_times; i++) {
//		vector<int> arr1;
//		vector<int> arr2;
//		RandomArr(arr1, max_n, min_val, max_val);
//		CopyArr(arr1, arr2);
//		int ans1 = ReversePair(arr1);
//		int ans2 = test(arr2);
//		if (ans1 != ans2) {
//			cout << ans1 << endl;
//			cout << ans2 << endl;
//			ASSERT_TRUE(false);
//		}
//	}
//	cout << "test success\n";
//	cout << "reverse pair test end\n\n";
//}