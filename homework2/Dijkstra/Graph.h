#ifndef GRAPH_H
#define GRAPH_H

/*
 *
 * This Header file defines interdependent classes for Graph, Node & Edge
 *
 */

#include <vector>
#include <iostream>
#include <queue>

using namespace std;

//forward declaration of Node
class Node;

/*
 * Class Edge
 */
class Edge {
private:
    Node *u;
    Node *v;
    double cost;

public:
    // Clients shouldn't instantiate edges directly (but rather thru Nodes)
    Edge(Node *u, Node *v, double cost): u(u), v(v), cost(cost) {};

    Node *get_u() { return u; }
    Node *get_v() { return v; }
    double get_cost() { return cost; }
};

/*
 * Class Node
 *
 *  Maintains a vector of edges representing the adjacency list
 */
class Node {
private:
    int id;
    // TODO change these to pointers to edges
    vector<Edge> edges; // outgoing edges

    double distance;

public:
    Node(int id): id(id) { distance = 0;};
    ~Node() { edges.clear(); }

    int get_id() { return id; }

    void add_edge(Node *v, double cost)
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
            cout << id << " - " << edge.get_v()->get_id() << " (" << edge.get_cost() << ") " << endl;
        }
    }

    void set_distance(double distance)
    {
        this->distance = distance;
    }

    double get_distance()
    {
        return distance;
    }

    vector<Edge> get_edges()
    {
        return edges;
    }
};

/*
 * Class Graph
 *
 *  Maintains a vector of Node objects, each of which having an adjacency list
 */
class Graph {
private:
    vector<Node *> nodes;

public:
    Graph() {}
    ~Graph() { nodes.clear(); }

    Graph(vector<Node *> nodes): nodes(nodes) {}

    /*
     * Constructor that builds a random undirected graph
     *
     * Assumes input is sane and correct
     */
    Graph(unsigned int num_nodes, double density,
          double min_edge_cost, double max_edge_cost)
    {
        double chance;
        double rand_cost;

        // add all the nodes (from 1 to num_nodes)
        for (unsigned int id = 1; id <= num_nodes; id++) {
            Node *n = new Node(id);

            add_node(n);
        }

        // add the edges to the nodes
        for (unsigned int i = 0; i < num_nodes; i++) {
            for (unsigned int j = i + 1; j < num_nodes; j++) {
                chance = rand() * 1.0 / RAND_MAX; // RAND_MAX is the max value returned by rand()

                if (chance < density) {
                    // generate a random double cost between min_edge_cost and max_edge_cost
                    rand_cost = (rand() * 1.0 * (max_edge_cost - min_edge_cost) )/RAND_MAX + min_edge_cost;

                    // add the edge to both nodes
                    nodes[i]->add_edge(nodes[j], rand_cost);
                    nodes[j]->add_edge(nodes[i], rand_cost);
                }
            }
        }
    }

    void add_node(Node *n)
    {
        nodes.push_back(n);
    }

    void display_nodes()
    {
        for (unsigned int i = 0; i < nodes.size(); i++) {
            cout << nodes[i]->get_id() << endl;
            nodes[i]->display_edges();
        }
    }

    Node *get_node(int id)
    {
        for (unsigned int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->get_id() == id) {
                return nodes[i];
            }
        }
        return 0;
    }

    vector<Node *> get_nodes()
    {
        return nodes;
    }

    bool contains(int id)
    {
        for (unsigned int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->get_id() == id) {
                return true;
            }
        }

        return false;
    }

    unsigned int num_nodes()
    {
        return nodes.size();
    }

};

#endif // GRAPH_H
