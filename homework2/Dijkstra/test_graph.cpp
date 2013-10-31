#include "Graph.h"

int main(void) {

    Node u(1);
    Node v(2);
    Node x(3);

    u.add_edge(&v, 10);
    u.add_edge(&x, 20);

    u.display_edges();

    return 0;
}
