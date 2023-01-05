#include <iostream>
#include <map>
#include "gtest/gtest.h"
#include "random.h"
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
private:
    struct Node {
        int key;
        int value;
        struct Node* last = nullptr;
        struct Node* next = nullptr;

        Node(int k, int v):key(k), value(v) {
        }
    };

    class NodeDoubleLinkedList {
    public:
        void AddNode(Node* node) {
            if (node == nullptr) {
                return;
            }

            if (head_ == nullptr) {
                head_ = node;
                tail_ = node;
            } else {
                tail_->next = node;
                node->last = tail_;
                tail_ = node;
            }
        }

        void MoveNodeToTail(Node* node) {
            if (node == nullptr) {
                return;
            }
            if (tail_ == node) {
                return;
            }

            if (head_ == node) {
                head_ = head_->next;
                head_->last = nullptr;
            } else {
                node->last->next = node->next;
                node->next->last = node->last;
            }

            node->last = tail_;
            node->next = nullptr;
            tail_->next = node;
            tail_ = node;
        }

        Node* RemoveHead() {
            if (head_ == nullptr) {
                return nullptr;
            }

            Node* ret = head_;
            if (head_ == tail_) {
                head_ = nullptr;
                tail_ = nullptr;
            } else {
                head_ = head_->next;
                ret->next = nullptr;
                head_->last = nullptr;
            }
            return ret;
        }

    private:
        Node* head_ = nullptr;
        Node* tail_ = nullptr;
    };

public:
    LRUCache(int capacity):capacity_(capacity) {
    }

    int get(int key) {
        auto iter = kv_.find(key);
        int ans = -1;
        if (iter != kv_.end()) {
            ans = iter->second->value;
            node_list_.MoveNodeToTail(iter->second);
        }

        return ans;
    }

    void put(int key, int value) {
        auto iter = kv_.find(key);
        if (iter != kv_.end()) {
            iter->second->value = value;
            node_list_.MoveNodeToTail(iter->second);
            return;
        }

        if (kv_.size() == capacity_) {
            Node* head = node_list_.RemoveHead();
            if (head != nullptr) {
                kv_.erase(head->key);
                delete head;
            }
        }

        Node* node = new Node(key, value);
        node_list_.AddNode(node);
        kv_.insert({key, node});
    }
private:
    map<int, Node*> kv_;
    NodeDoubleLinkedList node_list_;
    int capacity_;
};


class LRUCacheTest {
public:
    LRUCacheTest(int capacity): capacity_(capacity) {
        kv_ = new pair<int, int>[capacity_] {{0,0}};
    }

    ~LRUCacheTest() {
        delete [] kv_;
    }

    int get(int key) {
        if (size_ == 0) {
            return -1;
        }

        int ans = -1;
        int index = -1;
        for (int i = 0; i < size_; ++i) {
            if (kv_[i].first == key) {
                ans = kv_[i].second;
                index = i;
                break;
            }
        }

        if (index == -1) {
            return -1;
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

        if (key_index != -1) { // 存在key,取出来，调位置
            for (int i = key_index; i > 0; --i) {
                kv_[i] = kv_[i-1];
            }
            kv_[0] = {key, value};
        } else { // 不存在key，需要添加元素
            if (size_ >= capacity_) {
                for (int i = capacity_ - 1; i > 0; --i) {
                    kv_[i] = kv_[i-1];
                }
                kv_[0] = {key, value};
            } else if (size_ < capacity_){
                ++size_;
                for (int i = size_ - 1; i > 0; --i) {
                    kv_[i] = kv_[i-1];
                }
                kv_[0] = {key, value};
            }
        }
    }


private:
    int capacity_ = 0;
    pair<int, int>* kv_ = nullptr;
    int size_ = 0;
};

//TEST(PractiseTest, LRUCacheTest) {
//    cout << "lru cache test start\n";
//    int test_times = 500000;
//    int max_val = 100;
//    int min_val = -100;
//
//    LRUCacheTest lru_test(10);
//    LRUCache lru(10);
//    for (int i = 0; i < test_times; ++i) {
//        if (Random::random() < 0.5) {
//            int key = Random::random(min_val, max_val);
//            int value = Random::random(min_val, max_val);
//            lru_test.put(key, value);
//            lru.put(key, value);
//        } else {
//            int key = Random::random(min_val, max_val);
//            if (lru_test.get(key) != lru.get(key)) {
//                ASSERT_TRUE(false);
//            }
//        }
//    }
//
//    cout << "test success\n";
//    cout << "lru cache test end\n\n";
//}