#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph
{
public:
    int V;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Function to display the graph (adjacency list)
    void displayGraph()
    {
        cout << "Graph (Adjacency List):\n";
        for (int i = 0; i < V; ++i)
        {
            cout << i << ": ";
            for (int neighbor : adj[i])
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // DFS function to find bridges
    void DFS(int u, vector<bool> &visited, vector<int> &disc, vector<int> &low,
             vector<int> &parent, vector<pair<int, int>> &bridges)
    {
        static int time = 0; // Static variable to keep track of discovery time
        visited[u] = true;
        disc[u] = low[u] = ++time; // Initialize discovery time and low value

        // Explore all the vertices adjacent to u
        for (int v : adj[u])
        {
            if (!visited[v])
            {
                parent[v] = u;
                DFS(v, visited, disc, low, parent, bridges);

                // After returning from DFS of v, update the low[u]
                low[u] = min(low[u], low[v]);

                // Check if the subtree rooted at v has a connection back to one of the ancestors of u
                if (low[v] > disc[u])
                {
                    // This means (u, v) is a bridge
                    bridges.push_back({u, v});
                }
            }
            // Update low value of u for parent function calls.
            else if (v != parent[u])
            {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    // Function to find and print all bridges
    void findBridges()
    {
        vector<bool> visited(V, false);
        vector<int> disc(V, -1);        // Stores discovery times of visited vertices
        vector<int> low(V, -1);         // Earliest visited vertex reachable from subtree
        vector<int> parent(V, -1);      // Parent vertices in DFS tree
        vector<pair<int, int>> bridges; // To store the bridges

        // Call DFS for all unvisited vertices
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                DFS(i, visited, disc, low, parent, bridges);
            }
        }

        // Print all bridges
        cout << "Bridges in the graph are:\n";
        for (auto &bridge : bridges)
        {
            cout << bridge.first << " - " << bridge.second << endl;
        }
    }
};

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    // Create a graph
    Graph g(5);

    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    // Display the graph before finding bridges
    g.displayGraph();

    // Find and print all bridges
    g.findBridges();
    system("pause");
    return 0;
}
