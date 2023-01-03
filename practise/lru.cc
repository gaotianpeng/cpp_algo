#include <iostream>
#include <map>
#include <vector>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;
/*
    leetcode 146
    请你设计并实现一个满足 LRU (最近最少使用) 缓存 约束的数据结构
    实现 LRUCache 类：
        LRUCache(int capacity) 以 正整数 作为容量capacity 初始化 LRU 缓存
        int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1
        void put(int key, int value)如果关键字key 已经存在，则变更其数据值value

    如果不存在，则向缓存中插入该组key-value. 如果插入操作导致关键字数量超过capacity, 则应该 逐出 最久未使用的关键字
    函数 get 和 put 必须以 O(1) 的平均时间复杂度运行

    提示：
    1 <= capacity <= 3000
    0 <= key <= 10000
    0 <= value <= 105
    最多调用 2 * 105 次 get 和 put

 */
class LRUCache {
public:
    LRUCache(int capacity) {
    }

    int get(int key) {
        return -1;
    }

    void put(int key, int value) {

    }
};

class LRUCacheTest {
public:
    LRUCacheTest(int capacity): capacity_(capacity) {
    }

    int get(int key) {
        if (kv_.empty()) {
            return -1;
        }

        int ans = -1;
        int index = 0;
        for (; index < size_; ++index) {
            if (kv_[index].first == key) {
                ans = kv_[index].second;
            }
        }

        for (int i = index; i > 0; --i) {
            kv_[i] = kv_[i-1];
        }

        kv_[0] = {key, ans};

        return ans;
    }

    void put(int key, int value) {
        int key_index = -1;
        for (int i = 0; i < size_; ++i) {
            if (kv_[i].first == key) {
                key_index = i;
                break;
            }
        }

        if (key_index != -1) {
            for (int i = key_index; i > 0; --i) {
                kv_[i] = kv_[i-1];
            }
            kv_[0] = {key, value};
        } else {
            for (int i = size_; i > 0; --i) {
                kv_[i] = kv_[i-1];
            }
            kv_[0] = {key, value};
            if (size_ < capacity_) {
                ++size_;
            }
        }
    }

private:
    int capacity_ = 0;
    vector<pair<int, int>> kv_;
    int size_ = 0;
};

//TEST(PractiseTest, LRUCacheTest) {
//    cout << "lru cache test start\n";
//
//    cout << "test success\n";
//    cout << "lru cache test end\n\n";
//}