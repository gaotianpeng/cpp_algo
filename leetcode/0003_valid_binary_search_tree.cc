#include <algorithm>
/*
    98 验证二叉搜索树
        给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

        有效 二叉搜索树定义如下：

        节点的左子树只包含 小于 当前节点的数。
        节点的右子树只包含 大于 当前节点的数。
        所有左子树和右子树自身必须也是二叉搜索树。
 */
class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    struct Info {
        bool is_valid;
        int max_val;
        int min_val;
        Info(bool i, int max, int min):
            is_valid(i), max_val(max), min_val(min) {}
    };
public:

    bool isValidBST(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        Info* info = process(root);
        bool ans = info->is_valid;
        delete info;
        return ans;
    }

private:
    Info* process(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }

        Info* left = process(root->left);
        Info* right = process(root->right);
        int cur_max = root->val;
        if (left != nullptr) {
            cur_max = std::max(cur_max, left->max_val);
        }
        if (right != nullptr) {
            cur_max = std::max(cur_max, right->max_val);
        }
        int cur_min = root->val;
        if (left != nullptr) {
            cur_min = std::min(cur_min, left->min_val);
        }
        if (right != nullptr) {
            cur_min = std::min(cur_min, right->min_val);
        }
        bool is_bst = true;
        if (left != nullptr && !left->is_valid) {
            is_bst = false;
        }
        if (right != nullptr && !right->is_valid) {
            is_bst = false;
        }
        if (left != nullptr && cur_min <= left->max_val) {
            is_bst = false;
        }
        if (right != nullptr && cur_max >= right->min_val) {
            is_bst = false;
        }

        return new Info(is_bst, cur_max, cur_min);
    }
};