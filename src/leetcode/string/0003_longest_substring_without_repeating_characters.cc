#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;


namespace {

// Custom RandomStr function
static string RandomStr(int max_len) {
    int n = Random::nextInt(0, max_len);
    stringstream ss;
    for (int i = 0; i < n; ++i) {
        char ch = Random::nextInt(0, 128);
        ss << ch;
    }
    return ss.str();
}

} // namespace

/*
    https://leetcode.cn/problems/longest-substring-without-repeating-characters/
    03 无重复字符的最长子串
    给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度
*/

static int lengthOfLongestSubstring(string s) {
    if (s.empty() || s.size() == 1) {
        return s.size();
    }

    int map[128];
    for (int i = 0; i < 128; ++i) {
        map[i] = -1;
    }
    
    int ans = 0;
    int pre = -1;
    int cur = 0;
    for (int i = 0; i < s.size(); ++i) {
        pre = std::max(pre, map[s[i]]);
        cur = i - pre;
        ans = std::max(cur, ans);
        map[s[i]] = i;
    }

    return ans;
}

static int test(string s) {
    if (s.empty() || s.size() == 1) {
        return s.size();
    }

    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        int cur_max = 1;
        set<char> sets;
        sets.insert(s[i]);    
        for (int j = i + 1; j < s.size(); ++j) {
            if (sets.count(s[j]) > 0) {
                break;
            }
            sets.insert(s[j]);
            ++cur_max;
        }

        ans = std::max(ans, cur_max);
    }

    return ans;
}


int main(int argc, char* argv[]) {
    cout << "test start" << endl;
    int test_times = 10000;
    int max_len = 30;

    for (int i = 0; i < test_times; ++i) {
        string str = RandomStr(30);
        if (test(str) != lengthOfLongestSubstring(str)) {
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}