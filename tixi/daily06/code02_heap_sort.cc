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
	int len = (int)(Math::random() * (max_n + 1));
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

static void Heapify(vector<int>& arr, int index, int heap_size) {
    int left = index * 2 + 1;
    while (left < heap_size) {
        int larger = left + 1 < heap_size && arr[left] < arr[left + 1] ? 
            left + 1 : left;
        
        larger = arr[larger] > arr[index] ? larger: index;
        if (larger == index) {
            break;
        }

        Swap(arr, index, larger);
        index = larger;
        left = index * 2 + 1;
    }
}

static void HeapInsert(vector<int>& arr, int index) {
    while (arr[index] > arr[(index - 1) / 2]) {
        Swap(arr, index, (index - 1)/2);
        index = (index - 1) / 2;
    }
}

static void HeapSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int heap_size = arr.size();
    for (int i = 0; i < heap_size; ++i) {
        HeapInsert(arr, i);
    }

    while (heap_size > 0) {
        Heapify(arr, 0, heap_size);
        Swap(arr, 0, --heap_size);
    }
}

static void HeapSort2(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    for (int i = n - 1; i >= 0; --i) {
        Heapify(arr, i, n);
    }
    int heap_size = n;
    Swap(arr, 0, --heap_size);
    while (heap_size > 0) {
        Heapify(arr, 0, heap_size);
        Swap(arr, 0, --heap_size);
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
        HeapSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        HeapSort2(arr3);
        if (!IsEqual(arr1, arr2)) {
            PrintArr(arr1);
            PrintArr(arr2);
            cout << "test failed" << endl;
            break;
        }
        if (!IsEqual(arr2, arr3)) {
            PrintArr(arr2);
            PrintArr(arr3);
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}