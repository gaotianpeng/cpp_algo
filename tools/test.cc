#include <iostream>
#include <thread>
#include "gtest/gtest.h"

thread_local int counter = 0;

void increment_counter() {
    for (int i = 0; i < 100; ++i) {
        ++counter;
    }
    std::cout << "Thread ID: " << std::this_thread::get_id()
              << ", Counter Value: " << counter << std::endl;
}

//TEST(Test, TestForTest) {
//    std::thread t1(increment_counter);
//    std::thread t2(increment_counter);
//
//    t1.join();
//    t2.join();
//}
