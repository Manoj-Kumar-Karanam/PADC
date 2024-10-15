#include <iostream>
#include <vector>
#include <limits>
#include <omp.h>

using namespace std;

struct Edge {
    int src, dest, wt;
};

struct Graph {
    int V, E;
    vector<Edge> edge;
};

Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge.reserve(E); 
    return graph;
}

void printArr(const vector<int>& dist) {
    cout << "Vertex   Distance from Source" << endl;
    for (int i = 0; i < dist.size(); ++i)
        cout << i << "\t\t " << (dist[i] == numeric_limits<int>::max() ? "INF" : to_string(dist[i])) << endl;
}

void bellmanFord(Graph* graph, int src) {
    int V = graph->V;
    vector<int> dist(V, numeric_limits<int>::max());
    dist[src] = 0;

    for (int i = 0; i < V - 1; ++i) {
        vector<int> tempDist = dist; // Temporary distances for this iteration

        #pragma omp parallel for
        for (int j = 0; j < graph->E; ++j) {
            const Edge& edge = graph->edge[j];
            int thread_id = omp_get_thread_num(); // Get the thread ID
            bool relaxed = false;

            if (tempDist[edge.src] != numeric_limits<int>::max() && 
                tempDist[edge.src] + edge.wt < tempDist[edge.dest]) {
                tempDist[edge.dest] = tempDist[edge.src] + edge.wt;
                relaxed = true;
            }

            // Print which thread relaxed which edge
            if (relaxed) {
                #pragma omp critical
                {
                    cout << "Thread " << thread_id << " relaxed edge (" 
                         << edge.src << " -> " << edge.dest << ") with weight " 
                         << edge.wt << endl;
                }
            }
        }

        dist = tempDist; // Update the original distance vector
    }

    // Check for negative-weight cycles
    for (const auto& edge : graph->edge) {
        if (dist[edge.src] != numeric_limits<int>::max() && 
            dist[edge.src] + edge.wt < dist[edge.dest]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    printArr(dist);
}

int main() {
    int V = 6; 
    int E = 9; 
    Graph* graph = createGraph(V, E);
    graph->edge = {
        {0, 1, 1},
        {1, 5, 3},
        {1, 3, -1},
        {2, 0, 2},
        {2, 1, 4},
        {2, 3, 4},
        {3, 5, 1},
        {4, 0, 5},
        {4, 2, -2}
    };
    
    bellmanFord(graph, 4); 

    delete graph; 
    return 0;
}
