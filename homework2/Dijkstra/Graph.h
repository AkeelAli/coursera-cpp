#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

using namespace std;

//forward delcaration
class Node;

class Edge {
private:
    Node *u;
    Node *v;
    int cost;

public:
    // Clients shouldn't instantiate edges directly (but rather thru Nodes)
    Edge(Node *u, Node *v, int cost): u(u), v(v), cost(cost) {};

    Node *get_v() { return v; }
    Node *get_u() { return u; }
    int get_cost() { return cost; }
};

class Node {
private:
    int id;
    vector<Edge> edges; // outgoing edges

public:
    Node(int id): id(id) {};
    ~Node() { edges.clear(); }
    int get_id() { return id; }
    void add_edge(Node *v, int cost)
    {
        Edge new_edge(this, v, cost);
        edges.push_back(new_edge);
    }
    void display_edges()
    {
        for (unsigned int i = 0; i < edges.size(); i++) {
            Edge edge = edges[i];
            cout << id << " - " << edge.get_v()->get_id() << endl;
        }
    }
};

class Graph {
private:
    vector<Node *> nodes;

public:
    Graph() {};
    ~Graph()
    {
        //free
    }

    // assumption is that input is sane and correct
    Graph(unsigned int num_nodes, unsigned int density,
          int min_edge_cost, int max_edge_cost)
    {

    }

    void add_node(Node *n)
    {
        nodes.push_back(n);
    }
};
#endif // GRAPH_H
