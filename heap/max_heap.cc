#include <array>
#include <iostream>
#include <numeric>
#include "gtest/gtest.h"
#include "random.h"

using namespace std;
using namespace tools;

class MyMaxHeap {
public:
    MyMaxHeap(int limit):limit_(limit) {
        data_ = new int[limit] {0};
    }

    ~MyMaxHeap() {
        delete [] data_;
    }

    bool IsEmpty() {
        return heap_size_ == 0;
    }

    bool IsFull() {
        return heap_size_ == limit_;
    }

    bool Push(int value) {
        if (IsFull()) {
            return false;
        }

        data_[heap_size_] = value;
        HeapInsert(data_, heap_size_++);
        return true;
    }

    int Pop() {
        if (IsEmpty()) {
            throw;
        }

        int ans = data_[0];
        swap(data_[0], data_[--heap_size_]);
        Heapify(data_, 0, heap_size_);
        return ans;
    }

private:
    void HeapInsert(int* arr, int index) {
        while (arr[index] > arr[(index-1) / 2]) {
            swap(arr[index], arr[(index-1)/2]);
            index = (index - 1)/2;
        }
    }

    void Heapify(int* arr, int index, int heap_size) {
        int left = index * 2 + 1;
        while (left < heap_size) {
            int largest = left + 1 < heap_size && arr[left + 1] > arr[left] ? left + 1 : left;
            largest = arr[largest] > arr[index] ? largest : index;
            if (largest == index) {
                break;
            }
            // index和较大孩子，要互换
            swap(arr[largest], arr[index]);
            index = largest;
            left = index * 2 + 1;
        }
    }

private:
    int limit_  = 0;
    int heap_size_ = 0;
    int* data_ = nullptr;
};

class TestMaxHeap {
public:
    TestMaxHeap(int limit):limit_(limit) {
        data_ = new int[limit] {0};
    }

    ~TestMaxHeap() {
        delete [] data_;
    }

    bool IsEmpty() {
        return size_ == 0;
    }

    bool IsFull() {
        return size_ == limit_;
    }

    bool Push(int value) {
        if (IsFull()) {
            return false;
        }

        data_[size_++] = value;
        return true;
    }

    int Pop() {
        if (IsEmpty()) {
            throw;
        }

        int max_index = 0;
        for (int i = 1; i < size_; ++i) {
            if (data_[i] > data_[max_index]) {
                max_index = i;
            }
        }

        int ans = data_[max_index];
        data_[max_index] = data_[--size_];
        return ans;
    }

private:
    int limit_  = 0;
    int* data_ = nullptr;
    int size_ = 0;
};

//TEST(HeapTest, MaxHeapTest) {
//    std::cout << "max heap test start" << std::endl;
//    int test_times = 500000;
//    MyMaxHeap my_heap(100);
//    TestMaxHeap test_heap(100);
//    int max_val = 100;
//    int min_val = -100;
//    for (int i = 0; i < test_times; ++i) {
//        if (my_heap.IsEmpty() != test_heap.IsEmpty()) {
//            ASSERT_TRUE(false);
//        }
//
//        if (my_heap.IsFull() != test_heap.IsFull()) {
//            ASSERT_TRUE(false);
//        }
//
//        if (my_heap.IsEmpty()) {
//            int val = Random::random(min_val, max_val);
//            if (my_heap.Push(val) != test_heap.Push(val)) {
//                ASSERT_TRUE(false);
//            }
//        } else if (my_heap.IsFull()) {
//            if (my_heap.Pop() != test_heap.Pop()) {
//                ASSERT_TRUE(false);
//            }
//        } else {
//            if (Random::random() < 0.5) {
//                int val = Random::random(min_val, max_val);
//                if (my_heap.Push(val) != test_heap.Push(val)) {
//                    ASSERT_TRUE(false);
//                }
//            } else {
//                if (my_heap.Pop() != test_heap.Pop()) {
//                    ASSERT_TRUE(false);
//                }
//            }
//        }
//    }
//
//    std::cout << "test success" << std::endl;
//    std::cout << "max heap test end" << std::endl;
//}