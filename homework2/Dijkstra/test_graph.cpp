#include "Graph.h"

#include <queue>

int main(void) {


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


/*
    Graph g(10, 0.2, 1.0, 10.0);

    g.display_nodes();
*/

    return 0;
}
