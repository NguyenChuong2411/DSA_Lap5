#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Define a constant for infinity
const int INF = 1e9; // This is a large number to represent infinity

// Custom comparator for the priority queue to order by smallest distance
struct Compare
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.first > b.first; // Priority queue will pop the pair with the smallest first element (distance)
    }
};

// Function to implement Dijkstra's algorithm
void dijkstra(int start, const vector<vector<pair<int, int>>> &graph, vector<int> &distances)
{
    // Create a priority queue to store the (distance, vertex) pairs
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    // Set the distance to the start vertex as 0
    distances[start] = 0;

    // Push the start vertex into the priority queue with distance 0
    pq.push({0, start});

    while (!pq.empty())
    {
        // Extract the vertex with the minimum distance
        int current_dist = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        // If the current distance is greater than the already found distance, skip it
        if (current_dist > distances[current_vertex])
        {
            continue;
        }

        // Explore the neighbors of the current vertex
        for (const auto &neighbor : graph[current_vertex])
        {
            int next_vertex = neighbor.first;
            int weight = neighbor.second;

            // Calculate the new distance to the neighboring vertex
            int new_dist = current_dist + weight;

            // If a shorter path is found, update the distance and push the new distance into the queue
            if (new_dist < distances[next_vertex])
            {
                distances[next_vertex] = new_dist;
                pq.push({new_dist, next_vertex});
            }
        }
    }
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    // Adjacency list to store the graph
    vector<vector<pair<int, int>>> graph(V);

    // Input edges
    cout << "Enter edges (vertex1, vertex2, weight):\n";
    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w}); // edge from u to v with weight w
        graph[v].push_back({u, w}); // assuming undirected graph (optional)
    }

    // Distance vector to store the shortest distance from the start vertex
    vector<int> distances(V, INF);

    // Choose the source vertex (start from vertex 0)
    int start = 0;

    // Call Dijkstra's algorithm
    dijkstra(start, graph, distances);

    // Output the shortest distances
    cout << "Shortest distances from vertex " << start << ":\n";
    for (int i = 0; i < V; ++i)
    {
        if (distances[i] == INF)
        {
            cout << "Vertex " << i << " is unreachable from vertex " << start << ".\n";
        }
        else
        {
            cout << "Distance to vertex " << i << " is " << distances[i] << endl;
        }
    }
    system("pause");
    return 0;
}
