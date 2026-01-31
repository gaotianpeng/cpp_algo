#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "common/test_utils.h"
using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

static std::string RandomString(int poss, int max_len) {
    int len = Random::nextInt(0, max_len);
    std::string ans;
    for (int i = 0; i < len; ++i) {
        char ch = 'a' + Random::nextInt(0, poss - 1);
        ans.push_back(ch);
    }
    return ans;
}

} // namespace

/*
    nowcoder NC17 最长回文子串
    假设字符串str长度为N，想返回最长回文子串的长度, 时间复杂度O(N)
*/

static std::string manacherStr(std::string str) {
    int n = str.length();
    string ans;
    ans.resize(2*n+1);
    
    int index = 0;
    for (int i = 0; i < ans.size(); ++i) {
        ans[i] = (i&1) == 0 ? '#': str[index++];
    }

    return ans;
}

static int manacher(std::string str) {
    if (str.empty()) {
        return 0;
    }

    string mstr = manacherStr(str);
    vector<int> parr;
    parr.resize(mstr.size());

    int center = -1;
    int right = -1;

    int ans = 0;
    for (int i = 0; i < mstr.size(); i++) {
        parr[i] = right > i ? std::min(right - i, parr[2*center - i]) : 1;
        while (i + parr[i] < mstr.size() && i - parr[i] > -1) {
            if (mstr[i + parr[i]] == mstr[i - parr[i]]) {
                parr[i]++;
            } else {
                break;
            }
        }

        if (i + parr[i] > right) {
            right = i + parr[i];
            center = i;
        }
        
        ans = std::max(ans, parr[i]);
    }

    return ans - 1;
}

static int test(std::string str) {
    if (str.empty()) {
        return 0;
    }
    
    string mstr = manacherStr(str);
    int ans = 0;
    for (int i = 0; i < mstr.size(); ++i) {
        int left = i;
        int right = i;
        while (left >= 0 && right < mstr.size()) {
            if (mstr[left] == mstr[right]) {
                --left;
                ++right;
            } else {
                break;
            }
        }
        ans = std::max(ans, right - left - 1);
    }

    return ans / 2;
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int test_times = 100000;
    int max_val = 100;
    int max_len = 30;
    int poss = 6;
    for (int i = 0; i < test_times; ++i) {
        std::string str = RandomString(poss, max_len);
        if (manacher(str) != test(str)) {
            cout << "test faield" << endl;
            cout << str << endl;
            cout << manacher(str) << endl;
            cout << test(str) << endl;
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}