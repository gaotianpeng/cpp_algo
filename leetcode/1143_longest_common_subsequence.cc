#include <iostream>
#include <algorithm>
#include <string>
#include "gtest/gtest.h"

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.empty() || text2.empty()) {
            return 0;
        }

        return process(text1, text2, text1.size() - 1, text2.size() - 1);
    }

    int process(string text1, string text2, int i, int j) {
        if (i == 0 && j == 0) {
            return text1[i] == text2[j] ? 1 : 0;
        } else if (i == 0) {
            if (text1[i] == text2[j]) {
                return 1;
            } else {
                return process(text1, text2, i, j - 1);
            }
        } else if (j == 0) {
            if (text1[i] == text2[j]) {
                return 1;
            } else {
                return process(text1, text2, i - 1, j);
            }
        } else {
            int p1 = process(text1, text2, i - 1, j);
            int p2 = process(text1, text2, i, j - 1);
            int p3 =  text1[i] == text2[j]  ? (1 + process(text1, text2, i-1, j-1)) : 0;

            return std::max(p3, std::max(p1, p2));
        }
    }

    int longestCommonSubsequence2(string text1, string text2) {
        if (text1.empty() || text2.empty()) {
            return 0;
        }

        int m = text1.size();
        int n = text2.size();

        // 初始化 dp
        int **dp;
        dp = new int *[m];
        for(int i = 0; i < m; i++)
             dp[i] = new int [n] {0};

        dp[0][0] = text1[0] == text2[0] ? 1 : 0;
        for (int i = 1; i < m; ++i) {
            dp[i][0] = text1[i] == text2[0] ? 1 : dp[i-1][0];
        }

        for (int i = 1; i < n; ++i) {
            dp[0][i] = text1[0] == text2[i] ? 1 : dp[0][i-1];
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                int p1 = dp[i - 1][j];
                int p2 = dp[i][j - 1];
                int p3 =  text1[i] == text2[j]  ? (1 + dp[i-1][j-1]) : 0;
                dp[i][j] = std::max(std::max(p1, p2), p3);
            }
        }

        int ans = dp[m- 1][n- 1];

        // 释放dp
        for(int i = 0; i < m; i++)
            delete [] dp[i];
        delete [] dp;

        return ans;
    }
};
//
//TEST(LeetCodeTest, LongtestCommonSubsequenceTest) {
//    string text1 = "abcde";
//    string text2 = "ace";
//    Solution sol;
//    if ( sol.longestCommonSubsequence(text1, text2) ==
//            sol.longestCommonSubsequence2(text1, text2)) {
//        cout << "test success" << endl;
//    } else {
//        cout << "test faield" << endl;
//    }
//}