#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
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
    求二叉树最宽的层有多少个节点
*/
struct Info {
    Info(bool full, bool cbt, int h):
        is_full(full), is_cbt(cbt), height(h) {
    }

    bool is_full = false;
    bool is_cbt = false;
    int height = 0;
};

static Info process(Node* head) {
    if (head == nullptr) {
        return Info(true, true, 0);
    }

    Info left_info = process(head->left);
    Info right_info = process(head->right);
    int height = std::max(left_info.height, right_info.height) + 1;
    bool is_full = false;
    is_full = left_info.is_full && right_info.is_full
                && left_info.height == right_info.height;

    bool is_cbt = false;
    if (is_full) {
        is_cbt = true;
    } else {
        if (left_info.is_cbt && right_info.is_cbt) {
            if (left_info.is_full && right_info.is_cbt
                    && left_info.height == right_info.height) {
                is_cbt = true;
            }

            if (left_info.is_cbt && right_info.is_full
                    && left_info.height == right_info.height + 1) {
                is_cbt = true;
            }

            if (left_info.is_full && right_info.is_full
                    && left_info.height == right_info.height + 1) {
                is_cbt = true;
            }
        }
    }

    return Info(is_full, is_cbt, height);
}

static bool IsCBT(Node* head) {
    if (head == nullptr) {
        return true;
    }

    return process(head).is_cbt;
}

static bool IsCBT1(Node* head) {
    if (head == nullptr) {
        return true;
    }

    queue<Node*> que;
    que.push(head);
    bool leaf = false;

    while (!que.empty()) {
        Node* cur = que.front();
        que.pop();

        if (cur->left != nullptr) {
            if (leaf) {
                return false;
            }

            que.push(cur->left);
        } else {
            leaf = true;
        }

        if (cur->right != nullptr) {
            if (leaf) {
                return false;
            }

            que.push(cur->right);
        } else {
            leaf = true;
        }
    }

    return true;
}

static bool test(Node* head) {
    if (head == nullptr) {
        return true;
    }

    bool leaf = false;
    queue<Node*> que;
    que.push(head);
    Node* left = nullptr;
    Node* right = nullptr;

    while (!que.empty()) {
        Node* cur = que.front();
        que.pop();

        left = cur->left;
        right = cur->right;
        if ((leaf && (left != nullptr || right != nullptr))
                || (left == nullptr && right != nullptr)) {
            return false;
        }

        if (left != nullptr) {
            que.push(left);
        }

        if (right != nullptr) {
            que.push(right);
        }

        if (left == nullptr || right == nullptr) {
            leaf = true;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max_val = 100;
    int max_level = 6;
    int test_times = 10000;

    for (int i = 0; i < test_times; ++i) {
        Node* tree = GenerateRandomTree(max_val, max_level);
        if (IsCBT(tree) != test(tree)) {
            PrintTree(tree);
            cout << IsCBT(tree) << endl;
            cout << test(tree) << endl;
            cout << "test failed" << endl;
            FreeTree(tree);
            break;
        }

        FreeTree(tree);
    }

    for (int i = 0; i < test_times; ++i) {
        Node* tree = GenerateRandomTree(max_val, max_level);
        if (IsCBT1(tree) != test(tree)) {
            PrintTree(tree);
            cout << IsCBT1(tree) << endl;
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
