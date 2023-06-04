#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <stack>
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


static Node* GenerateRandomTree(int max_val, int max_level, int& max_width) {
    int level = 1;

    queue<Node*> que;
    Node* ans = nullptr;
    int cur_level_width = 0;
    if (Math::random() > 0.5) {
        Node* node = new Node(RandomVal(-max_val, max_val));
        que.push(node);
        ans = node;
        cur_level_width = 1;
        max_width = std::max(cur_level_width, max_width);
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
            cur->left = Math::random() > 0.5 ? nullptr : new Node(RandomVal(-max_val, max_val));
            cur->right = Math::random() > 0.5 ? nullptr : new Node(RandomVal(-max_val, max_val));
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
    
        cur_level_width = que.size();
        max_width = std::max(cur_level_width, max_width);
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

static void Print(const vector<int>& vals) {
    for (auto& elem: vals) {
        cout << elem << " ";
    }
    cout << endl;
}

static bool IsEqual(const vector<int>& vals1, const vector<int>& vals2) {
    if (vals1.size() != vals2.size()) {
        return false;
    }

    for (int i = 0; i < vals1.size(); ++i) {
        if (vals1[i] != vals2[i]) {
            return false;
        }
    }

    return true;
}

}  // namespace


static int MaxWidth(Node* head) {
    if (head == nullptr) {
        return 0;
    }

    queue<Node*> que;
    que.push(head);
    // 当前层，最右节点是谁
    Node* cur_end = head;
    // 下一层，最右节点是谁
    Node* next_end = nullptr;
    int max = 0;
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
            max = std::max(max, cur_level_nodes);
            cur_level_nodes = 0;
            cur_end = next_end;
        }
    }

    return max;
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max_val = 100;
    int max_level = 30;
    int test_times = 100;

    for (int i = 0; i < test_times; ++i) {
        int max_width = 0;
        Node* tree = GenerateRandomTree(max_val, max_level, max_width);
        if (MaxWidth(tree) != max_width) {
            cout << "test failed" << endl;
            FreeTree(tree);
            break;
        }

        FreeTree(tree);
    }

    cout << "test end" << endl;
    return 0;
}