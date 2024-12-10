#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Define a large value to represent "infinity" (max possible distance)
const int INF = 1e9; // You can adjust the value based on your graph size

// Define a structure for an edge (destination node, weight)
struct Edge
{
    int destination;
    int weight;

    Edge(int dest, int w) : destination(dest), weight(w) {}
};

// Define a comparator for the priority queue (min-heap)
struct Compare
{
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        return a.second > b.second; // Compare based on distance (ascending order)
    }
};

// Function to implement Dijkstra's algorithm
vector<int> dijkstra(int start, int n, const vector<vector<Edge>> &graph)
{
    // Distance table initialized to "infinity"
    vector<int> dist(n, INF);
    dist[start] = 0; // Distance to the start node is 0

    // Min-heap priority queue: stores (node, distance)
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({start, 0}); // Push the start node into the queue

    while (!pq.empty())
    {
        // Extract the node with the smallest distance
        int node = pq.top().first;
        int node_dist = pq.top().second;
        pq.pop();

        // If the current distance is already greater than the stored distance, skip it
        if (node_dist > dist[node])
        {
            continue;
        }

        // Explore the neighbors
        for (const Edge &edge : graph[node])
        {
            int neighbor = edge.destination;
            int weight = edge.weight;
            int new_dist = node_dist + weight;

            // If a shorter path to the neighbor is found
            if (new_dist < dist[neighbor])
            {
                dist[neighbor] = new_dist;
                pq.push({neighbor, new_dist}); // Push the neighbor into the queue
            }
        }
    }

    return dist; // Return the shortest distances from the start node to all other nodes
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    // Example graph (undirected weighted graph)
    int n = 5; // Number of nodes
    vector<vector<Edge>> graph(n);

    // Add edges to the graph
    graph[0].push_back(Edge(1, 2)); // Node 0 -> Node 1 with weight 2
    graph[0].push_back(Edge(2, 4)); // Node 0 -> Node 2 with weight 4
    graph[1].push_back(Edge(2, 1)); // Node 1 -> Node 2 with weight 1
    graph[1].push_back(Edge(3, 7)); // Node 1 -> Node 3 with weight 7
    graph[2].push_back(Edge(3, 3)); // Node 2 -> Node 3 with weight 3
    graph[3].push_back(Edge(4, 1)); // Node 3 -> Node 4 with weight 1
    graph[4].push_back(Edge(0, 8)); // Node 4 -> Node 0 with weight 8

    // Set the start node
    int start = 0;

    // Call Dijkstra's algorithm
    vector<int> shortest_distances = dijkstra(start, n, graph);

    // Output the shortest distances from the start node to all other nodes
    cout << "Shortest distances from node " << start << " to all other nodes:" << endl;
    for (int i = 0; i < n; ++i)
    {
        if (shortest_distances[i] == INF)
        {
            cout << "Node " << i << " is unreachable." << endl;
        }
        else
        {
            cout << "Node " << i << ": " << shortest_distances[i] << endl;
        }
    }
    system("pause");
    return 0;
}
