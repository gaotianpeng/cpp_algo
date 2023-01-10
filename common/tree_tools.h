#ifndef CPP_ALGO_COMMON_TREE_TOOLS_H_
#define CPP_ALGO_COMMON_TREE_TOOLS_H_

namespace tools {

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int v) {
        val = v;
    }
};

TreeNode* GenerateRandomBST(int max_level, int min_val, int max_val);

void FreeBST(TreeNode* tree);

} // namespace tools

#endif // CPP_ALGO_COMMON_TREE_TOOLS_H_
