#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph
{
public:
    int V;                // Number of vertices
    vector<int> *adjList; // Adjacency list representation

    // Constructor to initialize the graph
    Graph(int V)
    {
        this->V = V;
        adjList = new vector<int>[V];
    }

    // Function to add an undirected edge
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Function to print the adjacency list of the graph
    void printGraph()
    {
        cout << "Graph before finding connected components:" << endl;
        for (int i = 0; i < V; i++)
        {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjList[i])
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Function to perform DFS and find all connected components
    void DFS(int node, vector<bool> &visited)
    {
        stack<int> s;
        s.push(node);
        visited[node] = true;

        while (!s.empty())
        {
            int current = s.top();
            s.pop();
            cout << current << " ";

            // Explore all neighbors of the current node
            for (int neighbor : adjList[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
    }

    // Function to find all connected components in the graph
    void findConnectedComponents()
    {
        vector<bool> visited(V, false); // Array to keep track of visited nodes

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                cout << "Connected Component: ";
                DFS(i, visited);
                cout << endl;
            }
        }
    }
};

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    // Create a graph with 5 vertices
    Graph g(5);

    // Add edges to the graph (undirected)
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    // Show the graph before finding connected components
    g.printGraph();

    // Find and print all connected components
    g.findConnectedComponents();
    system("pause");
    return 0;
}
