#include <iostream>
#include <vector>
using namespace std;

// Function to display the graph as an adjacency list
void displayGraph(const vector<vector<int>> &graph)
{
    cout << "Graph representation (Adjacency List):\n";
    for (int i = 0; i < graph.size(); ++i)
    {
        cout << i << ": ";
        for (int neighbor : graph[i])
        {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

// Function to detect a cycle in a directed graph using DFS
bool dfsDirected(int node, vector<vector<int>> &graph, vector<int> &visited)
{
    if (visited[node] == 1)
    { // Node is in the current recursion stack, cycle detected
        return true;
    }
    if (visited[node] == 2)
    { // Node has already been completely processed
        return false;
    }

    // Mark the node as being visited (currently in the recursion stack)
    visited[node] = 1;

    // Explore all the neighbors of the current node
    for (int neighbor : graph[node])
    {
        if (dfsDirected(neighbor, graph, visited))
        {
            return true;
        }
    }

    // Mark the node as completely processed
    visited[node] = 2;
    return false;
}

// Function to detect a cycle in an undirected graph using DFS
bool dfsUndirected(int node, vector<vector<int>> &graph, vector<int> &visited, int parent)
{
    visited[node] = 1;

    // Explore all the neighbors of the current node
    for (int neighbor : graph[node])
    {
        // If the neighbor is not visited, do DFS on it
        if (visited[neighbor] == 0)
        {
            if (dfsUndirected(neighbor, graph, visited, node))
            {
                return true;
            }
        }
        // If the neighbor is visited and is not the parent, a cycle is detected
        else if (neighbor != parent)
        {
            return true;
        }
    }

    return false;
}

// Function to detect cycle in a graph
bool detectCycleInGraph(int nodes, vector<vector<int>> &graph, bool isDirected)
{
    vector<int> visited(nodes, 0); // 0 = Unvisited, 1 = Visiting, 2 = Visited

    // DFS traversal for cycle detection
    for (int i = 0; i < nodes; ++i)
    {
        if (visited[i] == 0)
        {
            if (isDirected)
            {
                if (dfsDirected(i, graph, visited))
                {
                    return true;
                }
            }
            else
            {
                if (dfsUndirected(i, graph, visited, -1))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    // Number of nodes in the graph
    int nodes = 4;

    // Directed graph example:
    vector<vector<int>> directedGraph = {
        {1}, // Node 0 has an edge to node 1
        {2}, // Node 1 has an edge to node 2
        {3}, // Node 2 has an edge to node 3
        {1}  // Node 3 has an edge to node 1 (creates a cycle)
    };

    // Undirected graph example:
    vector<vector<int>> undirectedGraph = {
        {1, 2},    // Node 0 has edges to nodes 1 and 2
        {0, 2},    // Node 1 has edges to nodes 0 and 2
        {0, 1, 3}, // Node 2 has edges to nodes 0, 1, and 3
        {2}        // Node 3 has an edge to node 2 (no cycle in this case)
    };

    // Display the graph before detecting cycles
    cout << "Directed Graph:\n";
    displayGraph(directedGraph);

    cout << "\nUndirected Graph:\n";
    displayGraph(undirectedGraph);

    // Check for cycle in the directed graph
    if (detectCycleInGraph(nodes, directedGraph, true))
    {
        cout << "\nCycle detected in the directed graph." << endl;
    }
    else
    {
        cout << "\nNo cycle detected in the directed graph." << endl;
    }

    // Check for cycle in the undirected graph
    if (detectCycleInGraph(nodes, undirectedGraph, false))
    {
        cout << "\nCycle detected in the undirected graph." << endl;
    }
    else
    {
        cout << "\nNo cycle detected in the undirected graph." << endl;
    }
    system("pause");
    return 0;
}
