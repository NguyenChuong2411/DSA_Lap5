#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Graph
{
public:
    int V;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency list representation

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

    // Function to calculate the modularity of a given community partition
    double modularity(const vector<int> &communities)
    {
        double m = 0.0; // Total number of edges
        for (int i = 0; i < V; ++i)
        {
            m += adj[i].size();
        }
        m /= 2.0; // Because it's an undirected graph

        double Q = 0.0;
        vector<double> community_weights(V, 0);     // Community -> Total degree within the community
        vector<double> community_connections(V, 0); // Community -> Total weight of connections to other communities

        // Calculate the community internal weights and external connections
        for (int u = 0; u < V; ++u)
        {
            for (int v : adj[u])
            {
                if (communities[u] == communities[v])
                {
                    community_weights[communities[u]] += 1.0;
                }
                else
                {
                    community_connections[communities[u]] += 1.0;
                }
            }
        }

        // Calculate modularity Q
        for (int i = 0; i < V; ++i)
        {
            double internal_weight = community_weights[i];
            double total_weight = community_connections[i];

            double expected_weight = total_weight * internal_weight / (2 * m);
            Q += (internal_weight / (2 * m)) - expected_weight;
        }

        return Q;
    }

    // Phase 1: Local modularity optimization (community assignment)
    void louvainPhase1(vector<int> &communities)
    {
        bool improvement = true;
        int iteration = 0;
        while (improvement && iteration < 100)
        { // Limit iterations to prevent infinite loops
            improvement = false;
            iteration++;
            // For each node, try moving it to the best neighboring community
            for (int u = 0; u < V; ++u)
            {
                int best_community = communities[u];
                double best_modularity_increase = 0;

                // Store the communities of all neighboring nodes
                vector<int> neighbor_communities;
                for (int v : adj[u])
                {
                    int comm = communities[v];
                    if (find(neighbor_communities.begin(), neighbor_communities.end(), comm) == neighbor_communities.end())
                    {
                        neighbor_communities.push_back(comm);
                    }
                }

                // Try moving to each neighboring community and calculate modularity increase
                for (int new_community : neighbor_communities)
                {
                    // Temporarily move the node to the new community
                    int old_community = communities[u];
                    communities[u] = new_community;

                    double new_modularity = modularity(communities);
                    double mod_increase = new_modularity - modularity(communities);
                    if (mod_increase > best_modularity_increase)
                    {
                        best_modularity_increase = mod_increase;
                        best_community = new_community;
                    }

                    // Restore original community
                    communities[u] = old_community;
                }

                // Move the node to the best community if there's an improvement
                if (best_community != communities[u])
                {
                    communities[u] = best_community;
                    improvement = true;
                }
            }
            cout << "Phase 1 Iteration " << iteration << " complete. Modularity: " << modularity(communities) << endl;
        }
    }

    // Phase 2: Create the new graph with communities as nodes
    Graph aggregateGraph(const vector<int> &communities)
    {
        vector<vector<int>> new_adj;
        int new_V = 0;
        vector<int> community_map(V, -1); // Map for community -> new node index

        // Create a new graph where each community becomes a node
        for (int u = 0; u < V; ++u)
        {
            int comm = communities[u];
            if (community_map[comm] == -1)
            {
                community_map[comm] = new_V++;
                new_adj.push_back(vector<int>());
            }
        }

        // Add edges between communities based on the original graph
        for (int u = 0; u < V; ++u)
        {
            int u_comm = communities[u];
            for (int v : adj[u])
            {
                int v_comm = communities[v];
                if (u_comm != v_comm)
                {
                    new_adj[community_map[u_comm]].push_back(community_map[v_comm]);
                }
            }
        }

        Graph new_graph(new_V);
        for (int i = 0; i < new_V; ++i)
        {
            for (int v : new_adj[i])
            {
                new_graph.addEdge(i, v);
            }
        }

        return new_graph;
    }

    // Louvain method to detect communities
    vector<int> louvainMethod()
    {
        vector<int> communities(V);
        for (int i = 0; i < V; ++i)
        {
            communities[i] = i; // Initialize each node in its own community
        }

        // Phase 1: Optimize modularity
        cout << "Starting Phase 1...\n";
        louvainPhase1(communities);
        cout << "Phase 1 Complete.\n";

        // Phase 2: Aggregate the graph
        cout << "Starting Phase 2...\n";
        Graph new_graph = aggregateGraph(communities);
        cout << "Phase 2 Complete.\n";

        // Reapply Louvain method recursively
        if (new_graph.V > V / 2)
        { // Stop recursion if the graph size is small enough
            vector<int> new_communities = new_graph.louvainMethod();
            // Map back the community IDs to the original graph
            vector<int> final_communities(V);
            for (int i = 0; i < V; ++i)
            {
                final_communities[i] = new_communities[communities[i]];
            }
            return final_communities;
        }
        return communities;
    }
};

// Test the Louvain method
int main()
{
    // Create a graph
    Graph g(8);

    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(6, 7);

    // Apply Louvain method
    vector<int> communities = g.louvainMethod();

    // Output communities
    cout << "Detected communities:\n";
    for (int i = 0; i < communities.size(); ++i)
    {
        cout << "Node " << i << " -> Community " << communities[i] << endl;
    }

    return 0;
}
