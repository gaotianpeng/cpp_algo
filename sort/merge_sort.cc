#include <array>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

static void merge(vector<int>& arr, size_t left, size_t mid, size_t right) {
	size_t n = right - left + 1;
	int* helper = new int[n];
	size_t i = 0;
	size_t p1 = left;
	size_t p2 = mid + 1;

	while (p1 <= mid && p2 <= right) {
		helper[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
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

}

static void process(vector<int>& arr, size_t left, size_t right) {
	if (left == right) {
		return;
	}

	size_t mid = left + ((right - left)>>1);
	process(arr, left, mid);
	process(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

static void MergeSort(vector<int>& arr) {
	if (arr.size() < 2) {
		return;
	}

	process(arr, 0, arr.size() - 1);
}

TEST(SortTest, MergeSort) {
	cout << "merge sort test start\n";
	int max_n = 100;
	int min_val = -20;
	int max_val = 30;
	int test_times = 100000;
	for (int i = 0; i < test_times; i++) {
		vector<int> arr1;
		vector<int> arr2;
		RandomArr(arr1, max_n, min_val, max_val);
		CopyArr(arr1, arr2);
		MergeSort(arr1);
		std::sort(arr2.begin(), arr2.end());
		if (!IsEqual(arr1, arr2)) {
			Print(arr1);
			Print(arr2);
			ASSERT_TRUE(false);
		}
	}
	cout << "test success\n";
	cout << "merge sort end\n\n";
}