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

    Node *get_u() { return u; }
    Node *get_v() { return v; }
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
    bool is_edge(int id)
    {
        for (unsigned int i = 0; i < edges.size(); i++) {
            if (id == edges[i].get_v()->get_id()) {
                return true;
            }
        }

        return false;
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

        // add all the nodes
        for (unsigned int i = 0; i < num_nodes; i++) {
            Node n(i);

            add_node(&n);
        }

        // add the edges to the nodes
        for (unsigned int i = 0; i < num_nodes; i++) {
            for (unsigned int j = i + 1; j < num_nodes; j++) {
                // if edge not existent already, then run random density?
                // TODO
            }
        }
    }

    void add_node(Node *n)
    {
        nodes.push_back(n);
    }
};
#endif // GRAPH_H
