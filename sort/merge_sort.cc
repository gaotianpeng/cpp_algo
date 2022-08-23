#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "random.h"

using namespace std;

static void swap(int& a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void merge(vector<int>& arr, size_t left, size_t mid, size_t right) {
	int n = right - left + 1;
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

	for (size_t  i = 0; i < n; i++) {
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

/*
    for test
*/
static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	Random random;
	int len = (int)(random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(random() * (max_val - min_val)) + min_val;
		out.emplace_back(val);
	}
}

static void CopyArr(const vector<int>& src, vector<int>& dst) {
	dst.clear();
	for (size_t i = 0; i < src.size(); i++) {
		dst.push_back(src[i]);
	}
}

static void Print(const vector<int>& arr) {
	for (auto& elem: arr) {
		cout << elem << " ";
	}
	cout << endl;
}

static bool IsEqual(const vector<int>& arr_a, const vector<int>& arr_b) {
	if (arr_a.size() != arr_b.size()) {
		return false;
	}

	int n = arr_a.size();
	for (int i = 0; i < n; i++) {
		if (arr_a[i] != arr_b[i]) {
			return false;
		}
	}

	return true;
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