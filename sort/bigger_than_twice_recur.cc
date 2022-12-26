#include <array>
#include <iostream>
#include <vector>
#include <numeric>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

/*
	在一个数组中，对于每个数num，求有多少个后面的数 * 2 依然<num，求总个数
	比如：[3,1,7,0,2]
		3的后面有：1，0
		1的后面有：0
		7的后面有：0，2
		0的后面没有
		2的后面没有
		所以总共有5个
 */
static int merge(vector<int>& arr, int left, int mid, int right) {
	int ans = 0;
	int win_r = mid + 1;
	for (int i = left; i <= mid; ++i) {
		while (win_r <= right && (long)arr[i] > (long)arr[win_r]*2) {
			++win_r;
		}
		ans += win_r - mid - 1;
	}

	int n = right - left + 1;
	int *helper = new int[n];
	int i = 0;
	int p1 = left;
	int p2 = mid + 1;
	while (p1 <= mid && p2 <= right) {
		helper[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
	}

	while (p1 <= mid) {
		helper[i++] = arr[p1++];
	}

	while(p2 <= right) {
		helper[i++] = arr[p2++];
	}

	for (int i = 0; i < n; ++i) {
		arr[left + i] = helper[i];
	}

	delete [] helper;

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

static int BiggerThanTwice(vector<int> arr) {
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
	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if ((long)arr[i] > ((long)arr[j] << 1)) {
				++ans;
			}
		}
	}

	return ans;
}

//TEST(SortTest, BiggerThanTwiceRecurTest) {
//	cout << "bigger than twice recur test start\n";
//	int max_n = 100;
//	int min_val = numeric_limits<int>::min();
//	int max_val = numeric_limits<int>::max();
//	int test_times = 500000;
//	for (int i = 0; i < test_times; i++) {
//		vector<int> arr1;
//		vector<int> arr2;
//		RandomArr(arr1, max_n, min_val, max_val);
//		CopyArr(arr1, arr2);
//		int ans1 = test(arr1);
//		int ans2 = BiggerThanTwice(arr2);
//		if (ans1 != ans2) {
//			cout << ans1 << endl;
//			cout << ans2 << endl;
//			ASSERT_TRUE(false);
//		}
//	}
//	cout << "test success\n";
//	cout << "bigger than twice recur test end\n\n";
//}