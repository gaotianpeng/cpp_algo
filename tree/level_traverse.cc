#include <iostream>
#include <queue>
#include "tree_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

static void LevelTraverseBTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    queue<TreeNode*> node_queue;
    node_queue.push(root);
    while (!node_queue.empty()) {
        TreeNode* cur_node = node_queue.front();
        cout << cur_node->val << " ";
        node_queue.pop();
        if (cur_node->left != nullptr) {
            node_queue.push(cur_node->left);
        }
        if (cur_node->right != nullptr) {
            node_queue.push(cur_node->right);
        }
    }
    cout << endl;
}

//TEST(TreeTest, LevelTraverseTest) {
//    TreeNode* tree = new TreeNode(1);
//    tree->left = new TreeNode(2);
//    tree->right = new TreeNode(3);
//    tree->left->right = new TreeNode(4);
//    tree->right->left = new TreeNode(5);
//    LevelTraverseBTree(tree);
//    FreeBST(tree);
//
//    cout << "level traverse tree test start" << endl;
//
//    int max_level = 4;
//    int min_val = 1;
//    int max_val = 9;
//    int test_time = 10;
//    for (int i = 0; i < test_time; ++i) {
//        TreeNode* tree = GenerateRandomBST(max_level, min_val, max_val);
//        LevelTraverseBTree(tree);
//        FreeBST(tree);
//    }
//
//    cout << "test success" << endl;
//    cout << "level traverse tree test end " << endl;
//}