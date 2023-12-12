#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
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

class TestHeap {
public:
    TestHeap(int limit):limit_(limit) {
    }

    ~TestHeap() {
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return size_ == limit_;
    }

    void push(int val) {
        if (full()) {
            throw logic_error("heap is full");
        }
        data_.emplace_back(val);
        ++size_;
    }

    int pop() {
        if (empty()) {
            throw logic_error("heap is empty");
        }
        int max_index = 0;
        for (int i = 0; i < size_; ++i) {
            max_index = data_[max_index] < data_[i] ? i : max_index;
        }
        int ans = data_[max_index];
        for (int i = max_index; i < size_ - 1; ++i) {
            data_[i]  = data_[i + 1];
        }
        --size_;
        return ans;
    }


private:
    int limit_;
    int size_ = 0;
    vector<int> data_;
};

// 大根堆
class HeapMap {
public:
    HeapMap(int limit):limit_(limit) {
        data_ = new int[limit];
    }

    ~HeapMap() {
        delete [] data_;
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return size_ == limit_;
    }

    void push(int val) {
        if (full()) {
            throw logic_error("Heap is full!!!");
        }

        data_[size_] = val; 
        heap_insert(size_++, data_);
    }

    int pop() {
        if (empty()) {
            throw logic_error("Heap is empty!!!");
        }

        int ret = data_[0];
        swap(0, size_ - 1);
        heapify(0, data_, --size_);
        return ret;
    }

private:
    void heapify(int index, int* arr, int heap_size) {
        int left = 2 * index + 1;
        while (left < heap_size) {
            int larger = left + 1 < heap_size ? 
                (arr[left] < arr[left + 1] ? left + 1: left) : left;
            if (larger == index) {
                break;
            }

            swap(larger, index);
            index = larger;
            left = 2 * index + 1;
        }

    }

    void heap_insert(int index, int* arr) {
        while (arr[index] > arr[(index - 1)/2]) {
            swap(index, (index - 1) /2);
        }
    }

    void swap(int i, int j) {
        if (i == j) {
            return;
        }

        int tmp = data_[i];
        data_[i] = data_[j];
        data_[j] = tmp;
    }

private:
    int limit_ = 0;
    int size_ = 0;
    int* data_ = nullptr;
};
} // namespace


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int value = 1000;
    int limit = 100;
    int test_times = 100000;
    bool success = true;

    for (int i = 0; i < test_times; ++i) {
        int cur_limit = (int) (Math::random() * limit) + 1;
        HeapMap my(cur_limit);
        TestHeap test(cur_limit);
        int curOpTimes = (int) (Math::random() * limit);
        for (int j = 0; j < curOpTimes; j++) {
            if (my.empty() != test.empty()) {
                success = false;
                break;
            }
            if (my.full() != test.full()) {
                success = false;
                break;
            }
            if (my.empty()) {
                int curValue = (int) (Math::random() * value);
                my.push(curValue);
                test.push(curValue);
            } else if (my.full()) {
                if (my.pop() != test.pop()) {
                    success = false;
                    break;
                }
            } else {
                if (Math::random() < 0.5) {
                    int curValue = (int) (Math::random() * value);
                    my.push(curValue);
                    test.push(curValue);
                } else {
                    if (my.pop() != test.pop()) {
                        success = false;
                        break;
                    }
                }
            }
        }

        if (!success) {
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}