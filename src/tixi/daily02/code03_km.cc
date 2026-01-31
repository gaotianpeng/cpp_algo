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

// k < m, m > 1
static void RandomKM(int max_n, int& k, int& m) {
    m = Random::nextInt(2, max_n);
    while (m == max_n) {
        m = Random::nextInt(2, max_n);
    }

    k = Random::nextInt(0, std::min(m - 1, max_n - m));
    while (k == m) {
        k = Random::nextInt(0, std::min(m - 1, max_n - m));
    }
}

static void RandomArr(vector<int>& out, int max, int min, int k, int m) {
    int times_m = Random::nextInt(2, m);
    set<int> vals;
    int val = Random::nextInt(min, max);
    vals.insert(val);
    for (int i = 0; i < k; ++i) {
        out.emplace_back(val);
    }

    while (times_m > 0) {
        val = Random::nextInt(min, max);
        while (vals.count(val) > 0) {
            val = Random::nextInt(min, max);
        }
        vals.insert(val);
        for (int i = 0; i < m; ++i) {
            out.emplace_back(val);
        }
        --times_m;
    }

    int n = out.size();
    for (int i = 0; i < n; ++i) {
        int index1 = Random::nextInt(0, n - 1);
        int index2 = Random::nextInt(0, n - 1);
        ArrayUtils::swap(out, index1, index2);
    }
}

} // namespace

/*
    一个数组中有一种数出现K次, 其他数都出现了M次，M > 1, K < M. 找到, 出现了K次的数
    要求: 额外空间复杂度O(1)，时间复杂度O(N)
 */
static int GetKM(vector<int> arr, int k, int m) {
    int ans = 0;
    constexpr int n_bits= sizeof(int) * 8;
    int helper[n_bits] = {0};
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n_bits; ++j) {
            helper[j] += ((arr[i] >> j) & 1);
        }
    }
    for (int i = 0; i < n_bits; ++i) {
        ans |= (((helper[i] %= m) != 0 ? 1 : 0) << i);
    }

    return ans;
}

static int test(const vector<int>& arr, int k, int m) {
    unordered_map<int, int> map;
    for (auto& elem: arr) {
        if (map.count(elem) > 0) {
            int count = map[elem];
            map.erase(elem);
            map[elem] = count + 1;
        } else {
            map[elem] = 1;
        }
    }

    int ans = 0;
    for (auto& elem: map) {
        if (elem.second == k) {
            return elem.first;
        }
    }

    return ans;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = 0;
    int max_m = 30;
    int test_times = 10;
    bool success = true;
    for (int i = 0; i < test_times; ++i) {
        vector<int> arr;
        int k = 0;
        int m = 0;
        RandomKM(max_m, k, m);
        RandomArr(arr, max, min, k, m);
        if (test(arr, k, m) != GetKM(arr, k, m)) {
            cout << "test faield" << endl;
            ArrayUtils::printArray(arr);
            cout << k << endl;
            cout << m << endl;
            cout << test(arr, k, m) << endl;
            cout << GetKM(arr, k, m) << endl;
            break;
        }
    }

    cout << (success ? "success" :"failed") << endl;
    cout << "test end" << endl;
    return 0;
}