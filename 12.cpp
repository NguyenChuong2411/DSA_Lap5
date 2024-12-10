#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

// Custom constant for "infinity" (a large value)
const int INF = 1e9;

// Graph structure to represent the social network
class SocialNetwork
{
public:
    vector<vector<int>> adjList; // Adjacency list for the graph
    int numUsers;                // Number of users in the network

    SocialNetwork(int n) : numUsers(n)
    {
        adjList.resize(n);
    }

    // Add a friendship (undirected edge)
    void addFriendship(int user1, int user2)
    {
        adjList[user1].push_back(user2);
        adjList[user2].push_back(user1);
    }

    // Degree Centrality
    vector<int> degreeCentrality()
    {
        vector<int> centrality(numUsers, 0);
        for (int i = 0; i < numUsers; ++i)
        {
            centrality[i] = adjList[i].size();
        }
        return centrality;
    }

    // BFS to calculate shortest paths
    vector<int> bfs(int start)
    {
        vector<int> dist(numUsers, INF);
        dist[start] = 0;
        queue<int> q;
        q.push(start);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : adjList[u])
            {
                if (dist[v] == INF)
                {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    }

    // Betweenness Centrality using shortest path counts
    vector<int> betweennessCentrality()
    {
        vector<int> centrality(numUsers, 0);

        // Approximate betweenness centrality by counting shortest paths
        for (int i = 0; i < numUsers; ++i)
        {
            vector<int> dist = bfs(i);
            for (int j = 0; j < numUsers; ++j)
            {
                if (dist[j] != INF && i != j)
                {
                    centrality[j] += 1; // Simple approximation (can be more refined)
                }
            }
        }
        return centrality;
    }

    // Closeness Centrality
    vector<int> closenessCentrality()
    {
        vector<int> centrality(numUsers, 0);
        for (int i = 0; i < numUsers; ++i)
        {
            vector<int> dist = bfs(i);
            for (int j = 0; j < numUsers; ++j)
            {
                if (dist[j] != INF)
                {
                    centrality[i] += dist[j];
                }
            }
        }
        return centrality;
    }

    // Simple Community Detection: Find connected components (a basic approach)
    vector<vector<int>> findCommunities()
    {
        vector<bool> visited(numUsers, false);
        vector<vector<int>> communities;

        for (int i = 0; i < numUsers; ++i)
        {
            if (!visited[i])
            {
                vector<int> community;
                dfs(i, visited, community);
                communities.push_back(community);
            }
        }
        return communities;
    }

private:
    // DFS to find connected components (communities)
    void dfs(int node, vector<bool> &visited, vector<int> &community)
    {
        visited[node] = true;
        community.push_back(node);
        for (int neighbor : adjList[node])
        {
            if (!visited[neighbor])
            {
                dfs(neighbor, visited, community);
            }
        }
    }
};

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    // Example: Create a social network with 8 users
    SocialNetwork sn(8);

    // Add friendships (edges)
    sn.addFriendship(0, 1);
    sn.addFriendship(0, 2);
    sn.addFriendship(1, 3);
    sn.addFriendship(2, 3);
    sn.addFriendship(3, 4);
    sn.addFriendship(4, 5);
    sn.addFriendship(5, 6);
    sn.addFriendship(6, 7);
    sn.addFriendship(3, 7);

    // Degree Centrality
    vector<int> degree = sn.degreeCentrality();
    cout << "Degree Centrality: ";
    for (int val : degree)
    {
        cout << val << " ";
    }
    cout << endl;

    // Betweenness Centrality
    vector<int> betweenness = sn.betweennessCentrality();
    cout << "Betweenness Centrality: ";
    for (int val : betweenness)
    {
        cout << val << " ";
    }
    cout << endl;

    // Closeness Centrality
    vector<int> closeness = sn.closenessCentrality();
    cout << "Closeness Centrality: ";
    for (int val : closeness)
    {
        cout << val << " ";
    }
    cout << endl;

    // Community Detection
    vector<vector<int>> communities = sn.findCommunities();
    cout << "Detected Communities: " << endl;
    for (const auto &community : communities)
    {
        for (int user : community)
        {
            cout << user << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
