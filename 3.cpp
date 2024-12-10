#include <iostream>
#include <vector>
#include <queue>
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

// Function to perform BFS traversal on the graph
void BFS(int startNode, vector<vector<int>> &graph, vector<bool> &visited)
{
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;

    // Start the BFS traversal
    while (!q.empty())
    {
        int currentNode = q.front();
        q.pop();
        cout << currentNode << " "; // Print the current node as part of the BFS traversal

        // Visit all the adjacent nodes of the current node
        for (int neighbor : graph[currentNode])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    // Number of nodes in the graph
    int nodes = 6;

    // Adjacency list representation of the graph
    vector<vector<int>> graph(nodes);

    // Example graph:
    // 0 -- 1 -- 2
    // |    |
    // 4 -- 3
    graph[0].push_back(1);
    graph[1].push_back(0);
    graph[1].push_back(2);
    graph[2].push_back(1);
    graph[0].push_back(4);
    graph[4].push_back(0);
    graph[3].push_back(1);
    graph[1].push_back(3);
    graph[4].push_back(3);
    graph[3].push_back(4);

    // Display the graph before BFS
    displayGraph(graph);

    // Vector to keep track of visited nodes
    vector<bool> visited(nodes, false);

    // Perform BFS starting from node 0
    cout << "\nBFS traversal starting from node 0: ";
    BFS(0, graph, visited);
    cout << endl;
    system("pause");
    return 0;
}
