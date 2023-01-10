#include <iostream>
#include "random.h"
#include "tree_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

void PreOrder(TreeNode* tree) {
    if (tree == nullptr) {
        return;
    }

    cout << tree->val << " ";
    PreOrder(tree->left);
    PreOrder(tree->right);
}

void InOrder(TreeNode* tree) {
    if (tree == nullptr) {
        return;
    }

    InOrder(tree->left);
    cout << tree->val << " ";
    InOrder(tree->right);
}

void PosOrder(TreeNode* tree) {
    if (tree == nullptr) {
        return;
    }

    PosOrder(tree->left);
    PosOrder(tree->right);
    cout << tree->val << " ";
}

//TEST(TreeTest, BinTreeTraverseRecurseTest) {
//    cout << "binary tree traverse recurse test start" << endl;
//    /*
//     *               1
//     *           2      3
//     *             4   5
//     *  pre order: 1, 2, 4, 3, 5
//     *  in  order: 2, 4, 1, 5, 3
//     *  pos order: 4, 2, 5, 3, 1
//     */
//    TreeNode* tree = new TreeNode(1);
//    tree->left = new TreeNode(2);
//    tree->right = new TreeNode(3);
//    tree->left->right = new TreeNode(4);
//    tree->right->left = new TreeNode(5);
//    PreOrder(tree);
//    cout << endl;
//    InOrder(tree);
//    cout << endl;
//    PosOrder(tree);
//    cout << endl;
//    FreeBST(tree);
//    cout << "test success" << endl;
//    cout << "binary tree traverse recurse test end " << endl;
//}