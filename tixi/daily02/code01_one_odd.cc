#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>

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

static int RandomVal(int max, int min) {
    return min + (int) (Math::random() * (double)(max - min));
}

static int RandomOdd(int max) {
    int val = (int)(Math::random()*(double(max))) + 1;
    while (val % 2 == 0) {
        val = (int)(Math::random()*(double(max))) + 1;
    }
    return val;
}

static int RandomEven(int max) {
    int val = (int)(Math::random()*(double(max))) + 1;
    while (val % 2 != 0) {
        val = (int)(Math::random()*(double(max))) + 1;
    }
    return val;
}

static void Swap(vector<int>& arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
    int arr_len = 0;
    while (true) {
        arr_len = RandomVal(0, max_n) + 1;
        if (arr_len % 2 != 0) {
            break;
        }
    }
    int odd_times = RandomOdd(arr_len);
    set<int> vals;
    int old_time_val = RandomVal(max_val, min_val);
    vals.insert(old_time_val);
    for (int i = 0; i < odd_times; ++i) {
        out.emplace_back(old_time_val);
    }
    arr_len -= odd_times;
    while (arr_len > 0) {
        int even_times = RandomEven(arr_len);
        int even_time_val = RandomVal(max_val, min_val);
        while (vals.find(even_time_val) != vals.end()) {
            even_time_val = RandomVal(max_val, min_val);
        }
        vals.insert(even_time_val);
        for (int i = 0; i < even_times; ++i) {
            out.emplace_back(even_time_val);
        }
        arr_len -= even_times;
    }
    int n = out.size();
    for (int i = 0; i < n; ++i) {
        int a = RandomVal(n, 0);
        int b = RandomVal(n, 0);
        Swap(out, a, b);
    }
}

static void PrintArr(const vector<int>& arr) {
    for (auto& elem: arr) {
        cout << elem << " ";
    }
    cout << endl;
}

} // namespace

/*
    从数组arr中找到唯一一个出现了奇数次的数
    注：由外部保证数组中只有一个数出现了奇数次
*/
static int GetOneOdd(vector<int>& arr) {
    if (arr.size() == 0) {
        return -1;
    }
    
    int ans = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        ans ^= arr[i];
    }

    return ans;
}

static int test(vector<int>& arr) {
    if (arr.size() == 0) {
        return -1;
    }
    int ans = 0;
    unordered_map<int, int> map;
    for (int i = 0; i < arr.size(); ++i) {
        int key = arr[i];
        if (map.find(key) != map.end()) {
            int val = map[key];
            map.erase(key);
            map[key] = val + 1;
        } else {
            map[key] = 1;
        }
    }

    for (auto& elem: map) {
        if (elem.second % 2 != 0) {
            ans = elem.first;
            break;
        }
    }
    
    return ans;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = 0;
    int max_n = 30;
    int test_times = 100000;
    bool success = true;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr;
        RandomArr(arr, max_n, min, max);
        if (GetOneOdd(arr) != test(arr)) {
            cout << "test failed" << endl;
            cout << GetOneOdd(arr) << endl;
            cout << test(arr) << endl;
            PrintArr(arr);
            success = false;
            break;
        }
    }

    cout << (success ?  "success" : "failed") << endl;
    cout << "test end" << endl;
    return 0;
}