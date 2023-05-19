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
		int val = (int)(Math::random() * (max_val - min_val)) + min_val;
		out.emplace_back(val);
	}
}

static int RandomVal(int min_val, int max_val) {
    return (int)(Math::random() * (max_val - min_val)) + min_val;
}


static void PrintArr(const vector<int>& arr) {
    for (auto& elem: arr) {
        cout << elem << " ";
    }
    cout << endl;
}

} // namespace

/*
    在一个有序数组中，找<=某个数最右侧的位置
*/
static int RightNearestIndex(vector<int>& arr, int target) {
    if (arr.size() == 0) {
        return -1;
    }
    int ans = -1;
    int n = arr.size();
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        if (arr[mid] <= target) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return ans;
}

static int test(vector<int>& arr, int target) {
    if (arr.size() == 0) {
        return -1;
    }

    int ans = -1;
    int n = arr.size();
    for (int i = n - 1; i >= 0; --i) {
        if (arr[i] <= target) {
            ans = i;
            break;
        }
    }
    return ans;
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr;
        RandomArr(arr, max_n, min, max);
        std::sort(arr.begin(), arr.end());
        int target = RandomVal(min, max);
        if (RightNearestIndex(arr, target) != test(arr, target)) {
            cout << "test failed" << endl;
            PrintArr(arr);
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}