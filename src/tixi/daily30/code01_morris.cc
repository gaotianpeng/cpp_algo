#include <iostream>
#include <vector>
#include <stack>
#include "common/test_utils.h"
using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;

    TreeNode(int v): val(v) {
    }
};

static TreeNode* generate(int max_level, int cur_level, int max_val) {
    if (cur_level > max_level || Random::nextDouble() > 0.5) {
        return nullptr;
    }
    TreeNode* node = new TreeNode(Random::nextInt(0, max_val));

    node->left = generate(max_level, ++cur_level, max_val);
    node->right = generate(max_level, ++cur_level, max_val);

    return node;
}

static void FreeBinaryTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    
    std::vector<TreeNode*> nodes;
    std::stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        nodes.push_back(node);
        if (node->left != nullptr) {
            s.push(node->left);
        }
        if (node->right != nullptr) {
            s.push(node->right);
        }
    }

    for (int i = 0; i < nodes.size(); ++i) {
        delete nodes[i];
    }
}

static TreeNode* GenerateBinaryTree(int max_level, int max_val) {
    return generate(max_level, 0, max_val);
}

static void PreOrder(TreeNode* root, vector<int>& ans) {
    if (root == nullptr) {
        return;
    }
    
    std::stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        ans.push_back(node->val);
        if (node->right != nullptr) {
            s.push(node->right);
        }
        if (node->left != nullptr) {
            s.push(node->left);
        }
    }
}

} // namespace

static void PreMorris(TreeNode* root, vector<int>& ans) {
    if (root == nullptr) {
        return;
    }

    TreeNode* cur = root;
    TreeNode* most_right = nullptr;
    while (cur != nullptr) {
        most_right = cur->left;
        if (most_right != nullptr) {
            while (most_right->right != nullptr && most_right->right != cur) {
                most_right = most_right->right;
            }

            if (most_right->right == nullptr) {
                ans.push_back(cur->val);
                most_right->right = cur;
                cur = cur->left;
                continue;
            } else {
                most_right->right = nullptr;
            }
        } else {
            ans.push_back(cur->val);
        }

        cur = cur->right;
    }
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int test_times = 100000;
    int max_val = 100;
    int max_level = 10;
    for (int i = 0; i < test_times; ++i) {
        TreeNode* root = GenerateBinaryTree(max_level, max_val);
        vector<int> ans1, ans2;
        PreOrder(root, ans1);
        PreMorris(root, ans2);
        if (!ArrayUtils::isEqual(ans1, ans2)) {
            cout << "test failed" << endl;
            ArrayUtils::printArray(ans1);
            ArrayUtils::printArray(ans2);
            FreeBinaryTree(root);
            break;
        }
        FreeBinaryTree(root);
    }
 
    cout << "test end" << endl;
    return 0;
}