#include "Graph.h"

#include <queue>

//Removed in favor of monte_carlo.cpp
#if 0
int main(void) {

/*
    Node u(1);
    Node v(2);
    Node x(3);

    u.add_edge(&v, 10);
    v.add_edge(&u, 10);

    u.add_edge(&x, 20);
    x.add_edge(&u, 20);

    v.add_edge(&x, 5);
    x.add_edge(&v, 5);

    vector<Node *> nodes;
    nodes.push_back(&u);
    nodes.push_back(&v);
    nodes.push_back(&x);

    Graph g (nodes);

    g.display_nodes();

    ShortestPath s(&g);

    cout << s.path_size(1, 3);
*/

/*
    Graph g(10, 0.2, 1.0, 10.0);

    g.display_nodes();
*/

/*
    Graph g(50, 0.2, 1.0, 10.0);

    g.display_nodes();

    ShortestPath s(&g);

    cout << "Average: " << s.path_size(1, 50, true) << endl;

    int num_paths = 0;
    double sum = 0;
    double average = 0;

    for (unsigned int i = 2; i <= 50; i++) {
        double dist = s.path_size(1,i, false);

        if (dist != -1) {
            cout << "dist between 1 & " << i << " is = " << dist << endl;
            sum += dist;
            num_paths++;
        }
    }

    average = sum / num_paths;

    cout << "Computed average: " << sum << " / " << num_paths  << " = " << average << endl;
*/


    return 0;
}
#endif
