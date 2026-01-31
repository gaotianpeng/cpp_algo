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
        if (arr_len % 2 != 0) {
            break;
        }
    }
    int odd_times = RandomOdd(arr_len);
    set<int> vals;
    int old_time_val = Random::nextInt(min_val, max_val);
    vals.insert(old_time_val);
    for (int i = 0; i < odd_times; ++i) {
        out.emplace_back(old_time_val);
    }
    arr_len -= odd_times;
    while (arr_len > 0) {
        int even_times = RandomEven(arr_len);
        int even_time_val = Random::nextInt(min_val, max_val);
        while (vals.find(even_time_val) != vals.end()) {
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
            ArrayUtils::printArray(arr);
            success = false;
            break;
        }
    }

    cout << (success ?  "success" : "failed") << endl;
    cout << "test end" << endl;
    return 0;
}