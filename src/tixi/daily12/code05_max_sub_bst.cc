#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <vector>

using namespace std;

/*
    for test
*/
namespace {

class Math {
public:
    static double random() {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
};

static int RandomVal(int min_val, int max_val) {
    return (int)(Math::random() * (max_val - min_val + 1)) + min_val;
}

struct Node {
    int val  = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int v):val(v) {
    }
};

static Node* generate(int cur_level, int max_level, int max_val) {
    if (cur_level > max_level || Math::random() > 0.6) {
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
    给定一棵二叉树的头节点head，
    返回这颗二叉树中最大的二叉搜索子树的大小
*/
struct Info {
    bool valid;
    int bst_size;
    int all_size;
    int min;
    int max;

    Info(int b, int a, int mi, int ma, bool v = true):
        bst_size(b), all_size(a), min(mi), max(ma), valid(v) {
    }
};

static Info process(Node* head) {
    if (head == nullptr) {
        return Info(0, 0, 0, 0, false);
    }

    int all_size = 1;
    int bst_size = 0;
    int max_val = head->val;
    int min_val = head->val;


    Info left_info = process(head->left);
    Info right_info = process(head->right);
    if (left_info.valid) {
        max_val = std::max(max_val, left_info.max);
        min_val = std::min(min_val, left_info.min);
        all_size += left_info.all_size;
    }

    if (right_info.valid) {
        max_val = std::max(max_val, right_info.max);
        min_val = std::min(min_val, right_info.min);
        all_size += right_info.all_size;
    }

    int p1 = -1;
    if (left_info.valid) {
        p1 = left_info.bst_size;
    }
    
    int p2 = -1;
    if (right_info.valid) {
        p2 = right_info.bst_size;
    }
    
    int p3 = -1;
    bool is_left_bst = !left_info.valid ? true : 
        left_info.all_size == left_info.bst_size;
    bool is_right_bst = !right_info.valid ? true :
        right_info.all_size == right_info.bst_size;
    if (is_left_bst && is_right_bst) {
        bool left_max_less_node = !left_info.valid ? true :
            left_info.max < head->val;
        bool right_min_more_node = !right_info.valid ? true :
            right_info.min > head->val;

        if (left_max_less_node && right_min_more_node) {
            int left_size = left_info.valid ? left_info.all_size : 0;
            int right_size = right_info.valid ? right_info.all_size : 0;
            p3 = left_size + right_size + 1;
        }
    }

    bst_size = std::max(std::max(p1, p2), p3);
    return Info(bst_size, all_size, min_val, max_val);
}

static int GetMaxSubBST(Node* head) {
    if (head == nullptr) {
        return 0;
    }

    return process(head).bst_size;
}

static void InTraverse(Node* head, vector<int>& vals) {
    if (head == nullptr) {
        return;
    }

    stack<Node*> nodes;
    Node* cur = head;
    while (!nodes.empty() || cur != nullptr) {
        if (cur != nullptr) {
            nodes.push(cur);
            cur = cur->left;
        } else {
            cur = nodes.top();
            nodes.pop();
            vals.emplace_back(cur->val);
            cur = cur->right;
        }
    }
}

static int GetBSTSize(Node* head) {
    if (head == nullptr) {
        return 0;
    }

    vector<int> vals;
    InTraverse(head, vals);
    for (int i = 1; i < vals.size(); ++i) {
        if (vals[i] <= vals[i-1]) {
            return 0;
        }
    }

    return vals.size();
}

static int test(Node* head) {
    if (head == nullptr) {
        return 0;
    }

    int ans = GetBSTSize(head);
    if (ans != 0) {
        return ans;
    }

    return std::max(test(head->left), test(head->right));
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max_val = 100;
    int max_level = 6;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        Node* tree = GenerateRandomTree(max_val, max_level);
        if (GetMaxSubBST(tree) != test(tree)) {
            PrintTree(tree);
            cout << GetMaxSubBST(tree) << endl;
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
