#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

static int RandomOdd(int max) {
    int val = (int)(Random::nextDouble()*(double(max))) + 1;
    while (val % 2 == 0) {
        val = (int)(Random::nextDouble()*(double(max))) + 1;
    }
    return val;
}

static int RandomEven(int max) {
    int val = (int)(Random::nextDouble()*(double(max))) + 1;
    while (val % 2 != 0) {
        val = (int)(Random::nextDouble()*(double(max))) + 1;
    }
    return val;
}

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
    int arr_len = 0;
    while (true) {
        arr_len = Random::nextInt(0, max_n) + 1;
        if (arr_len < 2) {
            continue;
        }

        if (arr_len % 2 == 0) {
            break;
        }
    }
    int odd_times = RandomOdd(arr_len);
    while (odd_times == arr_len) {
        odd_times = RandomOdd(arr_len);
    }
    set<int> vals;
    int old_time_val = Random::nextInt(min_val, max_val);
    vals.insert(old_time_val);
    for (int i = 0; i < odd_times; ++i) {
        out.emplace_back(old_time_val);
    }

    arr_len -= odd_times;
    odd_times = RandomOdd(arr_len);
    old_time_val = Random::nextInt(min_val, max_val);
    while (vals.count(old_time_val) > 0) {
        old_time_val = Random::nextInt(min_val, max_val);
    }
    vals.insert(old_time_val);
    for (int i = 0; i < odd_times; ++i) {
        out.emplace_back(old_time_val);
    }
    arr_len -= odd_times;
    while (arr_len > 0) {
        int even_times = RandomEven(arr_len);
        int even_time_val = Random::nextInt(min_val, max_val);
        while (vals.count(even_time_val) > 0) {
            even_time_val = Random::nextInt(min_val, max_val);
        }
        vals.insert(even_time_val);
        for (int i = 0; i < even_times; ++i) {
            out.emplace_back(even_time_val);
        }
        arr_len -= even_times;
    }
    int n = out.size();
    for (int i = 0; i < n; ++i) {
        int a = Random::nextInt(0, n);
        int b = Random::nextInt(0, n);
        ArrayUtils::swap(out, a, b);
    }
}

static bool IsEqual(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    if (a.first == b.first && a.second == b.second) {
        return true;
    }
    if (a.first == b.second && a.second == b.first) {
        return true;
    }

    return false;
}

} // namespace

/*
    一个数组中有两种数出现了奇数次，其他数都出现了偶数次，找到这两种数并返回
    注：假设arr中所有数都为正数，如果找不至均返回-1
       传入数组的中数据合理性由外部保证
*/
static std::pair<int, int> GetTwoOdd(vector<int>& arr) {
    int xor1 = arr[0];
    int N = arr.size();
    for (int i = 1; i < N; ++i) {
        xor1 ^= arr[i];
    }

    int rightOne = xor1 & (-xor1);
    int xor2 = 0;
    for (int i = 0; i < N; ++i) {
        if ((arr[i] & rightOne) != 0) {
            xor2 ^= arr[i];
        }
    }

    return {xor2, xor2 ^ xor1};
}

static std::pair<int, int> test(vector<int>& arr) {
    unordered_map<int, int> map;
    for (int i = 0; i < arr.size(); ++i) {
        int key = arr[i];
        if (map.count(key) > 0) {
            int val = map[key];
            map.erase(key);
            map[key] = val + 1;
        } else {
            map[key] = 1;
        }
    }

    vector<int> ans;

    for (auto& elem: map) {
        if (elem.second % 2 != 0) {
            ans.push_back(elem.first);
        }
    }

    return {ans[0], ans[1]};
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
        if (!IsEqual(test(arr), GetTwoOdd(arr))) {
            cout << "test faild" << endl;
            auto ans1 = test(arr);
            auto ans2 = GetTwoOdd(arr);
            cout << ans1.first << ",  " << ans1.second << endl;
            cout << ans2.first << ",  " << ans2.second << endl;
            success = false;
            break;
        }
    }

    cout << (success ? "success" : "failed") << endl;
    cout << "test end" << endl;
    return 0;
}