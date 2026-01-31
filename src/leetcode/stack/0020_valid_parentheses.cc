#include <iostream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <string>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

namespace {

// Custom RandomStr function
static string RandomStr(int max_n) {
    char chs[] = {'[', ']', '(', ')', '{', '}'};
    int len = Random::nextInt(0, max_n);
    stringstream ss;
    for (int i = 0; i < len; ++i) {
        char ch = chs[Random::nextInt(0, 5)];
        ss << ch; 
    }

    return ss.str();
}

} // namespace

/*
    https://leetcode.cn/problems/valid-parentheses/
    20. 有效的括号
    给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
    有效字符串需满足：
        左括号必须用相同类型的右括号闭合。
        左括号必须以正确的顺序闭合。
        每个右括号都有一个对应的相同类型的左括号。
*/

static bool isValid(string s) {
    if (s.empty()) {
        return true;
    }

    if (s.size() % 2 == 1) {
        return false;
    }

    unordered_map<char, char> bracket_pair = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    stack<char> st;
    for (int i = 0; i < s.size(); ++i) {
        char ch = s[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        } else {
            if (st.empty() || st.top() != bracket_pair[ch]) {
                return false;
            } else {
                st.pop();
            }
        }
    }

    return st.empty(); 
}

static bool test(string s) {
    if (s.empty()) {
        return true;
    }

    if (s.size() % 2 == 1) {
        return false;
    }

    while (s.find("()") != std::string::npos || 
            s.find("[]") != std::string::npos || 
            s.find("{}") != std::string::npos) {
        if (s.find("()") != std::string::npos) {
            s = s.replace(s.find("()"), 2, "");
        }

        if (s.find("[]") != std::string::npos) {
            s = s.replace(s.find("[]"), 2, "");
        }

        if (s.find("{}") != std::string::npos) {
            s = s.replace(s.find("{}"), 2, "");
        }
    }

    return s.empty();
}

int main(int argc, char* argv[]) {
    cout << "test start...." << endl;

    int test_times = 10000;
    int max_n = 30;
    for (int i = 0; i < test_times; ++i) {
        string str = RandomStr(max_n);
        if (isValid(str) != test(str)) {
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}