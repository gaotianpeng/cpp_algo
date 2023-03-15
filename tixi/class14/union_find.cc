#include <iostream>
#include <vector>
#include <stack>
#include <map>
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
                int *p = new int(i);
                sets_[elem[i]] = p;
                parents_[p] = p;
                size_map_[p] = 1;
            }
        }

        ~UnionFind() {
            for (auto elem: parents_) {
                delete elem.first;
            }
        }


        bool IsSameSet(int a, int b) {
            return FindFather(sets_.at(a)) == FindFather(sets_.at(b));
        }

        void Union(int a, int b) {
            int *a_head = FindFather(sets_.at(a));
            int *b_head = FindFather(sets_.at(b));
            if (a_head != b_head) {
                int a_set_size = size_map_[a_head];
                int b_set_size = size_map_[b_head];
                int *p_big = a_set_size >= b_set_size ? a_head : b_head;
                int *p_small = p_big == a_head ? b_head : a_head;
                parents_[p_small] = p_big;
                size_map_[p_big] = a_set_size + b_set_size;
                size_map_.erase(p_small);
            }
        }

        int Sets() const {
            return size_map_.size();
        }

    private:
        int *FindFather(int *p) {
            stack<int *> path;
            while (p != parents_[p]) {
                path.push(p);
                p = parents_[p];
            }

            while (!path.empty()) {
                parents_[path.top()] = p;
                path.pop();
            }

            return p;
        }

    private:
        map<int, int *> sets_;
        map<int *, int *> parents_;
        map<int *, int> size_map_;
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

TEST(UnionFind, UnionFindTest) {
//    std::cout << "union find" <<std::endl;
//    vector<int> elem { 1, 2, 3, 4, 5, 6};
//    UnionFindTest u(elem);
//    cout << u.Sets() << endl;
//
//    u.Union(1, 2);
//    cout << u.Sets() << endl;
//    cout << u.IsSameSet(1, 2) << endl;
//
//    cout << u.IsSameSet(1, 3) << endl;
//
//    u.Union(1, 3);
//    cout << u.Sets() << endl;
    cout << "test start ...." << endl;
    int test_times = 10000;
    int min_val = 10;
    int max_val = 100;
    int max_n = 20;
    bool is_success = true;
    for (int i = 0; i < test_times; ++i) {
        vector<int> elem;
        tools::RandomNorepeatedArr(elem, max_n, min_val, max_val);
        if (elem.empty()) {
            continue;
        }
        UnionFind union1(elem);
        UnionFindTest union2(elem);
        for (int j = 0; j < 100; ++j) {
            if (Random::random() < 0.33) {
                int a = RandomVal(0, elem.size() - 1);
                int b = RandomVal(0, elem.size() - 1);
                if (union1.IsSameSet(elem[a], elem[b]) != union2.IsSameSet(elem[a], elem[b])) {
                    cout << "test failed" << endl;
                    is_success = false;
                    break;
                }
            } else if (Random::random() < 0.66) {
                if (union1.Sets() != union2.Sets()) {
                    cout << "test failed" << endl;
                    is_success = false;
                    break;
                }
            } else {
                int a = RandomVal(0, elem.size()- 1);
                int b = RandomVal(0, elem.size()-1);
                union1.Union(elem[a], elem[b]);
                union2.Union(elem[a], elem[b]);
            }
        }

        if (!is_success) {
            break;
        }
    }

    cout << "test end" << endl;
}