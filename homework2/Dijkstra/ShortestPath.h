#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

/*
 * This Header file defines the ShortestPath class implementing Dijkstra's algorithm
 *
 */

#include "Graph.h"

// model of infinity in Dijkstra's algorithm
const double INFINITY = 99999999.0;

/*
 * Class ShortestPath
 *
 *  Holds a graph pointer that it works with
 */
class ShortestPath
{
private:
    Graph *g;

    bool is_debug_enabled;

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

        if (is_debug_enabled) cout << "Open set before pop: ";
        if (is_debug_enabled) display_set(vector_set);

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

        if (is_debug_enabled) cout << "Open set after pop: ";
        if (is_debug_enabled) display_set(vector_set);

        return min_node;
    }

public:
    ShortestPath(Graph *g): g(g) { is_debug_enabled = false; }
    ~ShortestPath() {}

    void toggle_debug()
    {
        is_debug_enabled = ~is_debug_enabled;
    }

    /*
     * path_size() can run under one of two modes determined
     * by the value of average:
     *
     * average = false ===> basic use case finding shortest path from src to dst
     * average = true ===> use case for finding average shortest path from src to all destinations in g
     */
    double path_size(int src, int dst, bool average)
    {
        if (is_debug_enabled) cout << endl;
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
            if (is_debug_enabled) cout << "    Adding node " << latest_added_id << " to closed set" << endl;
            closed_set.push_back(latest_added_id);

            // relaxation step
            vector<Edge> edges = latest_added->get_edges();
            double starting_distance = latest_added->get_distance();

            for (unsigned int i = 0; i < edges.size(); i++)
            {
                Node *v = edges[i].get_v();
                if (set_contains(closed_set, v->get_id()))
                    continue; // skip already visited nodes

                if (is_debug_enabled) cout << "    Relaxing node " << v->get_id() << endl;
                double current_distance = v->get_distance();
                double cost = edges[i].get_cost();

                double new_distance = starting_distance + cost;

                if (new_distance < current_distance)
                    v->set_distance(new_distance);

                if (!set_contains(open_set, v->get_id()))
                    open_set.push_back(v->get_id());
            }

        }

        if (average) {
            double sum = 0;

            for (unsigned int i = 0; i < closed_set.size(); i++) {
                sum += g->get_node(closed_set[i])->get_distance();
            }

            if (is_debug_enabled) cout << sum << " / " << closed_set.size() - 1 << endl;
            return (sum/(closed_set.size() - 1));  // -1 to remove src
        }

        Node *dst_node = g->get_node(dst);

        if (dst_node->get_distance() == INFINITY) {
            if (is_debug_enabled) cout << dst << " is unreachable from " << src << "!" << endl;
            return -1.0;
        } else {
            return dst_node->get_distance();
        }
    }

};

#endif

