#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

/*
    for test
*/
namespace {

class Math {
public:
    static double random() {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
};

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Math::random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Math::random() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
}

static void CopyArray(const vector<int>& src, vector<int>& dst) {
	for (int i = 0; i < src.size(); i++) {
        dst.push_back(src[i]);
	}
}

static void PrintArr(const vector<int>& arr) {
    for (auto& elem: arr) {
        cout << elem << " ";
    }
    cout << endl;
}

static bool IsEqual(const vector<int>& arr1, const vector<int>& arr2) {
    if (arr1.size() != arr2.size()) {
        return false;
    }

    for (int i = 0; i < arr1.size(); ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

static void Swap(vector<int>& arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

} // namespace

/*
选择排序
    arr[0～N-1]范围上，找到最小值所在的位置，然后把最小值交换到0位置
    arr[1～N-1]范围上，找到最小值所在的位置，然后把最小值交换到1位置
    arr[2～N-1]范围上，找到最小值所在的位置，然后把最小值交换到2位置
    …
    arr[N-1～N-1]范围上，找到最小值位置，然后把最小值交换到N-1位置
*/
static void SelectSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Swap(arr, min_idx, i);
        }
    }
}

/*
    选择排序
        arr[0～N-1]范围上，找到最大值所在的位置，然后把最大值交换到 N-1 位置
        arr[0～N-2]范围上，找到最大值所在的位置，然后把最大值交换到 N-2 位置
        arr[0～N-3]范围上，找到最磊值所在的位置，然后把最大值交换到 M-3 位置
        …
        arr[0~0] 范围上，找到最大值位置，然后把最大值交换到 0 位置
*/
static void SelectSort1(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    for (int i = n - 1; i >= 0; --i) {
        int max_idx = i;
        for (int j = 0; j < i; j++) {
            max_idx = arr[j] > arr[max_idx] ? j : max_idx;
        }
        if (max_idx != i) {
            Swap(arr, i, max_idx);
        }
    }
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr1, arr2, arr3;
        RandomArr(arr1, max_n, min, max);
        CopyArray(arr1, arr2);
        CopyArray(arr1, arr3);
        SelectSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        SelectSort1(arr3);
        if (!IsEqual(arr1, arr2)) {
            PrintArr(arr1);
            PrintArr(arr2);
            cout << "test failed" << endl;
            break;
        }
        if (!IsEqual(arr1, arr3)) {
            PrintArr(arr1);
            PrintArr(arr3);
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;

    return 0;
}