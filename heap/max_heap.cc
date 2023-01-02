#include <array>
#include <iostream>
#include <vector>
#include <numeric>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

class MyMaxHeap {
public:
    MyMaxHeap(int limit):limit_(limit) {
    }

    bool IsEmpty() {
        return true;
    }

    bool IsFull() {
        return true;
    }

    void Push(int value) {
    }

    int Pop() {
        return -1;
    }


private:
    int limit_;
};

TEST(HeapTes, MaxHeapTest) {
    std::cout << "max heap test start" << std::endl;

    std::cout << "test success" << std::endl;
    std::cout << "max heap test end" << std::endl;
}