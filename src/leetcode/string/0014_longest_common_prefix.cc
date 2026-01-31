#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

namespace {

// Custom RandomStr and RandomStrings functions
static string RandomStr(int max_len) {
    int n = Random::nextInt(0, max_len);
    stringstream ss;
    for (int i = 0; i < n; ++i) {
        char ch = 'a' + Random::nextInt(0, 25);
        ss << ch;
    }

    return ss.str();
}

static vector<string> RandomStrings(int max_n, int max_len) {
    int n = Random::nextInt(0, max_n);
    vector<string> ans;
    for (int i = 0; i < n; ++i) {
        ans.emplace_back(RandomStr(max_len));
    }

    return ans;
}

} // namespace

static string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) {
        return "";
    }

    if (strs.size() == 1) {
        return strs[0];
    }

    string cmp = strs[0];
    int ans = cmp.size();
    
    for (int i = 1; i < strs.size(); ++i) {
        int len = std::min(cmp.size(), strs[i].size());
        int index = 0;
        for (int j = 0; j < len; ++j) {
            if (cmp[j] != strs[i][j]) {
                break;
            }
            ++index;
        }
        ans = std:: min(ans, index);
    }

    return cmp.substr(0, ans);
}

static string longestCommonPrefix(const string& str1, const string& str2) {
    int length = min(str1.size(), str2.size());
    int index = 0;
    while (index < length && str1[index] == str2[index]) {
        ++index;
    }
    return str1.substr(0, index);
}

static string test(vector<string>& strs) {
    if (!strs.size()) {
        return "";
    }
    string prefix = strs[0];
    int count = strs.size();
    for (int i = 1; i < count; ++i) {
        prefix = longestCommonPrefix(prefix, strs[i]);
        if (!prefix.size()) {
            break;
        }
    }
    return prefix;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int test_times = 50000;
    int max_n = 100;
    int max_len = 30;
    
    for (int i = 0; i < test_times; ++i) {
        vector<string> strs = RandomStrings(max_n, max_len);
        if (longestCommonPrefix(strs) != test(strs)) {
            cout << "test failed " << endl;
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}
