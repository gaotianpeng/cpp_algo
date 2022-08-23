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

static void BubbleSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    for (int i = n-1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

static void test(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    size_t n = arr.size();
    for (int i = n - 1; i > 0; --i) {
        size_t max_idx = i;
        for (int j = 0; j < i; j++) {
            if (arr[max_idx] < arr[j]) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swap(arr[max_idx], arr[i]);
        }
    }
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

TEST(SortTest, BubbleSort) {
    cout << "bubble sort test start\n";
    int max_n = 100;
    int min_val = -20;
    int max_val = 30;
    int test_times = 100000;
    for (int i = 0; i < test_times; i++) {
        vector<int> arr1;
        vector<int> arr2;
        vector<int> arr3;
        RandomArr(arr1, max_n, min_val, max_val);
        CopyArr(arr1, arr2);
        CopyArr(arr1, arr3);
        BubbleSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        test(arr3);
        if (!IsEqual(arr2, arr3)) {
            Print(arr2);
            Print(arr3);
            ASSERT_TRUE(false);
        }
        if (!IsEqual(arr1, arr2)) {
            Print(arr1);
            Print(arr2);
            ASSERT_TRUE(false);
        }
    }
    cout << "test success\n";
    cout << "bubble sort end\n";
}