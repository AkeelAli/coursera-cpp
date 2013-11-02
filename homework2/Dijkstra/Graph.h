#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <queue>

using namespace std;

//forward delcaration
class Node;

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

class Graph {
private:
    vector<Node *> nodes;

public:
    Graph() {}
    ~Graph()
    {
        // TODO does clear take care of deleting?
        for (unsigned int i = 0; i < nodes.size(); i++) {
            delete(nodes[i]);
        }
        nodes.clear();
    }

    /* TODO does distance have to be double, i.e. could be any rational number in range?? */
    // assumption is that input is sane and correct
    Graph(unsigned int num_nodes, double density,
          double min_edge_cost, double max_edge_cost)
    {
        double chance;
        double rand_cost;
        // seed
        srand (time(0));

        // add all the nodes
        for (unsigned int i = 0; i < num_nodes; i++) {
            Node *n = new Node(i);

            add_node(n);
        }

        // add the edges to the nodes
        for (unsigned int i = 0; i < num_nodes; i++) {
            for (unsigned int j = i + 1; j < num_nodes; j++) {
                chance = rand() * 1.0 / RAND_MAX; // RAND_MAX is the max value returned by rand()

                if (chance < density) {
                    rand_cost = (rand() * 1.0 * (max_edge_cost - min_edge_cost) )/RAND_MAX + min_edge_cost;

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

    // TODO untested!
    Node *get_node(int id)
    {
        for (unsigned int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->get_id() == id) {
                return nodes[i];
            }
        }
        return 0;
    }

    // TODO for now, return all nodes (not good practice)
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

const double INFINITY = 99999999;

class ShortestPath
{
private:
    //priority_queue<Node *,vector<Node *>, greater_dist > open_set;
    vector<int> open_set;
    vector<int> closed_set;
    Graph *g;

    int pop_min()
    {
        double minimum = INFINITY;
        int min_node = 0;
        int idx_remove = 0;

        for (unsigned int i = 0; i < open_set.size(); i++)
        {
            Node *n = g->get_node(open_set[i]);

            if (n->get_distance() < minimum) {
                min_node = open_set[i];
                idx_remove = i;
            }
        }

        // remove it
        open_set.erase(open_set.begin() + idx_remove);

        return min_node;
    }
public:
    ShortestPath(Graph *g): g(g) {}

    double path_size(int src, int dst)
    {
        if (!g->contains(src) || !g->contains(dst))
            return -1;

        vector<Node *> nodes = g->get_nodes();

        closed_set.push_back(src);

        g->get_node(src)->set_distance(0.0);
        for (unsigned int i = 0; i < nodes.size(); i++)
        {
            nodes[i]->set_distance(INFINITY);
        }

        int latest_added_id = src;
        Node *latest_added = g->get_node(latest_added_id);

        while (latest_added_id != dst &&
               closed_set.size() == g->num_nodes()) {
            // relaxation step
            vector<Edge> edges = latest_added->get_edges();
            double starting_distance = latest_added->get_distance();

            for (unsigned int i = 0; i < edges.size(); i++)
            {
                Node *v = edges[i].get_v();
                double current_distance = v->get_distance();
                double cost = edges[i].get_cost();

                double new_distance = starting_distance + cost;

                if (new_distance < current_distance)
                    v->set_distance(new_distance);

                open_set.push_back(v->get_id());
            }

            // add smallest in open_set to closed_set
            latest_added_id = pop_min();
            closed_set.push_back(latest_added_id);
            latest_added = g->get_node(latest_added_id);
        }

        if (latest_added_id == dst) {
            return latest_added->get_distance();
        } else {
            return -1;
        }
    }
};
#endif // GRAPH_H
