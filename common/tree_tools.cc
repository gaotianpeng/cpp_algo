#include "tree_tools.h"
#include "random.h"
#include <queue>

namespace tools {

static TreeNode* generate(int level, int max_level, int min_val, int max_val) {
    if (level > max_level || Random::random() < 0.5) {
        return nullptr;
    }

    TreeNode* head = new TreeNode(Random::random(min_val, max_val));
    head->left = generate(level + 1, max_level, min_val, max_val);
    head->right = generate(level + 1, max_level, min_val, max_val);
    return head;
}

TreeNode* GenerateRandomBST(int max_level, int min_val, int max_val) {
    return generate(1, max_val, min_val, max_val);
}

void FreeBST(TreeNode* tree) {
    if (tree == nullptr) {
        return;
    }

    std::queue<TreeNode*> node_queue;
    node_queue.push(tree);

    while (node_queue.empty()) {
        TreeNode* cur_node = node_queue.front();
        if (cur_node->left != nullptr) {
            node_queue.push(cur_node->left);
        }
        if (cur_node->right != nullptr) {
            node_queue.push(cur_node->right);
        }
        delete cur_node;
        cur_node = nullptr;
    }
}

} // namespace tools

