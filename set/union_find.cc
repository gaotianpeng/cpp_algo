#include <iostream>
#include <map>
using namespace std;

namespace {
class Node {
public:
    Node(int v) {
        val = v;
    }

private:
    int val;
};

class UnionFind {
public:
    std::map<int, Node*> nodes;
    std::map<Node*, Node*> parents;
    std::map<Node*, int> size_map;

    UnionFind() {

    }
public:
public:

};



} // namespace