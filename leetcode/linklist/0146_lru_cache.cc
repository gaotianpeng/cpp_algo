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

    void AddNode(Node* node) {
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

    
    void MoveNodeToTail(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (head == nullptr) {
            return;
        }

        if (head == tail) {
            return;
        }


        if (head == node) {
            head = node->next;
            if (head) {
                head->last = nullptr;
            }
        } else if (tail == node) {
            return;
        } 
        else {
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
        node_list_.MoveNodeToTail(node);
        
        return node->value;
    }

    void put(int key, int value) {
        auto iter = key_node_map_.find(key);
        if (iter == key_node_map_.end()) {
            Node* new_node = new Node(key, value);
            key_node_map_.insert({key, new_node});
            node_list_.AddNode(new_node);
            if (key_node_map_.size() == capacity_ + 1) {
                removeMostUnusedCache();
            }
        } else {
            Node* node = key_node_map_[key];
            node->value = value;
            node_list_.MoveNodeToTail(node);
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

int main(int argc, char* argv[]) {
    LRUCache cache(1);
    cache.put(2, 1);
    cache.get(2);
    return 0;
}