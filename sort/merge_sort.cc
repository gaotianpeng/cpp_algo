#include <array>
#include <iostream>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

static void merge(vector<int>& arr, int left, int mid, int right) {
	int n = right - left + 1;
	int* helper = new int[n];
	int i = 0;
	int p1 = left;
	int p2 = mid + 1;

	while (p1 <= mid && p2 <= right) {
		helper[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
	}

	while (p1 <= mid) {
		helper[i++] = arr[p1++];
	}

	while (p2 <= right) {
		helper[i++] = arr[p2++];
	}

	for (int i = 0; i < n; i++) {
		arr[left + i] = helper[i];
	}

	delete [] helper;
}

static void MergeSort(vector<int>& arr) {
	if (arr.size() < 2) {
		return;
	}

	int n = arr.size();
	int merge_size = 1;
	while (merge_size < n) {
		int left = 0;
		while (left < n) {
			if (merge_size >= n - left) {
				break;
			}

			int mid = left + merge_size - 1;
			int right = mid + std::min(merge_size, n - mid - 1);
			merge(arr, left, mid, right);
			left = right + 1;
		}

		// 防止溢出
		if (merge_size > n/2) {
			break;
		}
		merge_size <<= 1;
	}
}
//
//TEST(SortTest, MergeSortTest) {
//	cout << "merge sort test start\n";
//	int max_n = 100;
//	int min_val = -20;
//	int max_val = 30;
//	int test_times = 500000;
//	for (int i = 0; i < test_times; i++) {
//		vector<int> arr1;
//		vector<int> arr2;
//		RandomArr(arr1, max_n, min_val, max_val);
//		CopyArr(arr1, arr2);
//		MergeSort(arr1);
//		std::sort(arr2.begin(), arr2.end());
//		if (!IsEqual(arr1, arr2)) {
//			Print(arr1);
//			Print(arr2);
//			ASSERT_TRUE(false);
//		}
//	}
//	cout << "test success\n";
//	cout << "merge sort end\n\n";
//}