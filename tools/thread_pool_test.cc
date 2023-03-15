//
// Created by gtp on 2023/3/15.
//

#include "gtest/gtest.h"
#include <iostream>
#include <chrono>
#include "thread_pool.h"

using namespace std;

void Func(int a) {
    cout << "hello func " << a << endl;
}

struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};

//TEST(ThreadPool, ThreadPoolTest) {
//    ThreadPool thread_pool(4);
//    thread_pool.Start();
//    thread_pool.Run(Func, 3);
//
//    Foo foo;
//    auto f = std::bind(&Foo::print_sum, &foo, std::placeholders::_1, std::placeholders::_1);
//    thread_pool.Run(f, 3, 4);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    thread_pool.Stop();
//}