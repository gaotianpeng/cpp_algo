#include <list>
#include <map>
#include <set>

class GraphNode;

struct GraphEdge {
    int weight;
    GraphNode* from;
    GraphNode* to;

    GraphEdge(int weight, GraphNode* from, GraphNode* to) {
        this->weight = weight;
        this->from = from;
        this->to = to;
    }
};

struct GraphNode{
    int value;
    int in;
    int out;
    std::list<GraphNode*> nexts;
    std::list<GraphEdge*> edges;

    GraphNode(int value) {
        this->value = value;
        in = 0;
        out = 0;
    }
};

struct Graph {
    std::map<int, GraphNode*> nodes;
    std::set<GraphEdge*> edges;
};

// matrix 所有的边
// N*3 的矩阵
// [weight, from节点上面的值，to节点上面的值]
//
// [ 5 , 0 , 7]
// [ 3 , 0,  1]
//

Graph* createGraph(int** matrix ,int row, int cols = 3) {
    Graph* graph = new Graph;
    for (int i = 0; i < row; ++i) {
        int weight = matrix[i][0];
        int from = matrix[i][1];
        int to = matrix[i][2];

        if (!(graph->nodes.find(from) != graph->nodes.end())) {
            graph->nodes.insert({from, new GraphNode(from)});
        }
        if (!(graph->nodes.find(to) != graph->nodes.end())) {
            graph->nodes.insert({to, new GraphNode(to)});
        }

        GraphNode* from_node = graph->nodes[from];
        GraphNode* to_node = graph->nodes[to];
        GraphEdge* new_edge = new GraphEdge(weight, from_node, to_node);
        from_node->nexts.push_back(to_node);
        from_node->out++;
        from_node->in++;
        from_node->edges.push_back(new_edge);
        graph->edges.insert(new_edge);
    }

    return graph;
}