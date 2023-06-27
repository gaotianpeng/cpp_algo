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

static void merge(vector<int>& arr, int left, int mid, int right) {
    int n = right - left + 1;
    int* helper = new int[n];
    int left_index = left;
    int right_index = mid + 1;
    int index = 0;
    while (left_index <= mid && right_index <= right) {
        helper[index++] = arr[left_index] <= arr[right_index] ? arr[left_index++]
            : arr[right_index++];
    }
    while (left_index <= mid) {
        helper[index++] = arr[left_index++];
    }
    while (right_index <= right) {
        helper[index++] = arr[right_index++];
    }
    for (int i = 0; i < n; ++i) {
        arr[left + i] = helper[i];
    }
    delete [] helper;
}

static void MergeSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int merge_size = 1;
    int n = arr.size();

    while (merge_size < n) {
        int left = 0;
        while (left < n) {
            if (n - left < merge_size) {
                break;
            }

            int mid = left + merge_size - 1;
            int right = mid + std::min(merge_size, n - mid - 1);
            merge(arr, left, mid, right);
            left = right + 1;
        }

        if (merge_size > n / 2) {
            break;
        }

        merge_size <<= 1;
    }
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr1, arr2;
        RandomArr(arr1, max_n, min, max);
        CopyArray(arr1, arr2);
        MergeSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        if (!IsEqual(arr1, arr2)) {
            PrintArr(arr1);
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;

    return 0;
}