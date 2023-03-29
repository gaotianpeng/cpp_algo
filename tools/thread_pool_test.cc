//
// Created by gtp on 2023/3/15.
//

#include "gtest/gtest.h"
#include <iostream>
#include <chrono>
#include <set>
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

void sampleFunction() {
    cout << "endl" << endl;
    throw std::runtime_error("An error occurred.");
}

std::thread::id PrintThreadId() {
    return std::this_thread::get_id();
}


//TEST(ThreadPool, ThreadPoolTest) {
//    ThreadPool pool;
//    pool.Start();
//    pool.Run(&sampleFunction);
//    std::this_thread::sleep_for(std::chrono::seconds (5));
//
//    int i = 10000;
//    std::set<std::thread::id> idsets;
//    std::vector<std::shared_ptr<std::future<std::thread::id>>> vecs;
//
//    while(i >= 0) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//        std::shared_ptr<std::future<std::thread::id>> id = pool.Run(&PrintThreadId);
//        vecs.push_back(id);
//    }
//
//    for (int j = 0; j < vecs.size(); ++j) {
//        auto id = vecs[j]->get();
//        idsets.insert(id);
//    }
//
//    cout << idsets.size() <<endl;
//}