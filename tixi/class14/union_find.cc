#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include "random.h"
#include "common.h"
#include "gtest/gtest.h"

using namespace std;

namespace {

class UnionFind {
public:
    UnionFind(vector<int> &elem) {
        for (int i = 0; i < elem.size(); ++i) {
            int *p = new int(i);
            sets_[i] = p;
            parents_[p] = p;
            size_map_[p] = 1;
        }
    }

    bool IsSameSet(int a, int b) {
        return true;
    }

    void Union(int a, int b) {

    }

    int Sets() const {
        return size_map_.size();
    }

private:
    int* FindFather(int val) {
        return nullptr;
    }

private:
    map<int, int*> sets_;
    map<int*, int*> parents_;
    map<int*, int> size_map_;
};

class UnionFindTest {
public:
    UnionFindTest(vector<int> &elem) {
    }

    bool IsSameSet(int a, int b) {
        return true;
    }

    void Union(int a, int b) {
    }

    int Sets() const {
        return 0;
    }

private:

};
}

TEST(UnionFind, UnionFindTest) {
    std::cout << "union find" <<std::endl;

}