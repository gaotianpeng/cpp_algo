#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <random>
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
    Node* parent = nullptr;
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
        node->parent = nullptr;
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
                cur->left->parent = cur;
                que.push(cur->left);
            }

            if (cur->right != nullptr) {
                cur->right->parent = cur;
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

static Node* GetRandomNodeFromBT(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    queue<Node*> que;
    vector<Node*> nodes;
    que.push(head);
    while (!que.empty()) {
        Node* cur = que.front();
        que.pop();
        nodes.emplace_back(cur);
        if (cur->left) {
            que.push(cur->left);
        }
        if (cur->right) {
            que.push(cur->right);
        }
    }

    int n = nodes.size();
    return nodes[RandomVal(0, n - 1)];
}

}  // namespace

/*
    二叉树结构如下定义：
    Class Node {
        V value;
        Node left;
        Node right;
        Node parent;
    }
    给你二叉树中的某个节点，返回该节点的后继节点

    某一节点的后继节点是二叉树中序遍历序列中该节点的后一节点
*/
static Node* GetLeftestNode(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}
static Node* GetSuccessorNode(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->right != nullptr) {
        return GetLeftestNode(node->right);
    } else {
        Node* parent = node->parent;
        while (parent != nullptr && parent->right == node) {
            node = parent;
            parent = node->parent;
        }

        return parent;
    }
}

static Node* test(Node* head, Node* node) {
    if (head == nullptr || node == nullptr) {
        return nullptr;
    }

    vector<Node*> in_nodes;
    stack<Node*> nodes;
    Node* cur = head;
    while (!nodes.empty() || cur != nullptr) {
        if (cur != nullptr) {
            nodes.push(cur);
            cur = cur->left;
        } else {
            cur = nodes.top();
            nodes.pop();
            in_nodes.emplace_back(cur);
            cur = cur->right;
        }
    }

    for (int i = 0; i < in_nodes.size(); ++i) {
        if (node == in_nodes[i] && i != in_nodes.size() - 1) {
            return in_nodes[i+1];
        }
    }

    return nullptr;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max_val = 100;
    int max_level = 5;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        Node* head = GenerateRandomTree(max_val, max_level);
        Node* node = GetRandomNodeFromBT(head);
        if (GetSuccessorNode(node) != test(head, node)) {
            cout << "test failed" << endl;
            PrintTree(head);
            FreeTree(head);
            break;
        }

        FreeTree(head);
    }

    cout << "test end" << endl;
    return 0;
}