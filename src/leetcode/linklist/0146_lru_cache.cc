#include <iostream>
#include <random>
#include <map>

using namespace std;

namespace {

class Math {
public:
    static double random() {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
}; // class Math

static int RandomVal(int min_val, int max_val) {
    return (int)(Math::random() * (max_val - min_val)) + min_val;
}


} // namespace

/*
    https://leetcode.cn/problems/lru-cache/
    146 LRU缓存
*/

struct Node {
    Node(int k, int v):key(k), value(v) {
    }

    int key;
    int value;
    Node* last = nullptr;
    Node* next = nullptr;
};

class NodeDoubleLinkedList {
public:
    NodeDoubleLinkedList() {
    }

    ~NodeDoubleLinkedList() {
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }

    void addNode(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->last = tail;
            tail = node;
        }
    }
    
    void moveNodeToTail(Node* node) {
        if (node == nullptr || head == tail
                || node == tail) {
            return;
        }


        if (head == node) {
            head = node->next;
            if (head) {
                head->last = nullptr;
            }
        }  else {
            node->last->next = node->next;
            node->next->last = node->last;
        }

        node->last = tail;
        node->next = nullptr;
        tail->next = node;

        tail = node;
    }
    
    Node* remvoeHead() {
        if (head == nullptr) {
            return nullptr;
        }

        Node* ans = head;
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = ans->next;
            head->last = nullptr;
            ans->next = nullptr;
        }

        return ans;
    }

    void removeNode(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (head == node) {
            head = head->next;
            if (head) {
                head->last = nullptr;
            }
            node->next = nullptr;
        } else if (tail == node) {
            tail = tail->last;
            if (tail) {
                tail->next = nullptr;
            }
            node->last = nullptr;
        } else {
            node->next->last = node->last;
            node->last->next = node->next;
            node->last = nullptr;
            node->next = nullptr;
        }
    }

private:
    Node* head = nullptr;
    Node* tail = nullptr;
};


class LRUCache {
public:
    LRUCache(int capacity):capacity_(capacity) {
    }

    int get(int key) {
        auto iter = key_node_map_.find(key);
        if (iter == key_node_map_.end()) {
            return -1;
        }

        Node* node = iter->second;
        node_list_.moveNodeToTail(node);
        
        return node->value;
    }

    void put(int key, int value) {
        auto iter = key_node_map_.find(key);
        if (iter == key_node_map_.end()) {
            Node* new_node = new Node(key, value);
            key_node_map_.insert({key, new_node});
            node_list_.addNode(new_node);
            if (key_node_map_.size() == capacity_ + 1) {
                removeMostUnusedCache();
            }
        } else {
            Node* node = key_node_map_[key];
            node->value = value;
            node_list_.moveNodeToTail(node);
        }
    }

    void Delete(int key) {
        auto iter = key_node_map_.find(key);
        if (iter != key_node_map_.end()) {
            node_list_.removeNode(iter->second);
            delete iter->second;
            key_node_map_.erase(key);
        }
    }

private:
    void removeMostUnusedCache() {
        Node* node_to_remove = node_list_.remvoeHead();
        if (node_to_remove) {   
            key_node_map_.erase(node_to_remove->key);
            delete node_to_remove;
        }
    }

private:
    int capacity_;
    std::map<int, Node*> key_node_map_;
    NodeDoubleLinkedList node_list_;
};

class TestLRUCache {
public:
    TestLRUCache(int capacity):capacity_(capacity) {
    }
    
    int get(int key) {
        int i = 0;
        bool exist = false;
        int ans = -1;
        for (i = 0; i < cache_.size(); ++i) {
            if (cache_[i].first == key) {
                exist = true;
                ans = cache_[i].second;
                break;
            }
        }
        
        if (!exist) {
            return ans;
        }

        for (int j = i + 1; j < cache_.size(); ++j) {
            cache_[j - 1] = cache_[j];
        }
        cache_[cache_.size() - 1] = std::make_pair(key, ans);
        return ans;
    }

    void put(int key, int value) {
        int i = 0;
        bool exist = false;
        for (i = 0; i < cache_.size(); ++i) {
            if (cache_[i].first == key) {
                exist = true;
                break;
            }
        }
        
        if (!exist) {
            cache_.emplace_back(std::make_pair(key, value));
            if (cache_.size() == capacity_ + 1) {
                removeUnusedHead();
            }
        } else {
            for (int j = i + 1; j < cache_.size(); ++j) {
                cache_[j-1] = cache_[j];
            }
            cache_[cache_.size() - 1] = std::make_pair(key, value);
        }
    }

    void Delete(int key) {
        int i = 0;
        bool exist = false;
        for (i = 0; i < cache_.size(); ++i) {
            if (cache_[i].first == key) {
                exist = true;
                break;
            }
        }

        if (exist) {
            for (int j = i; j < cache_.size() - 1; ++j) {
                cache_[j] = cache_[j+1];
            }
            cache_.pop_back();
        }
    }

private:
    void removeUnusedHead()  {
        for (int i = 1; i < cache_.size(); ++i) {
            cache_[i-1] = cache_[i];
        }
        cache_.pop_back();
    }

private:
    int capacity_;
    std::vector<std::pair<int, int>> cache_;
};

int main(int argc, char* argv[]) {
    cout << "test start" << endl;
    int test_times = 1000;
    int min_val = 1;
    int max_val = 20;
    bool success = true;

    for (int i = 0; i < test_times; ++i) {
        if (!success) {
            cout << "test failed" << endl;
            break;
        }

        int capacity = RandomVal(0, 10);
        LRUCache cache(capacity);
        TestLRUCache test_cache(capacity);

        std::vector<int> key_sets;
        for (int idx = 0; idx < 10; ++idx) {
            key_sets.emplace_back(RandomVal(min_val, max_val));
        }

        for (int j = 0; j < 10000; ++j) {
            int key = key_sets[RandomVal(0, key_sets.size() - 1)];
            double p = Math::random();
            if (p < 0.4) {
                int value = RandomVal(min_val, max_val);
                cache.put(key, value);
                test_cache.put(key, value);
            } else if (p < 0.7){
                if (cache.get(key) != test_cache.get(key)) {
                    cout << cache.get(key) << endl;
                    cout << test_cache.get(key) << endl;
                    success = false;
                    break;
                }
            } else {
                cache.Delete(p);
                test_cache.Delete(p);
            }
        }
    }

    cout << "test end" << endl;

    return 0;
}