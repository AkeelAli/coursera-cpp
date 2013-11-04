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
        /*
        for (unsigned int i = 0; i < nodes.size(); i++) {
            delete(nodes[i]);
        }
        */
        nodes.clear();
    }

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

const double INFINITY = 99999999.0;

class ShortestPath
{
private:
    //priority_queue<Node *,vector<Node *>, greater_dist > open_set;
    Graph *g;

    bool set_contains(vector<int>& vector_set, int id)
    {
        for (unsigned int i = 0; i < vector_set.size(); i++)
        {
            if (vector_set[i] == id)
                return true;
        }

        return false;
    }

    void display_set(vector<int>& vector_set)
    {
        for (unsigned int i = 0; i < vector_set.size(); i++)
        {
            Node *n = g->get_node(vector_set[i]);
            cout << vector_set[i] << " (" << n->get_distance() << ") ";
        }
        cout << endl;
    }

    /* Generic function poping minimum from any vector of ints */
    int pop_min(vector<int>& vector_set)
    {
        double minimum = INFINITY;
        int min_node = -1;
        int idx_remove = -1;

        //cout << "Open set before pop: ";
        //display_set(vector_set);

        if (vector_set.size() == 0) {
            cout << "pop min from empty set";
            return -1;
        }

        for (unsigned int i = 0; i < vector_set.size(); i++)
        {
            Node *n = g->get_node(vector_set[i]);

            if (n->get_distance() < minimum) {
                min_node = vector_set[i];
                idx_remove = i;
                minimum = n->get_distance();
            }
        }

        // remove it
        if (idx_remove != -1)
            vector_set.erase(vector_set.begin() + idx_remove);

        //cout << "Open set after pop: ";
        //display_set(vector_set);

        return min_node;
    }
public:
    ShortestPath(Graph *g): g(g) {}
    ~ShortestPath() {}

    double path_size(int src, int dst, bool average)
    {
        //cout << endl;
        // set of nodes that we can visit
        vector<int> open_set;
        // instead of marking nodes as visited, we use a closed_set
        vector<int> closed_set;

        if (!g->contains(src) || !g->contains(dst))
            return -1;

        vector<Node *> nodes = g->get_nodes();

        // init distances to infinity
        for (unsigned int i = 0; i < nodes.size(); i++)
        {
            nodes[i]->set_distance(INFINITY);
        }
        // set src distance to 0 & add to open_set
        g->get_node(src)->set_distance(0.0);
        open_set.push_back(src);

        int latest_added_id = src;
        Node *latest_added = g->get_node(latest_added_id);

        while (open_set.size() > 0) {
            // add smallest in open_set to closed_set
            latest_added_id = pop_min(open_set);
            latest_added = g->get_node(latest_added_id);
            if (!latest_added) {
                cout << "Can't find node (" << latest_added_id << ") in graph " << endl;
                return -1;
            }
            //cout << "    Adding node " << latest_added_id << " to closed set" << endl;
            closed_set.push_back(latest_added_id);

            // relaxation step
            vector<Edge> edges = latest_added->get_edges();
            double starting_distance = latest_added->get_distance();

            for (unsigned int i = 0; i < edges.size(); i++)
            {
                Node *v = edges[i].get_v();
                if (set_contains(closed_set, v->get_id()))
                    continue; // skip already visited nodes

                //cout << "    Relaxing node " << v->get_id() << endl;
                double current_distance = v->get_distance();
                double cost = edges[i].get_cost();

                double new_distance = starting_distance + cost;

                if (new_distance < current_distance)
                    v->set_distance(new_distance);

                if (!set_contains(open_set, v->get_id()))
                    open_set.push_back(v->get_id());
            }

            //display_set(open_set);
        }

        if (average) {
            double sum = 0;

            for (unsigned int i = 0; i < closed_set.size(); i++) {
                sum += g->get_node(closed_set[i])->get_distance();
            }

            //cout << sum << " / " << closed_set.size() - 1 << endl;
            return (sum/(closed_set.size() - 1));  // -1 to remove src
        }

        Node *dst_node = g->get_node(dst);

        if (dst_node->get_distance() == INFINITY) {
            //cout << dst << " is unreachable from " << src << "!" << endl;
            return -1.0;
        } else {
            return dst_node->get_distance();
        }
    }
};
#endif // GRAPH_H
