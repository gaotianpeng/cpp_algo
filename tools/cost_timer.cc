#include <iostream>
#include <chrono>
#include <string>
#include "gtest/gtest.h"
using namespace std;

class CostTimer {
public:
    CostTimer(const std::string& msg):t0(std::chrono::high_resolution_clock::now()), msg_(msg) {
        t_last = t0;
    }

    int Cost(const std::string& msg) {
        auto t_cur = std::chrono::high_resolution_clock::now();
        auto nanos = std::chrono::duration_cast<chrono::milliseconds>(t_cur - t_last).count();
        cout << msg_ << ": cost time: " <<  nanos << " ms" << endl;
        t_last = t_cur;

        return nanos;
    }

    int CostAll() {
        auto t_cur = std::chrono::high_resolution_clock::now();
        auto nanos = std::chrono::duration_cast<chrono::milliseconds>(t_cur - t0).count();
        cout << msg_ << ": cost time: " <<  nanos << " ms" << endl;
        return nanos;
    }

    ~CostTimer() {
        auto t_cur = std::chrono::high_resolution_clock::now();
        auto nanos = std::chrono::duration_cast<chrono::milliseconds>(t_cur - t0).count();
        cout << msg_ << ": cost time: " <<  nanos << " ms" << endl;
    }

private:
    std::chrono::high_resolution_clock::time_point  t0;
    std::chrono::high_resolution_clock::time_point  t_last;
    std::string msg_;
};

TEST(ToolsTest, CostTimer) {
    int N = 100000000;
    long double sum = 0;
    CostTimer timer("test");
    for (int i = 0; i < N; ++i) {
        sum += i * 3.14159;
    }
    timer.Cost("current cost1 ");
    for (int i = 0; i < N; ++i) {
        sum += i * 3.14159;
    }
    timer.Cost("current cost2 ");
    for (int i = 0; i < N; ++i) {
        sum += i * 3.14159;
    }
    timer.Cost("current cost2 ");
    for (int i = 0; i < N; ++i) {
        sum += i * 3.14159;
    }

    cout << timer.CostAll() << endl;
}