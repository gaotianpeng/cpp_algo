#include <algorithm>
#include <iostream>
#include <random>
#include <queue>
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

static Node* GenerateRandomTree(int max_val, int max_level) {
    int level = 1;

    queue<Node*> que;
    Node* ans = nullptr;
    if (Math::random() > 0.5) {
        Node* node = new Node(RandomVal(-max_val, max_val));
        que.push(node);
        ans = node;
    } else {
        return nullptr;
    }

    queue<Node*> cur_level_nodes;
    while (level <= max_level) {
        while (!que.empty()) {
            Node* cur = que.front();
            que.pop();
            cur_level_nodes.push(cur);
        }

        while (!cur_level_nodes.empty()) {
            Node* cur = cur_level_nodes.front();
            cur_level_nodes.pop();
            cur->left = Math::random() > 0.5 ? nullptr : 
                    new Node(RandomVal(-max_val, max_val));
            cur->right = Math::random() > 0.5 ? nullptr : 
                    new Node(RandomVal(-max_val, max_val));

            if (cur->left != nullptr) {
                que.push(cur->left);
            }
            if (cur->right != nullptr) {
                que.push(cur->right);
            }
        }

        if (que.empty()) {
            break;
        }

        ++level;
    }

    return ans;
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
    求二叉树最宽的层有多少个节点
*/
static int MaxWidth(Node* head) {
    if (head == nullptr) {
        return 0;
    }

    queue<Node*> que;
    que.push(head);
    Node* cur_end = head;
    Node* next_end = nullptr;
    
    int ans = 0;
    int cur_level_nodes = 0;
    while (!que.empty()) {
        Node* cur = que.front();
        que.pop();
        if (cur->left != nullptr) {
            que.push(cur->left);
            next_end = cur->left;
        }
        if (cur->right != nullptr) {
            que.push(cur->right);
            next_end = cur->right;
        }

        cur_level_nodes++;
        if (cur == cur_end) {
            ans = std::max(cur_level_nodes, ans);
            cur_end = next_end;
            cur_level_nodes = 0;
        }
    }

    return ans;
}

static int test(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    int ans = 0;
    queue<Node*> que;
    queue<Node*> cur_level_nodes;
    que.push(node);
    int cur_level_width = que.size();
    ans = std::max(cur_level_width, ans);
    while (!que.empty()) {
        while (!que.empty()) {
            cur_level_nodes.push(que.front());
            que.pop();
        }

        while (!cur_level_nodes.empty()) {
            Node* cur = cur_level_nodes.front();
            cur_level_nodes.pop();
            if (cur->left != nullptr) {
                que.push(cur->left);
            }
            if (cur->right != nullptr) {
                que.push(cur->right);
            }
        }
        cur_level_width = que.size();
        ans = std::max(ans, cur_level_width);
    }

    return ans;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max_val = 100;
    int max_level = 5;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        Node* tree = GenerateRandomTree(max_val, max_level);
        if (MaxWidth(tree) != test(tree)) {
            cout << "test failed" << endl;
            PrintTree(tree);
            FreeTree(tree);
            break;
        }

        FreeTree(tree);
    }

    cout << "test end" << endl;
    return 0;
}