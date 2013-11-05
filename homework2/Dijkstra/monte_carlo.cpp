#include "Graph.h"
#include "ShortestPath.h"

const int NUM_TESTS = 1000;
const int NUM_NODES = 50;
const double LOW_DENSITY = 0.2; // 20% edge density
const double MED_DENSITY = 0.4; // 40% edge density
const double MIN_EDGE_COST = 1.0;
const double MAX_EDGE_COST = 10.0;

void monte_carlo(double edge_density = LOW_DENSITY)
{
    double sum_average_shortest_path = 0;

    for (int i = 0; i < NUM_TESTS; i++) {
        double average = 0;

        Graph g(NUM_NODES, edge_density, MIN_EDGE_COST, MAX_EDGE_COST);

        ShortestPath s(&g);

        average = s.path_size(1, NUM_NODES, true);

        sum_average_shortest_path += average;
    }

    cout << "Graph with " << edge_density << " Edge Density: Average Average Shortest Path = " << sum_average_shortest_path / NUM_TESTS << endl;

}

int main(void)
{
    double density = 0;

    // seed once at the beginning
    srand (time(0));

    monte_carlo(LOW_DENSITY);
    monte_carlo(MED_DENSITY);

    return 0;
}

