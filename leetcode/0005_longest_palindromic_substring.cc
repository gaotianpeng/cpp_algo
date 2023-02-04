#include "gtest/gtest.h"
#include <string>
using namespace std;

namespace {

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.empty()) {
            return 0;
        }

        return process(s, 0, s.size() - 1);
    }

    int process(const string& s, int left, int right) {
        if (left == right) {
            return 1;
        }

        if (left == right - 1) {
            return 2;
        }

        int p1 = process(s, left + 1, right - 1);
        int p2 = process(s, left, right - 1);
        int p3 = process(s, left + 1, right);
        int p4 = s[left] != s[right] ? 0 : (2 + process(s, left + 1, right - 1));

        return std::max(std::max(p1, p2), std::max(p3, p4));
    }

    int longestPalindromeSubseq2(string s) {
        if (s.empty()) {
            return 0;
        }

        int n = s.size();
        int** dp = new int* [n];
        for (int i = 0; i < n; ++i) {
            dp[i] = new int[n] {0};
        }

        dp[n-1][n-1] = 1;
        for (int i = 0; i < n - 1; i++) {
            dp[i][i] = 1;
            dp[i][i+1] = s[i] == s[i+1] ? 2 : 1;
        }

        for (int left = n - 3; left >= 0; --left) {
            for (int right = left + 2; right < n; ++right) {
                dp[left][right] = std::max(dp[left][right - 1], dp[left + 1][right]);
                if (s[left] == s[right]) {
                   dp[left][right] = std::max(dp[left][right], 2 + dp[left+1][right-1]);
                }
            }
        }

        int ans = dp[0][n-1];
        for (int i = 0; i < n; ++i) {
            delete [] dp[i];
        }

        delete [] dp;
        return ans;
    }
};

//TEST(LeetcodeTest, LongestPalindromeSubseqTest) {
//    string s = "bbbab";
//    Solution sol;
//    if (sol.longestPalindromeSubseq(s) == sol.longestPalindromeSubseq2(s)) {
//        cout << "LongestPalindromeSubseqTest success" << endl;
//    } else {
//        cout << "LongestPalindromeSubseqTest failed" << endl;
//    }
//}

} // namespace
