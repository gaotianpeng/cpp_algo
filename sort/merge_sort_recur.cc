#include <array>
#include <iostream>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

static void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n = right - left + 1;
    int* helper = new int[n];
    int i = 0;
    int p1 = left;
    int p2 = mid + 1;

    while (p1 <= mid && p2 <= right) {
        helper[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
    }

    while( p1 <= mid) {
        helper[i++] = arr[p1++];
    }

    while (p2 <= right) {
        helper[i++] = arr[p2++];
    }

    for (int i = 0; i < n; i++) {
        arr[left + i]  = helper[i];
    }
    delete [] helper;
}

static void process(vector<int>& arr, int left, int right) {
    if (left == right) {
        return;
    }

    int mid = left + ((right - left) >> 1);
    process(arr, left , mid);
    process(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

static void MergeSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    process(arr, 0, arr.size() - 1);
}

//TEST(SortTest, MergeSortRecursiveTest) {
//	cout << "merge sort recursive test start\n";
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