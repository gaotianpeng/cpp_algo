#include <string>
#include <algorithm>
#include "gtest/gtest.h"

using namespace std;

namespace {

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }

        int map[256];
        for (int i = 0; i < 256; i++) {
            map[i] = -1;
        }

        int len = 0;
        int pre = -1;
        int cur = 0;
        for (int i = 0; i != s.size(); i++) {
            pre = std::max(pre, map[s[i]]);
            cur = i - pre;
            len = std::max(len, cur);
            map[s[i]] = i;
        }
        return len;
    }
};

TEST(LeetcodeTest, LongtestPalindromicWithoutRepeatingCharactersTest) {
    string s = "abcabcbb";
    Solution sol;
    cout << sol.lengthOfLongestSubstring(s) << endl;
}

} // namespace