#include <queue>
#include <set>
#include <iostream>
#include "graph.h"

using namespace std;

static void bfs(GraphNode* start_node) {
    if (start_node == nullptr) {
        return;
    }

    queue<GraphNode*> node_que;
    set<GraphNode*> node_set;
    node_que.push(start_node);
    node_set.insert(start_node);

    while (!node_que.empty()) {
        GraphNode* cur = node_que.front();
        node_que.pop();
        node_set.insert(cur);
        cout << cur->value << endl;
        for (auto next: cur->nexts) {
            if (!(node_set.find(next) != node_set.end())) {
                node_set.insert(next);
                node_que.push(next);
            }
        }
    }
}