#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = 1e9; // A large value to represent infinity (inaccessible paths)

// Graph structure to represent the city's road network
class CityTrafficNetwork
{
public:
    vector<vector<pair<int, int>>> adjList; // adjacency list for roads (node, weight)
    int numIntersections;                   // number of intersections (nodes)

    CityTrafficNetwork(int n) : numIntersections(n)
    {
        adjList.resize(n);
    }

    // Add a road (edge) between two intersections (nodes)
    void addRoad(int u, int v, int weight)
    {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Assuming bidirectional roads
    }

    // Dijkstra's algorithm to find the shortest paths from a source
    vector<int> dijkstra(int source)
    {
        vector<int> dist(numIntersections, INF);
        dist[source] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});

        while (!pq.empty())
        {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u])
                continue;

            for (auto &neighbor : adjList[u])
            {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }

    // Find the centrality of nodes using betweenness centrality approximation
    vector<int> betweennessCentrality()
    {
        vector<int> centrality(numIntersections, 0);

        // Approximate betweenness centrality by considering all pairs of nodes
        for (int i = 0; i < numIntersections; ++i)
        {
            vector<int> dist = dijkstra(i); // Find shortest paths from node i

            for (int j = 0; j < numIntersections; ++j)
            {
                if (dist[j] != INF && i != j)
                {
                    centrality[j] += 1; // Increment centrality if node j is in the path
                }
            }
        }

        return centrality;
    }

    // Find alternative routes by considering multiple shortest paths (using Dijkstra multiple times)
    vector<vector<int>> findAlternativeRoutes(int source)
    {
        vector<vector<int>> allRoutes;
        for (int i = 0; i < numIntersections; ++i)
        {
            if (i != source)
            {
                vector<int> dist = dijkstra(source);
                allRoutes.push_back(dist);
            }
        }
        return allRoutes;
    }

    // Suggest optimal traffic light timings (based on traffic bottlenecks)
    void suggestTrafficLightTimings()
    {
        vector<int> centrality = betweennessCentrality();

        cout << "Suggested Traffic Light Timings Based on Traffic Bottlenecks:" << endl;
        for (int i = 0; i < numIntersections; ++i)
        {
            if (centrality[i] > 1)
            { // Assuming a threshold for bottleneck detection
                cout << "Intersection " << i << " is a potential bottleneck. Adjust traffic light timings." << endl;
            }
        }
    }

    // Display the shortest path from source to all intersections
    void displayShortestPaths(int source)
    {
        vector<int> dist = dijkstra(source);

        cout << "Shortest paths from Intersection " << source << " to all other intersections:" << endl;
        for (int i = 0; i < numIntersections; ++i)
        {
            if (dist[i] == INF)
            {
                cout << "Intersection " << i << " is unreachable" << endl;
            }
            else
            {
                cout << "Distance to Intersection " << i << ": " << dist[i] << endl;
            }
        }
    }
};

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    // Create a city with 6 intersections
    CityTrafficNetwork city(6);

    // Add roads between intersections with weights (representing traffic or travel time)
    city.addRoad(0, 1, 2); // Road between intersection 0 and 1 with a travel time of 2
    city.addRoad(0, 2, 4); // Road between intersection 0 and 2 with a travel time of 4
    city.addRoad(1, 2, 1); // Road between intersection 1 and 2 with a travel time of 1
    city.addRoad(1, 3, 7); // Road between intersection 1 and 3 with a travel time of 7
    city.addRoad(2, 4, 3); // Road between intersection 2 and 4 with a travel time of 3
    city.addRoad(3, 5, 1); // Road between intersection 3 and 5 with a travel time of 1
    city.addRoad(4, 5, 5); // Road between intersection 4 and 5 with a travel time of 5

    // Display the shortest paths from intersection 0
    city.displayShortestPaths(0);

    // Suggest optimal traffic light timings based on traffic bottlenecks
    city.suggestTrafficLightTimings();

    // Find alternative routes from intersection 0
    vector<vector<int>> alternativeRoutes = city.findAlternativeRoutes(0);
    cout << "Alternative Routes from Intersection 0:" << endl;
    for (int i = 0; i < alternativeRoutes.size(); ++i)
    {
        cout << "Distance to Intersection " << i << ": " << alternativeRoutes[i][i] << endl;
    }
    system("pause");
    return 0;
}
