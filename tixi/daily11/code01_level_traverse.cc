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

static Node* generate(int level, int max_level, int max_val, vector<int>& vals) {
    if (level > max_level || Math::random() > 0.5) {
        return nullptr;
    }

    Node* node = new Node(RandomVal(-max_val, max_val));
    vals.emplace_back(node->val);
    node->left = generate(level + 1, max_level, max_val, vals);
    node->right = generate(level + 1, max_level, max_val, vals);
    return node;
}

static Node* GenerateRandomTree(int max_val, int max_level, vector<int>& vals) {
    int level = 1;

    queue<Node*> que;
    Node* node = nullptr;
    Node* ans = nullptr;
    if (Math::random() > 0.5) {
        node = new Node(RandomVal(-max_val, max_val));
        vals.emplace_back(node->val);
        que.push(node);
        ans = node;
    } else {
        return nullptr;
    }

    while (level < max_level) {
        while (!que.empty()) {
            Node* cur = que.front();
            que.pop();
            cur->left = Math::random() > 0.5 ? nullptr : new Node(RandomVal(-max_val, max_val));
            if (cur->left) {
                vals.emplace_back(cur->left->val);
            }
            cur->right = Math::random() > 0.5 ? nullptr : new Node(RandomVal(-max_val, max_val));
            if (cur->right) {
                vals.emplace_back(cur->right->val);
            }
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


static void LevelTraverse(Node* cur, vector<int>& vals) {
    if (cur == nullptr) {
        return;
    }

    queue<Node*> que;
    que.push(cur);
    while (!que.empty()) {
        Node* node = que.front();
        vals.emplace_back(node->val);
        que.pop();
        if (node->left) {
            que.push(node->left);
        }
        if (node->right) {
            que.push(node->right);
        }
    }
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max_val = 100;
    int max_level = 30;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        vector<int> vals1, vals2;
        Node* tree = GenerateRandomTree(max_val, max_level, vals1);
        LevelTraverse(tree, vals2);
        if (!IsEqual(vals1, vals2)) {
            cout << "test failed" << endl;
            Print(vals1);
            Print(vals2);
            FreeTree(tree);
            break;
        }

        FreeTree(tree);
    }

    cout << "test end" << endl;
    return 0;
}