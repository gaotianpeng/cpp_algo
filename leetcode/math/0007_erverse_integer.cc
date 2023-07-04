#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <string>

using namespace std;

namespace {

class Math {
public:
    static double random() {
        std::random_device rd;
        std::default_random_engine engine(rd());
        std::uniform_real_distribution<> distribution(0.0, 1.0);
        
        return distribution(engine);
    } 
};

static int RandomVal(int min, int max) {
    return (int)(Math::random() * (max - min + 1)) + min;
}

} // namespace

/*
    https://leetcode.cn/problems/reverse-integer/  
    7 整数反转
    给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
    如果反转后整数超过 32 位的有符号整数的范围 [−2^31,  2^31 − 1] ，就返回 0。
    假设环境不允许存储 64 位整数（有符号或无符号）。
*/

static int reverse(int x) {
    bool neg = ((x >> 31) & 1) == 1;
    x = neg ? x : -x;
    int int_min = std::numeric_limits<int>::min();

    int m = int_min / 10;
    int o = int_min % 10;

    int res = 0;
    while (x != 0) {
        if (res < m || (res == m && x / 10 < o)) {
            return 0;
        }
        res = res * 10 + x % 10;
        x = x / 10;
    }

    return neg? res : std::abs(res);
}

static int test(int num) {
    int reversed = 0;
    while (num != 0) {
        int digit = num % 10;   
        if (reversed > std::numeric_limits<int>::max() / 10 || 
                (reversed == std::numeric_limits<int>::max() / 10 && digit > 7)) {
            return 0;
        }
            
        if (reversed < std::numeric_limits<int>::min() / 10 || 
                (reversed == std::numeric_limits<int>::min() / 10 && digit < -8)) {
            return 0;
        }
            
        reversed = reversed * 10 + digit;
        num /= 10;
    }

    return reversed;
}


int main(int argc, char* argv[]) {
    cout << "test start ..." << endl;
    int test_times = 50000;
    int min = std::numeric_limits<int>::min();
    int max = std::numeric_limits<int>::max();

    for (int i = 0; i < test_times; ++i) {
        int x = RandomVal(min, max);
        int ans1 = reverse(x);
        int ans2 = test(x);

        if (ans1 != ans2) {
            cout << "test failed " << std::endl;
            break;
        }
    }

    cout << "test end" << endl;

    return 0;
}