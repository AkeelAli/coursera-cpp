#include "Graph.h"

#include <queue>

int main(void) {

/*
    Node u(1);
    Node v(2);
    Node x(3);

    u.add_edge(&v, 10);
    u.add_edge(&x, 20);

    u.display_edges();
 */

/*
    Graph g(10, 0.2, 1.0, 10.0);

    g.display_nodes();
*/

    srand(time(0));
    priority_queue<int,vector<int>,greater<int> > q;
    for( int i = 0; i != 10; ++i ) q.push(rand()%10);
    cout << "Min-heap, popped one by one: ";
    while( ! q.empty() ) {
        cout << q.top() << ' ';  // 0 3 3 3 4 5 5 6 8 9
        q.pop();
    }
    cout << endl;


    return 0;
}
