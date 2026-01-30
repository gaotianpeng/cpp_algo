#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <string>
using namespace std;

/*
    for test
*/
namespace {

class Math {
public:
    static double random() {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
};

static int RandomVal(int max) {
    return int(Math::random() * (double)max);
}

static std::string RandomString(int poss, int max_len) {
    int len = RandomVal(max_len);
    std::string ans;
    for (int i = 0; i < len; ++i) {
        char ch = 'a' + RandomVal(poss);
        ans.push_back(ch);
    }
    return ans;
}

} // namespace

/*
    leetcode 28 找出字符串中第一个匹配项的下标
        给你两个字符串haystack和needle. 请你在haystack字符串中找出needle字符串的第一个匹配项的下标
        如果needle不是haystack 的一部分，则返回-1
    https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
*/
static void NextArray(std::string str, vector<int>& next) {
    if (str.length() == 1) {
        next.push_back(-1);
        return;
    }

    next.resize(str.size());
    next[0] = -1;
    next[1] = 0;
    int i = 2;
    int cn = 0;
    int n = next.size();
    while (i < n) {
        if (str[i-1] == str[cn]) {
            next[i++] = ++cn;
        } else if (cn > 0) {
            cn = next[cn];
        } else {
            next[i++] = 0;
        }
    }
}

static int kmp(std::string haystack, std::string needle) {
    if (haystack.size() == 0 || needle.size() == 0 || haystack.length() < needle.length()) {
        return -1;
    }

    vector<int> next;
    NextArray(needle, next);
    int x = 0;
    int y = 0;
    while (x < haystack.size() && y < needle.size()) {
        if (haystack[x] == needle[y]) {
            ++x;
            ++y;
        } else if (next[y] == -1) {
            ++x;
        } else {
            y = next[y];
        }
    }

    return y == needle.size() ? x - y : -1;
}

static int test(std::string haystack, std::string needle) {
    if (haystack.size() == 0 || needle.size() == 0 || haystack.length() < needle.length()) {
        return -1;
    }

    int j = 0;
    for (int i = 0; i <= haystack.length() - needle.length(); ++i) {
        int start = i;
        for (j = 0; j < needle.length(); ++j) {
            if (haystack[start] == needle[j]) {
                ++start;
            } else {
                break;
            }
        }
        if (j == needle.length()) {
            return i;
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int test_times = 100000;
    int max_val = 100;
    int poss = 5;
    int max_len = 30;
    for (int i = 0; i < test_times; ++i) {
        string hay = RandomString(poss, max_len);
        string needle = RandomString(poss, max_len);

        if (kmp(hay, needle) != test(hay, needle)) {
            cout << kmp(hay, needle) << endl;
            cout << test(hay, needle) << endl;
            cout << hay << endl;
            cout << needle << endl;
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}