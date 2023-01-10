#include <iostream>
#include <vector>
#include <stack>
#include "arr_tools.h"
#include "tree_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

static void PreOrder(TreeNode* tree, vector<int>& orders) {
    if (tree == nullptr) {
        return;
    }

    stack<TreeNode*> node_stack;
    node_stack.push(tree);
    while (!node_stack.empty()) {
        TreeNode* cur = node_stack.top();
        node_stack.pop();
        orders.push_back(cur->val);
        if (cur->right != nullptr) {
            node_stack.push(cur->right);
        }

        if (cur->left != nullptr) {
            node_stack.push(cur->left);
        }
    }
}

static void PreOrderTest(TreeNode* tree, vector<int>& orders) {
    if (tree == nullptr) {
        return;
    }

    orders.push_back(tree->val);
    PreOrderTest(tree->left, orders);
    PreOrderTest(tree->right, orders);
}

static void InOrder(TreeNode* tree, vector<int>& orders) {
    if (tree == nullptr) {
        return;
    }

    stack<TreeNode*> node_stack;
    TreeNode* cur = tree;
    while (!node_stack.empty() || cur != nullptr) {
        if (cur != nullptr) {
            node_stack.push(cur);
            cur = cur->left;
        } else {
            cur = node_stack.top();
            node_stack.pop();
            orders.push_back(cur->val);
            cur = cur->right;
        }
    }
}

static void InOrderTest(TreeNode* tree, vector<int>& orders) {
    if (tree == nullptr) {
        return;
    }

    InOrderTest(tree->left, orders);
    orders.push_back(tree->val);
    InOrderTest(tree->right, orders);
}

static void PosOrder(TreeNode* tree, vector<int>& orders) {
    if (tree == nullptr) {
        return;
    }

    stack<TreeNode*> node_stack;
    stack<TreeNode*> res_stack;
    node_stack.push(tree);

    while (!node_stack.empty()) {
        TreeNode* cur = node_stack.top();
        node_stack.pop();
        res_stack.push(cur);
        if (cur->left != nullptr) {
            node_stack.push(cur->left);
        }
        if (cur->right != nullptr) {
            node_stack.push(cur->right);
        }
    }

    while (!res_stack.empty()) {
        orders.push_back(res_stack.top()->val);
        res_stack.pop();
    }
}

static void PosOrderTest(TreeNode* tree, vector<int>& orders) {
    if (tree == nullptr) {
        return;
    }

    PosOrderTest(tree->left, orders);
    PosOrderTest(tree->right, orders);
    orders.push_back(tree->val);
}

//TEST(TreeTest, BinTreeTraverseTest) {
//    cout << "binary tree traverse test start" << endl;
//    int test_times = 100000;
//    int min_val = 1;
//    int max_val = 100;
//    int max_level = 20;
//
//    for (int i = 0; i < test_times; ++i) {
//        TreeNode* tree = GenerateRandomBST(max_level, min_val, max_val);
//        vector<int> order1;
//        vector<int> order2;
//        PreOrder(tree, order1);
//        PreOrderTest(tree, order2);
//
//        if (!IsEqual(order1, order2)) {
//            ASSERT_TRUE(false);
//        }
//        FreeBST(tree);
//    }
//
//    for (int i = 0; i < test_times; ++i) {
//        TreeNode* tree = GenerateRandomBST(max_level, min_val, max_val);
//        vector<int> order1;
//        vector<int> order2;
//        InOrder(tree, order1);
//        InOrderTest(tree, order2);
//
//        if (!IsEqual(order1, order2)) {
//            ASSERT_TRUE(false);
//        }
//        FreeBST(tree);
//    }
//
//    for (int i = 0; i < test_times; ++i) {
//        TreeNode* tree = GenerateRandomBST(max_level, min_val, max_val);
//        vector<int> order1;
//        vector<int> order2;
//        PosOrder(tree, order1);
//        PosOrderTest(tree, order2);
//
//        if (!IsEqual(order1, order2)) {
//            ASSERT_TRUE(false);
//        }
//        FreeBST(tree);
//    }
//
//    cout << "test success" << endl;
//    cout << "binary tree traverse test end " << endl;
//}