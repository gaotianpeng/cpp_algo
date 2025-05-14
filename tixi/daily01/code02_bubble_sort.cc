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

static void BubbleSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int N = arr.size();
    for (int i = 0; i < N - 1; ++i) {
        for (int j = N - 1; j > i; --j) {
            if (arr[j-1] > arr[j]) {
                Swap(arr, j-1, j);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;
    bool success = true;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr1, arr2;
        RandomArr(arr1, max_n, min, max);
        CopyArray(arr1, arr2);
        BubbleSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        if (!IsEqual(arr1, arr2)) {
            PrintArr(arr1);
            PrintArr(arr2);
            success = false;
            break;
        }
    }

    cout << (success ? "success" : "failed") << endl;
    cout << "test end" << endl;
    return 0;
}