#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <set>
#include "random.h"
#include "common.h"
#include "arr_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

namespace {

class UnionFind {
public:
    UnionFind(vector<int> &elem) {
        for (int i = 0; i < elem.size(); ++i) {
            int* p_set = new int(elem[i]);
            nodes_[elem[i]] = p_set;
            size_map_[p_set] = 1;
            parents_[p_set] = p_set;
        }
    }

    ~UnionFind() {
        for (auto elem: nodes_) {
            delete elem.second;
        }
    }


    bool IsSameSet(int a, int b) {
        return FindFather(nodes_[a]) == FindFather(nodes_[b]);
    }

    void Union(int a, int b) {
        int* a_head = FindFather(nodes_[a]);
        int* b_head = FindFather(nodes_[b]);
        if (a_head != b_head) {
            int set_a_size = size_map_[a_head];
            int set_b_size = size_map_[b_head];
            int* big = set_a_size >= set_b_size ? a_head : b_head;
            int* small = big == a_head ? b_head : a_head;
            parents_[small] = big;
            size_map_[big] = set_a_size + set_b_size;
            size_map_.erase(small);
        }
    }

    int Sets() const {
        return size_map_.size();
    }

private:
    int* FindFather(int* cur) {
        stack<int*> path;
        while (cur != parents_[cur]) {
            path.push(cur);
            cur = parents_[cur];
        }
        while (!path.empty()) {
            parents_[path.top()] = cur;
            path.pop();
        }

        return cur;
    }

private:
    unordered_map<int, int*> nodes_;
    unordered_map<int*, int*> parents_;
    unordered_map<int*, int> size_map_;

};

class UnionFindTest {
public:
    UnionFindTest(vector<int> &elem) {
        for (int i = 0; i < elem.size(); ++i) {
            vector<int> vec;
            vec.push_back(elem[i]);
            sets.push_back(vec);
        }
    }

    bool IsSameSet(int a, int b) {
        for (int i = 0; i < sets.size(); ++i) {
            set<int> val;
            for (int j = 0; j < sets[i].size(); ++j) {
                val.insert(sets[i][j]);
            }

            if (val.contains(a) && val.contains(b)) {
                return true;
            }
        }
        return false;
    }

    void Union(int a, int b) {
        if (IsSameSet(a, b)) {
            return;
        }

        int pos_a = -1;
        int pos_b = -1;
        for (int i = 0; i < sets.size(); ++i) {
            for (int j = 0; j < sets[i].size(); ++j) {
                if (sets[i][j] == a) {
                    pos_a = i;
                    break;
                }
            }
        }
        for (int i = 0; i < sets.size(); ++i) {
            for (int j = 0; j < sets[i].size(); ++j) {
                if (sets[i][j] == b) {
                    pos_b = i;
                    break;
                }
            }
        }

        if (pos_a == -1 || pos_b == -1) {
            return;
        }

        for (int i = 0; i < sets[pos_b].size(); ++i) {
            sets[pos_a].push_back(sets[pos_b][i]);
        }
        sets.erase(sets.begin() + pos_b);
    }

    int Sets() const {
        return sets.size();
    }

private:
    vector<vector<int>> sets;
};
}

//TEST(UnionFind, UnionFindTest) {
//    cout << "test start ...." << endl;
//    int test_times = 10000;
//    int min_val = 10;
//    int max_val = 100;
//    int max_n = 20;
//    bool is_success = true;
//    for (int i = 0; i < test_times; ++i) {
//        vector<int> elem;
//        tools::RandomNorepeatedArr(elem, max_n, min_val, max_val);
//        if (elem.empty()) {
//            continue;
//        }
//        UnionFind union1(elem);
//        UnionFindTest union2(elem);
//        for (int j = 0; j < 100; ++j) {
//            if (Random::random() < 0.33) {
//                int a = RandomVal(0, elem.size() - 1);
//                int b = RandomVal(0, elem.size() - 1);
//                if (union1.IsSameSet(elem[a], elem[b]) != union2.IsSameSet(elem[a], elem[b])) {
//                    cout << "test failed" << endl;
//                    is_success = false;
//                    break;
//                }
//            } else if (Random::random() < 0.66) {
//                if (union1.Sets() != union2.Sets()) {
//                    cout << "test failed" << endl;
//                    is_success = false;
//                    break;
//                }
//            } else {
//                int a = RandomVal(0, elem.size()- 1);
//                int b = RandomVal(0, elem.size()-1);
//                union1.Union(elem[a], elem[b]);
//                union2.Union(elem[a], elem[b]);
//            }
//        }
//
//        if (!is_success) {
//            break;
//        }
//    }
//
//    cout << "test end" << endl;
//}