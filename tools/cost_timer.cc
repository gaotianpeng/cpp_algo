#include <iostream>
#include <chrono>
#include <string>
#include "gtest/gtest.h"
using namespace std;

class CostTimer {
public:
    CostTimer(const std::string& msg = ""): t0_(std::chrono::high_resolution_clock::now()), msg_(msg) {
        t_last_ = t0_;
    }

    int Cost() {
        auto t_now = std::chrono::high_resolution_clock::now();
        auto nanos = std::chrono::duration_cast<chrono::microseconds>(t_now - t_last_).count();
        t_last_ = t_now;
        return nanos;
    }

    int CostAll() {
        auto t_now = std::chrono::high_resolution_clock::now();
        auto nanos = std::chrono::duration_cast<chrono::microseconds>(t_now - t0_).count();
        return nanos;
    }

    auto Reset() {
        t_last_ = t0_ = std::chrono::high_resolution_clock::now();
    }

    ~CostTimer() {
        auto t_now = std::chrono::high_resolution_clock::now();
        auto nanos = std::chrono::duration_cast<chrono::microseconds>(t_now - t0_).count();
        cout << msg_ << " cost time: " <<  nanos << " mm" << endl;
    }

    static std::string MicorToMinute(int micro_s) {
        int ms = micro_s / 1000;
        int total_second = ms / 1000;
        if (ms % 1000 > 500) {
            total_second++;
        }
        int min = total_second / 60;
        int seconds = total_second % 60;
        int milloseconds = ms % 1000;
        return std::to_string(min) + ":" +
               std::to_string(seconds) + ":" + std::to_string(milloseconds);
    }

private:
    std::chrono::high_resolution_clock::time_point  t0_;
    std::chrono::high_resolution_clock::time_point  t_last_;
    std::string msg_;
};

TEST(ToolsTest, CostTimer) {
    int N = 100000000;
    long double sum = 0;
    CostTimer timer("test");
    for (int i = 0; i < N; ++i) {
        sum += i * 3.14159;
    }
    cout << timer.Cost() << endl;
    for (int i = 0; i < N; ++i) {
        sum += i * 3.14159;
    }
    cout << timer.Cost() << endl;
    for (int i = 0; i < N; ++i) {
        sum += i * 3.14159;
    }
    cout << timer.Cost() << endl;
    for (int i = 0; i < N; ++i) {
        sum += i * 3.14159;
    }

    cout << timer.CostAll() << endl;
}