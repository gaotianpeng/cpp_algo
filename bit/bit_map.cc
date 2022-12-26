#include <iostream>
#include <limits>
#include <map>
#include "gtest/gtest.h"
#include "common.h"
using namespace std;
using namespace tools;

class BitMap {
public:
    BitMap(int max) {
        bits = new long[(max + 64) >> 6];
    }

    ~BitMap() {
        delete [] bits;
    }

    void Add(int num) {
        bits[num >> 6] |= (1L << (num & 63));
    }

    void Delete(int num) {
        bits[num >> 6] &= ~(1L << (num & 63));
    }
    
    bool Contains(int num) {
        return (bits[num >> 6] & (1L << (num & 63))) != 0;
    }
private:
    long* bits = nullptr;
};

class BitMapTest {
public:
    BitMapTest(int max) {
    }

    void Add(int num) {
        set_.insert(num);
    }

    void Delete(int num) {
        set_.erase(num);
    }

    bool Contains(int num) {
        return set_.find(num) != set_.end();
    }

private:
    std::set<int> set_;
};

//TEST(BitTest, BitMapTest) {
//    cout << "bit map test start\n";
//    int test_times = 5000000;
//    int max_val = 1000;
//    BitMap bit_map1(max_val);
//    BitMapTest bit_map2(max_val);
//    for (int i = 0; i < test_times; ++i) {
//        int num = RandomVal(0, max_val);
//        double decide = RandomVal(0.0, 1.0);
//        if (decide < 0.333) {
//            bit_map1.Add(num);
//            bit_map2.Add(num);
//        } else if (decide < 0.666) {
//            bit_map1.Delete(num);
//            bit_map2.Delete(num);
//        } else {
//            if (bit_map1.Contains(num) != bit_map2.Contains(num)) {
//                ASSERT_TRUE(false);
//            }
//        }
//    }
//
//    for (int num = 0; num <= max_val; ++num) {
//        if (bit_map1.Contains(num) != bit_map2.Contains(num)) {
//            ASSERT_TRUE(false);
//        }
//    }
//
//    cout << "test success\n";
//    cout << "bit map test end\n\n";
//}

