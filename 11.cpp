#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

// Define a structure for an edge (destination node, distance/time)
struct Edge
{
    int destination;
    int weight;

    Edge(int dest, int w) : destination(dest), weight(w) {}
};

// Dijkstra’s algorithm to calculate shortest path from the source to all other nodes
vector<int> dijkstra(int start, int n, const vector<vector<Edge>> &graph)
{
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    // Min-heap priority queue to process nodes with the smallest tentative distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        int node = pq.top().second;
        int node_dist = pq.top().first;
        pq.pop();

        if (node_dist > dist[node])
        {
            continue;
        }

        for (const Edge &edge : graph[node])
        {
            int neighbor = edge.destination;
            int weight = edge.weight;
            int new_dist = node_dist + weight;

            if (new_dist < dist[neighbor])
            {
                dist[neighbor] = new_dist;
                pq.push({new_dist, neighbor});
            }
        }
    }

    return dist;
}

// Function to calculate the shortest route using Dijkstra for multiple delivery points (Greedy approach)
vector<int> findRoute(int start, const vector<vector<Edge>> &graph, const vector<int> &deliveryPoints)
{
    int n = graph.size();
    vector<int> totalDist(deliveryPoints.size());
    vector<bool> visited(deliveryPoints.size(), false);
    int currentPoint = start;
    int totalDistance = 0;

    vector<int> route;
    route.push_back(currentPoint);

    for (int i = 0; i < deliveryPoints.size(); ++i)
    {
        // Use Dijkstra to find the shortest path from currentPoint to each of the delivery points
        vector<int> dist = dijkstra(currentPoint, n, graph);

        // Find the nearest delivery point that has not been visited yet
        int minDist = INT_MAX;
        int nextPoint = -1;

        for (int j = 0; j < deliveryPoints.size(); ++j)
        {
            if (!visited[j])
            {
                if (dist[deliveryPoints[j]] < minDist)
                {
                    minDist = dist[deliveryPoints[j]];
                    nextPoint = j;
                }
            }
        }

        // Mark the chosen point as visited and update total distance
        visited[nextPoint] = true;
        currentPoint = deliveryPoints[nextPoint];
        totalDistance += minDist;
        route.push_back(currentPoint);
    }

    cout << "Total Distance: " << totalDistance << endl;
    return route;
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    // Example graph (adjacency list representation)
    int n = 6; // Total nodes (locations)
    vector<vector<Edge>> graph(n);

    // Adding edges (location1 -> location2 with weight=distance)
    graph[0].push_back(Edge(1, 2));
    graph[0].push_back(Edge(2, 4));
    graph[1].push_back(Edge(2, 1));
    graph[1].push_back(Edge(3, 7));
    graph[2].push_back(Edge(3, 3));
    graph[3].push_back(Edge(4, 1));
    graph[4].push_back(Edge(5, 5));
    graph[5].push_back(Edge(0, 8));

    // List of delivery points (nodes)
    vector<int> deliveryPoints = {1, 2, 3, 4}; // Locations 1, 2, 3, 4 need to be visited

    // Start location
    int start = 0;

    // Find the best route using a greedy approach
    vector<int> route = findRoute(start, graph, deliveryPoints);

    // Output the delivery route
    cout << "Route: ";
    for (int i : route)
    {
        cout << i << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
