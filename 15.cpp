#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Structure for representing an edge
struct Edge
{
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Class to represent the graph
class Graph
{
public:
    int V;              // Number of vertices (devices)
    vector<Edge> edges; // List of edges (connections)

    Graph(int V)
    {
        this->V = V;
    }

    // Add an edge to the graph
    void addEdge(int u, int v, int weight)
    {
        edges.push_back(Edge(u, v, weight));
    }

    // Find the parent of a node using Union-Find
    int findParent(vector<int> &parent, int u)
    {
        if (parent[u] == u)
        {
            return u;
        }
        return parent[u] = findParent(parent, parent[u]);
    }

    // Union operation for Union-Find
    void unionSets(vector<int> &parent, vector<int> &rank, int u, int v)
    {
        int rootU = findParent(parent, u);
        int rootV = findParent(parent, v);

        if (rootU != rootV)
        {
            // Union by rank
            if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
            }
            else if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
            }
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

    // Kruskal's algorithm to find Minimum Spanning Tree (MST)
    vector<Edge> kruskalMST()
    {
        sort(edges.begin(), edges.end(), [](const Edge &e1, const Edge &e2)
             { return e1.weight < e2.weight; });

        vector<int> parent(V);
        vector<int> rank(V, 0);
        for (int i = 0; i < V; i++)
        {
            parent[i] = i;
        }

        vector<Edge> mst;
        for (const auto &edge : edges)
        {
            int u = edge.u, v = edge.v;
            if (findParent(parent, u) != findParent(parent, v))
            {
                mst.push_back(edge);
                unionSets(parent, rank, u, v);
            }
        }
        return mst;
    }

    // Helper function to find bridges (critical edges) in the graph
    void dfs(int u, vector<bool> &visited, vector<int> &disc, vector<int> &low,
             vector<int> &parent, vector<Edge> &bridges)
    {
        static int time = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;

        for (const auto &edge : edges)
        {
            if (edge.u == u)
            {
                int v = edge.v;
                if (!visited[v])
                {
                    parent[v] = u;
                    dfs(v, visited, disc, low, parent, bridges);

                    // Check if the subtree rooted at v has a connection back to one of the ancestors of u
                    low[u] = min(low[u], low[v]);

                    // If the lowest vertex reachable from v is below u in DFS tree, then u-v is a bridge
                    if (low[v] > disc[u])
                    {
                        bridges.push_back(edge);
                    }
                }
                else if (v != parent[u])
                {
                    low[u] = min(low[u], disc[v]);
                }
            }
        }
    }

    // Function to find all bridges in the graph
    vector<Edge> findBridges()
    {
        vector<bool> visited(V, false);
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<int> parent(V, -1);
        vector<Edge> bridges;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                dfs(i, visited, disc, low, parent, bridges);
            }
        }

        return bridges;
    }
};

// Helper function to print the MST edges
void printMST(const vector<Edge> &mst)
{
    cout << "Minimum Spanning Tree (MST):\n";
    for (const auto &edge : mst)
    {
        cout << "Edge: " << edge.u << " - " << edge.v << " Weight: " << edge.weight << endl;
    }
}

// Helper function to print the bridges (critical edges)
void printBridges(const vector<Edge> &bridges)
{
    cout << "Critical Edges (Bridges):\n";
    for (const auto &edge : bridges)
    {
        cout << "Edge: " << edge.u << " - " << edge.v << " Weight: " << edge.weight << endl;
    }
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name: Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    cout << "\n";
    // Create a graph representing the network with 5 devices
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 20);
    g.addEdge(1, 2, 30);
    g.addEdge(1, 3, 40);
    g.addEdge(2, 3, 50);
    g.addEdge(3, 4, 60);

    // Find the MST (optimized network topology for minimum cost)
    vector<Edge> mst = g.kruskalMST();
    printMST(mst);

    // Find bridges (critical edges)
    vector<Edge> bridges = g.findBridges();
    printBridges(bridges);
    system("pause");
    return 0;
}
