#include <algorithm>
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
    判断二叉树是否是搜索二叉树
*/
struct Info {
    int height;
    bool is_balanced;

    Info(int h, bool b):height(h), is_balanced(b) {
    }
};

static Info process(Node* head) {
    if (head == nullptr) {
        return Info(-1, true);
    }

    bool is_balanced = true;
    Info left_info = process(head->left);
    Info right_info = process(head->right);
    if (!left_info.is_balanced || !right_info.is_balanced) {
        is_balanced = false;
    }

    if (std::abs(left_info.height - right_info.height) > 1) {
        is_balanced = false;
    }

    int height = std::max(left_info.height, right_info.height) + 1;
    return Info(height, is_balanced);
}

static bool IsBalanced(Node* head) {
    if (head == nullptr) {
        return true;
    }

    return process(head).is_balanced;
}

static int process1(Node* node, bool& is_balanced) {
    if (node == nullptr || !is_balanced) {
        return -1;
    }

    int left_h = process1(node->left, is_balanced);
    int right_h = process1(node->right, is_balanced);
    if (std::abs(left_h - right_h) > 1) {
        is_balanced = false;
    }

    return std::max(left_h, right_h) + 1;
}

static bool test(Node* head) {
    if (head == nullptr) {
        return true;
    }

    bool is_balanced = true;
    process1(head, is_balanced);
    return is_balanced;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max_val = 100;
    int max_level = 6;
    int test_times = 10000;

    for (int i = 0; i < test_times; ++i) {
        Node* tree = GenerateRandomTree(max_val, max_level);
        if (IsBalanced(tree) != test(tree)) {
            PrintTree(tree);
            cout << "test failed" << endl;
            FreeTree(tree);
            break;
        }

        FreeTree(tree);
    }

    cout << "test end" << endl;
    return 0;
}
