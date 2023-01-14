#include <iostream>
#include <queue>
#include <map>
#include "tree_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

static int maxWidth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    queue<TreeNode*> node_queue;
    node_queue.push(root);
    int max = 0;
    TreeNode* cur_end = root;
    TreeNode* next_end = nullptr;
    int cur_leve_nodes = 0;
    while (!node_queue.empty()) {
        TreeNode* cur = node_queue.front();
        node_queue.pop();
        if (cur->left != nullptr) {
            node_queue.push(cur->left);
            next_end = cur->left;
        }
        if (cur->right != nullptr) {
            node_queue.push(cur->right);
            next_end = cur->right;
        }
        cur_leve_nodes++;
        if (cur == cur_end) {
            max = std::max(cur_leve_nodes, max);
            cur_leve_nodes = 0;
            cur_end = next_end;
            next_end = nullptr;
        }
    }
    return max;
}

static int maxWidthTest(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    queue<TreeNode*> node_queue;
    node_queue.push(root);
    map<TreeNode*, int> level_map;
    level_map.insert({root, 1});
    int cur_level = 1; // 当前正在统计哪一层的宽度
    int cur_level_nodes = 0; // 当前层 cur_level 层，宽度目前是多少
    int max = 0;
    while (!node_queue.empty()) {
        TreeNode* cur = node_queue.front();
        node_queue.pop();
        int cur_node_level = level_map[cur];
        if (cur->left != nullptr) {
            level_map.insert({cur->left, cur_node_level + 1});
            node_queue.push(cur->left);
        }

        if (cur->right != nullptr) {
            level_map.insert({cur->right, cur_node_level + 1});
            node_queue.push(cur->right);
        }

        if (cur_node_level == cur_level) {
            cur_level_nodes++;
        } else {
            max = std::max(max, cur_level_nodes);
            cur_level++;
            cur_level_nodes = 1;
        }
    }

    return std::max(max, cur_level_nodes);
}

//TEST(TreeTest, BinaryTreeMaxWidthTest) {
//    cout << "binary tree max width test start " << endl;
//
//    int test_times = 100000;
//    int max_level = 5;
//    int min_val = 1;
//    int max_val = 10;
//    for (int i = 0; i < test_times; ++i) {
//        TreeNode* tree = GenerateRandomBST(max_level, min_val, max_val);
//        if (maxWidth(tree) != maxWidthTest(tree)) {
//            ASSERT_TRUE(false);
//        }
//
//        FreeBST(tree);
//    }
//
//    cout << "test success" << endl;
//    cout << "binary tree max width test end " << endl;
//}