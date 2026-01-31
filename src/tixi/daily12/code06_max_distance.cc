#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
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

static Node* generate(int cur_level, int max_level, int max_val) {
    if (cur_level > max_level || Random::nextDouble() > 0.6) {
        return nullptr;
    }

    Node* node = new Node(RandomVal(-std::abs(max_val), std::abs(max_val)));
    node->left = generate(cur_level + 1, max_level, max_val);
    node->right = generate(cur_level + 1, max_level, max_val);

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

static void PrintTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    cout << "++++++++++++ binary tree ++++++++++" << endl;

    queue<Node*> que;
    que.push(node);
    queue<Node*> cur_level_nodes;
    int next_level_node_n = 0;
    while (!que.empty()) {
        next_level_node_n = 0;
        while (!que.empty()) {
            Node* cur = que.front();
            cur_level_nodes.push(que.front());
            que.pop();
            if (cur == nullptr) {
                cout << "n "; 
            } else {
                cout << cur->val << " ";
            }
        }
        cout << endl;

        while (!cur_level_nodes.empty()) {
            Node* cur = cur_level_nodes.front();
            cur_level_nodes.pop();
            if (cur == nullptr) {
                que.push(nullptr);
                que.push(nullptr);
            } else {
                if (cur->left == nullptr) {
                    que.push(nullptr);
                } else {
                    que.push(cur->left);
                    ++next_level_node_n;
                }
                if (cur->right == nullptr) {
                    que.push(nullptr);
                } else {
                    que.push(cur->right);
                    ++next_level_node_n;
                }
            }
        }
        if (next_level_node_n == 0) {
            break;
        }
    }

    cout << "------------ binary tree ----------" << endl;
}

}  // namespace

/*
    给定一棵二叉树的头节点head，任何两个节点之间都存在距离，
    返回整棵二叉树的最大距离
*/
struct Info {
    int max_distance;
    int height;

    Info(int m, int h):max_distance(m), height(h) {
    }
};

static Info process(Node* node) {
    if (node == nullptr) {
        return Info(0, 0);
    }

    Info left_info = process(node->left);
    Info right_info = process(node->right);

    int height = std::max(left_info.height, right_info.height) + 1;

    int p1 = left_info.max_distance;
    int p2 = right_info.max_distance;
    int p3 = left_info.height + right_info.height + 1;

    int max_distance = std::max(std::max(p1, p2), p3);

    return Info(max_distance, height);
}

static int GetMaxDistance(Node* head) {
    return process(head).max_distance;
}

/*
    for test 
    ----------------------------------------------------------------------------
*/
static void PreTraverse(Node* head, vector<Node*>& vals) {
    if (head == nullptr) {
        return;
    }

    stack<Node*> nodes;
    nodes.push(head);
    while (!nodes.empty()) {
        Node* cur = nodes.top();
        nodes.pop();
        vals.emplace_back(cur);
        if (cur->right != nullptr) {
            nodes.push(cur->right);
        }
        if (cur->left != nullptr) {
            nodes.push(cur->left);
        }
    }
}

static void FillParentMap(Node* head, unordered_map<Node*, Node*>& parent_map) {
    if (head->left != nullptr) {
        parent_map.insert({head->left, head});
        FillParentMap(head->left, parent_map);
    }
    if (head->right != nullptr) {
        parent_map.insert({head->right, head});
        FillParentMap(head->right, parent_map);
    }
}

static void GetParentMap(Node* head, unordered_map<Node*, Node*>& parent_map) {
    parent_map.insert({head, nullptr});
    FillParentMap(head, parent_map);
}

static int distance(const unordered_map<Node*, Node*>& parent_map,
        Node* node1, Node* node2) {
    unordered_set<Node*> node1_set;
    Node* cur = node1;
    node1_set.insert(cur);
    while (parent_map.at(cur) != nullptr) {
        cur = parent_map.at(cur);
        node1_set.insert(cur);
    }

    cur = node2;
    while (!node1_set.contains(cur)) {
        cur = parent_map.at(cur);
    }

    Node* lowest_ancestor = cur;
    cur = node1;
    int distance1 = 1;
    while (cur != lowest_ancestor) {
        cur = parent_map.at(cur);
        distance1++;
    }

    cur = node2;
    int distance2 = 1;
    while (cur != lowest_ancestor) {
        cur = parent_map.at(cur);
        distance2++;
    }

    return distance1 + distance2 - 1;
}

static int test(Node* head) {
    if (head == nullptr) {
        return 0;
    }

    vector<Node*> prelist;
    PreTraverse(head, prelist);
    unordered_map<Node*, Node*> parent_map;
    GetParentMap(head, parent_map);
    int ans = 0;
    for (int i = 0; i < prelist.size(); ++i) {
        for (int j = i; j < prelist.size(); ++j) {
            ans = std::max(ans, distance(parent_map, prelist[i], prelist[j]));
        }
    }

    return ans;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max_val = 100;
    int max_level = 6;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        Node* tree = GenerateRandomTree(max_val, max_level);
        if (GetMaxDistance(tree) != test(tree)) {
            PrintTree(tree);
            cout << GetMaxDistance(tree) << endl;
            cout << test(tree) << endl;
            cout << "test failed" << endl;
            FreeTree(tree);
            break;
        }

        FreeTree(tree);
    }

    cout << "test end" << endl;
    return 0;
}