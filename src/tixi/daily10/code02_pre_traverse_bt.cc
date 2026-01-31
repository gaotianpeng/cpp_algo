#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

static int RandomVal(int min_val, int max_val) {
    return Random::nextInt(min_val, max_val);
}

struct Node {
    int val  = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int v):val(v) {
    }
};

static Node* generate(int level, int max_level, int max_val) {
    if (level > max_level || Random::nextDouble() > 0.5) {
        return nullptr;
    }

    Node* node = new Node(RandomVal(-max_val, max_val));
    node->left = generate(level + 1, max_level, max_val);
    node->right = generate(level + 1, max_level, max_val);
    return node;
}

static Node* GenerateRandomTree(int max_val, int max_level) {
    return generate(1, max_level, max_val);
}

static void FreeTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    queue<Node*> que;
    que.push(node);
    while (!que.empty()) {
        Node* cur = que.front();
        que.pop();
        if (cur->left) {
            que.push(cur->left);
        }
        if (cur->right) {
            que.push(cur->right);
        }
        delete cur;
    }
}

static void Print(const vector<int>& vals) {
    for (auto& elem: vals) {
        cout << elem << " ";
    }
    cout << endl;
}

static bool IsEqual(const vector<int>& vals1, const vector<int>& vals2) {
    if (vals1.size() != vals2.size()) {
        return false;
    }

    for (int i = 0; i < vals1.size(); ++i) {
        if (vals1[i] != vals2[i]) {
            return false;
        }
    }

    return true;
}

}  // namespace


static void process(Node* node, vector<int>& val) {
    if (node == nullptr) {
        return;
    }

    val.emplace_back(node->val);
    process(node->left, val);
    process(node->right, val);
}

static void test(Node* node, vector<int>& val) {
    process(node, val);
}

static void PreTraverse(Node* node, vector<int>& val) {
    if (node == nullptr) {
        return;
    }

    stack<Node*> nodes;
    nodes.push(node);
    while (!nodes.empty()) {
        Node* cur = nodes.top();
        nodes.pop();
        val.emplace_back(cur->val);
        if (cur->right) {
            nodes.push(cur->right);
        }
        if (cur->left) {
            nodes.push(cur->left);
        }
    }
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max_val = 100;
    int max_level = 30;
    int test_times = 1000;

    for (int i = 0; i < test_times; ++i) {
        Node* tree = GenerateRandomTree(max_val, max_level);
        vector<int> vals1, vals2;
        PreTraverse(tree, vals1);
        test(tree, vals2);
        if (!IsEqual(vals1, vals2)) {
            cout << "test failed" << endl;
            Print(vals1);
            Print(vals2);
            FreeTree(tree);
            break;
        }

        FreeTree(tree);
    }

    cout << "test end" << endl;
    return 0;
}