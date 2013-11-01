#include "Graph.h"



int main(void) {

/*
    Node u(1);
    Node v(2);
    Node x(3);

    u.add_edge(&v, 10);
    u.add_edge(&x, 20);

    u.display_edges();
 */

    Graph g(10, 0.2, 1.0, 10.0);

    g.display_nodes();

    return 0;
}
