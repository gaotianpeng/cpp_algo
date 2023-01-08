#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include "gtest/gtest.h"
#include "arr_tools.h"
#include "random.h"

using namespace std;
using namespace tools;

class TrieTree {
    struct Node {
        int pass;
        int end;
        array<Node*, 26> nexts = {nullptr};

        Node() {
           pass = 0;
           end = 0;
        };
    };
public:
    TrieTree() {
        root_ = new Node();
    }

    ~TrieTree() {
        if (root_ != nullptr) {
            delete root_;
            root_ = nullptr;
        }
    }

    void Insert(string word) {
        if (word.empty()) {
            return;
        }

        Node* node = root_;
        node->pass++;
        int path = 0;
        for (int i = 0; i < word.size(); ++i) {
            path = word[i] - 'a';
            if (node->nexts[path] == nullptr) {
                node->nexts[path] = new Node();
            }
            node = node->nexts[path];
            node->pass++;
        }
        node->end++;
    }

    void Delete(string word) {
        if (Search(word) == 0) {
            return;
        }

        Node* node = root_;
        node->pass--;
        int path = 0;
        for (int i = 0; i < word.size(); ++i) {
            path = word[i] - 'a';
            if (--node->nexts[path]->pass == 0) {
                FreeNode(node->nexts[path]);
                node->nexts[path] = nullptr;
                return;
            }
            node = node->nexts[path];
        }
        node->end--;
    }

    int Search(string word) {
        if (word.empty()) {
            return 0;
        }

        Node* node = root_;
        int index = 0;
        for (int i = 0; i < word.size(); ++i) {
            index = word[i] - 'a';
            if (node->nexts[index] == nullptr) {
                return 0;
            }
            node = node->nexts[index];
        }
        return node->end;
    }

    int Prefix(const string& prefix) {
        if (prefix.empty()) {
            return 0;
        }

        Node* node = root_;
        int index = 0;
        for (int i = 0; i < prefix.size(); ++i) {
            index = prefix[i] - 'a';
            if (node->nexts[index] == nullptr) {
                return 0;
            }
            node = node->nexts[index];
        }

        return node->pass;
    }

private:
    void FreeNode(Node* node) {
        if (node == nullptr) {
            return;
        }

        queue<Node*> node_queue;
        set<Node*> node_set;
        node_queue.push(node);
        node_set.insert(node);
        while (!node_queue.empty()) {
            Node* tmp = node_queue.front();
            node_queue.pop();
            for (int i = 0; i < tmp->nexts.size(); ++i) {
                if (tmp->nexts[i] != nullptr) {
                    node_queue.push(tmp->nexts[i]);
                    node_set.insert(tmp->nexts[i]);
                }
            }
        }

        for (auto elem: node_set) {
            delete elem;
        }
    }
private:
    Node* root_ = nullptr;
};

class TrieTreeTest {
public:
    TrieTreeTest() {
    }

    void Insert(const string& word) {
        if (kv_.find(word) != kv_.end()) {
            int cnt = kv_[word];
            kv_.erase(word);
            kv_.insert({word, cnt + 1});
        } else {
            kv_.insert({word, 1});
        }
    }

    void Delete(const string& word) {
        if (word.empty()) {
            return;
        }

        if (kv_.find(word) != kv_.end()) {
            if (kv_[word] == 1) {
                kv_.erase(word);
            } else {
                int cnt = kv_[word];
                kv_.erase(word);
                kv_.insert({word, cnt-1});
            }
        }
    }

    int Search(const string& word) {
        if (word.empty()) {
            return 0;
        }
        if (kv_.find(word) != kv_.end()) {
            return kv_[word];
        }
        return 0;
    }

    int Prefix(const string& word) {
        if (word.empty()) {
            return 0;
        }
        int ans = 0;
        int len = word.size();
        for (auto& elem: kv_) {
            if (elem.first.substr(0, len) == word) {
                ans += elem.second;
            }
        }
        return ans;
    }

private:
    std::map<string, int> kv_;
};

static string generateRandomString(int str_len) {
    int n = Random::random(1, str_len);
    char* chs = new char[n+1] {0};
    chs[n] = '\0';
    for (int i = 0; i < n; ++i) {
        chs[i] =(char)(Random::random(1, 26) + 96);
    }

    string ret(chs);
    delete [] chs;
    return ret;
}

static void generateRandomStringArray(vector<string>& arr, int arr_len, int str_len) {
    int n = Random::random(1, arr_len);
    for (int i = 0; i < n; ++i) {
        arr.push_back(generateRandomString(str_len));
    }
}

//TEST(TreeTest, TrieTreeTest) {
//    cout << "trie tree test start\n";
//    int arr_len = 100;
//    int str_len = 20;
//    int test_times = 10000;
//    for (int i = 0; i < test_times; ++i) {
//        vector<string> arr;
//        generateRandomStringArray(arr, arr_len, str_len);
//        TrieTree trie_tree;
//        TrieTreeTest trie_tree_test;
//        for (int j = 0; j < arr.size(); ++j) {
//            double decide = Random::random();
//            if (decide < 0.25) {
//                trie_tree.Insert(arr[j]);
//                trie_tree_test.Insert(arr[j]);
//            } else if (decide < 0.5) {
//                trie_tree.Delete(arr[j]);
//                trie_tree_test.Delete(arr[j]);
//            } else if (decide < 0.75) {
//                int ans1 = trie_tree.Search(arr[j]);
//                int ans2 = trie_tree_test.Search(arr[j]);
//                if (ans1 != ans2) {
//                    ASSERT_TRUE(false);
//                }
//            } else {
//                int ans1 = trie_tree.Prefix(arr[j]);
//                int ans2 = trie_tree_test.Prefix(arr[j]);
//                if (ans1 != ans2) {
//                    cout << ans1 << endl;
//                    cout << ans2 << endl;
//                    cout << arr[j] << endl;
//                    ASSERT_TRUE(false);
//                }
//            }
//        }
//    }
//
//    cout << "test success\n";
//    cout << "trie tree test end\n\n";
//}