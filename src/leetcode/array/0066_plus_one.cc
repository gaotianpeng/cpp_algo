#include <iostream>
#include <random>
#include <vector>
#include <deque>

using namespace std;


namespace {
class Math {
public:
    static double random() {
        static random_device rd;
        static default_random_engine engine(rd());
        static uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
};

static int RandomVal(int min, int max) {
    return (int)(Math::random()*(max - min + 1)) + min;
}

static vector<int> RandomArr(int max_len, int min, int max) {
    int len = RandomVal(0, max_len);
    vector<int> ans;
    for (int i = 0; i < len; ++i) {
        ans.emplace_back(RandomVal(min, max));
    }

    return ans;
}

static bool IsEqual(const vector<int>& nums1, const vector<int>& nums2) {
    if (nums1.size() != nums2.size()) {
        return false;
    }

    for (int i = 0; i < nums1.size(); ++i) {
        if (nums1[i] != nums2[i]) {
            return false;
        }
    }

    return true;
}

} // namespace

/*
    https://leetcode.cn/problems/plus-one/
    66 加一
        给定一个由 整数 组成的 非空 数组所表示的非负整数，在该数的基础上加一。
        最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。
        你可以假设除了整数 0 之外，这个整数不会以零开头

    输入：digits = [1,2,3]
    输出：[1,2,4]
    解释：输入数组表示数字 123
*/
static vector<int> plusOne(vector<int>& digits) {
    vector<int> ans = digits;

    int n = digits.size();
    for (int i = n - 1; i >= 0; --i) {
        if (ans[i] != 9) {
            ++ans[i];
            for (int j = i + 1; j < n; ++j) {
                ans[j] = 0;
            }
            return ans;
        }
    }

    vector<int> ans1(n+1);
    ans1[0] = 1;
    return ans1;
}

static vector<int> test(vector<int>& digits) {
    int carry = 1;
    vector<int> ans = digits;
    int n = digits.size();

    for (int i = n - 1; i >= 0; --i) {
        int sum = ans[i] + carry;
        carry = sum / 10;
        ans[i] = sum % 10;
    }

    if (carry == 1) {
        vector<int> ans(n+1);
        ans[0] = 1;
        return ans;
    } else {
        return ans;
    }
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int test_times = 50000;
    int min = 0;
    int max = 9;
    int max_len = 30;

    for (int i = 0; i < test_times; ++i) {
        vector<int> digits = RandomArr(max_len, min, max);
        vector<int> ans1 = plusOne(digits);
        vector<int> ans2 = test(digits);

        if (!IsEqual(ans1, ans2)) {
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}